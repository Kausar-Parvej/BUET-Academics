import torch
from torchvision import datasets, transforms
from torch.utils.data import DataLoader
import torch.nn as nn
import torch.optim as optim
import numpy as np
import random


def set_seed(seed):
    random.seed(seed)
    np.random.seed(seed)
    torch.manual_seed(seed)
    torch.cuda.manual_seed(seed)
    torch.cuda.manual_seed_all(seed)
    torch.backends.cudnn.deterministic = True
    torch.backends.cudnn.benchmark = False


set_seed(42)

transform = transforms.Compose([
    transforms.Resize((224, 224)),
    transforms.ToTensor(),
    transforms.Normalize(mean=[0.485, 0.456, 0.406],
                         std=[0.229, 0.224, 0.225])
])


# Load dataset
dataset = datasets.ImageFolder(
    root="images/",
    transform=transform
)

# DataLoader
dataloader = DataLoader(
    dataset,
    batch_size=30,
    shuffle=True,
)

images, labels = next(iter(dataloader))

print("Batch image tensor shape:", images.shape)
print("Batch labels tensor shape:", labels.shape)

# Number of classes
num_classes = len(dataset.classes)

# # ResNet Building Blocks
# class ResidualBlock(nn.Module):
#     """Basic Residual Block with skip connection"""
#     def __init__(self, in_channels):
#         super(ResidualBlock, self).__init__()
        
#         # TODO: Layer 1
#         self.conv1 = nn.Conv2d(in_channels, in_channels, kernel_size=3, stride=1, padding=1)
#         self.bn1 = nn.BatchNorm2d(in_channels)
#         self.relu1 = nn.ReLU()
        
#         # TODO: Layer 2
#         self.conv2 = nn.Conv2d(in_channels, in_channels, kernel_size=5, stride=1, padding=2)
#         self.bn2 = nn.BatchNorm2d(in_channels)
        
#     def forward(self, x):
#         identity = x
        
#         # TODO: Layer 1
#         out = self.conv1(x)
#         out = self.bn1(out)
#         out = self.relu1(out)
        
#         # TODO: Layer 2
#         out = self.conv2(out)
#         out = self.bn2(out)
        
#         # Add skip connection
#         out = out + identity
#         out = nn.ReLU()(out)
        
#         return out


# ResNet Building Blocks
class ResidualBlock(nn.Module):
    """Basic Residual Block with skip connection"""
    def __init__(self, in_channels):
        super(ResidualBlock, self).__init__()
        
        # TODO: Layer 1
        self.layer_1 = nn.Sequential(
            nn.Conv2d(in_channels, in_channels, kernel_size=3, padding=1, stride=1),  
            # output size = floor( (Input + 2×padding - kernel_size)/stride )
            nn.BatchNorm2d(in_channels),
            nn.ReLU()
        )
        
        
        # TODO: Layer 2
        self.layer_2 = nn.Sequential(
            nn.Conv2d(in_channels, in_channels, kernel_size=5, padding=2, stride=1), 
            nn.BatchNorm2d(in_channels)
        )
        
        
    def forward(self, x):
        identity = x
        
        # TODO: Layer 1
        x = self.layer_1(x)
    
        
        
        # TODO: Layer 2
        x = self.layer_2(x)
        

        out = x + identity  # Skip connection
        out = nn.ReLU()(out)
        
        
        return out


class CustomResNet(nn.Module):
    """Custom ResNet architecture without nn.Sequential"""
    def __init__(self):
        super(CustomResNet, self).__init__()
        
        # TODO: Initial convolution layer
        self.init_conv = nn.Sequential(
            nn.Conv2d(3, 64, kernel_size=8, padding=3, stride=2),
            nn.BatchNorm2d(64),
            nn.ReLU(),
            nn.MaxPool2d(kernel_size=3, stride=2, padding=1)
        )
        
        
        # TODO: Layer 1
        self.layer1_res = ResidualBlock(64)
        
        # TODO: Layer 1 conv
        self.layer1_conv = nn.Sequential(
            nn.Conv2d(64, 32, kernel_size=4, padding=7, stride=1),
            nn.BatchNorm2d(32),
            nn.ReLU()
        )
        
        # TODO: Layer 2
        self.layer2_res = ResidualBlock(32)
        
        # TODO: Layer 2 conv
        self.layer2_conv = nn.Sequential(
            nn.Conv2d(32, 16, kernel_size=5, padding=2, stride=2),
            nn.BatchNorm2d(16),
            nn.ReLU()
        )
        

        # TODO: Layer 3
        self.layer3_res = nn.Sequential(
            ResidualBlock(16),
            nn.BatchNorm2d(16)
        )
        
        
        # TODO: Global average pooling and FC layer
        self.global_avg_pool = nn.AdaptiveAvgPool2d((1, 1))
        self.flatten = nn.Flatten()
        self.fc = nn.Linear(16, 1)  # Binary classification
        
    

    def forward(self, x):
        # TODO: Initial conv
        x = self.init_conv(x)
        
        # TODO: Layer 1
        x = self.layer1_res(x)

        # TODO: Layer 1 conv
        x = self.layer1_conv(x)
        

        # TODO: Layer 2
        x = self.layer2_res(x)
        
        
        # TODO: Layer 2 conv
        x = self.layer2_conv(x)

    
        # TODO: Layer 3
        x = self.layer3_res(x)
        

        # TODO: Global pooling and FC layer
        x = self.global_avg_pool(x)
        x = self.flatten(x)
        x = self.fc(x)
        
        return x


# Initialize model
device = torch.device("cpu")

model = CustomResNet().to(device)

criterion = nn.BCEWithLogitsLoss()
optimizer = optim.Adam(model.parameters(), lr=1e-3)

num_epochs = 4

print(f"\nTraining Custom ResNet with {sum(p.numel() for p in model.parameters())} parameters")
print(f"Device: {device}\n")

for epoch in range(num_epochs):
    model.train()
    running_loss = 0.0
    correct = 0
    total = 0

    for images, labels in dataloader:
        images = images.to(device)
        labels = labels.float().to(device)

        # Forward pass
        outputs = model(images).squeeze()
        loss = criterion(outputs, labels)

        # Backward pass
        optimizer.zero_grad()
        loss.backward()
        optimizer.step()

        # Statistics
        running_loss += loss.item() * images.size(0)
        
        predicted = (torch.sigmoid(outputs) > 0.5).long()
        total += labels.size(0)
        correct += (predicted == labels.long()).sum().item()

    epoch_loss = running_loss / total
    epoch_acc = 100 * correct / total

    print(f"Epoch [{epoch+1}/{num_epochs}] "
          f"Loss: {epoch_loss:.4f} | Accuracy: {epoch_acc:.2f}%")
