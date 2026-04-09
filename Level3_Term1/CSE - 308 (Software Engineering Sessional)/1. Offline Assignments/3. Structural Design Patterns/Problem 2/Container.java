import java.util.ArrayList;
public class Container extends Component{
    private final ArrayList<Component> children;

    public Container(String name, String type, String directory){
        this.name = name;
        this.type = type;
        this.componentCount = 0;
        this.size = 0;
        this.directory = directory;
        this.creationTime = "13 December, 2023 5:12 PM";
        children = new ArrayList<>();
    }

    public Container changeDirectory(String directory){
        for(Component child : children){
            String additional = directory + "\\";
            if(child.name.equals(additional) || child.name.equals(directory) ){
                if(child.type.equals("File")){
                    System.out.println("Error! It is a file");
                    return null;
                }
                System.out.println("In the directory " + child.directory);
                return (Container) child;
            }
        }
        System.out.println("Error! The Folder or Drive doesn't exist in the current directory");
        return null;
    }

    @Override
    public void details() {
        this.componentCount = children.size();
        this.size = this.calculateSize();

        System.out.println();
        System.out.println("Name: " + name);
        System.out.println("Type: " + type);
        System.out.println("Size: " + size + "kB");
        System.out.println("Directory: " + directory);
        System.out.println("Component Count: " + componentCount);
        System.out.println("Creation Time: " + creationTime);
        System.out.println();
    }

    @Override
    public int calculateSize() {
        int temp = 0;
        for(Component child : children){
            temp += child.calculateSize();
        }
        return temp;
    }

    public void findChild(String name){
        System.out.println();
        for(Component child : children){
            if(child.name.equals(name)){
                child.details();
                return;
            }
        }
        System.out.println();
        System.out.println("Error! Does not exist in the current directory");
    }


    @Override
    public void listing() {
        this.size = this.calculateSize();
        System.out.println(name + "\t" + size + " kB\t" + creationTime);
    }
    public void childList() {
        for(Component child : children){
            child.listing();
        }
    }

    @Override
    public void delete(String name) {
        for(Component child : children){
            if(child.name.equals(name)){
                if(child.type.equals("File")){
                    System.out.println(child.name + " deleted from the current directory" );
                    children.remove(child);
                }
                else {
                    if(child.componentCount == 0){
                        System.out.println(child.name + " deleted from the current directory" );
                        children.remove(child);
                        return;
                    }
                    System.out.println("Container is not empty!");
                }
                return;
            }
        }
    }

    public void deleteAll(){
        for(Component child : children){
            if(child.type.equals("File")){
                children.remove(child);
            }
            else{
                Container childContainer = (Container) child;
                childContainer.deleteAll();
                children.remove(child);
            }
        }
    }

    @Override
    public void recursiveDelete(String name) {
        for(Component child : children){
            if(child.name.equals(name)){
                if(child.type.equals("File")){
                    children.remove(child);
                    System.out.println("Warning! " + child.name + " Deleted, But it is a file");
                }
                else{
                    Container childContainer = (Container) child;
                    childContainer.deleteAll();
                    children.remove(child);
                }
                System.out.println(name + " and all it's files/folders are deleted");
                return;
            }
        }
        System.out.println(name + " does not exist in the current directory");
    }


    public void makeDir(String name) {
        for(Component component : children){
            if(component.name.equals(name)){
                System.out.println("Error! This name already exist in the current directory");
                return;
            }
        }
        if(type.equals("Drive") || type.equals("Folder")){
            Component child;
            String childDirectory = directory + "\\" + name;
            child = new Container(name, "Folder", childDirectory);
            children.add(child);
            System.out.println("Created a Folder named " + name +" in the current directory");
        }
    }

    public void touch(String name, int size) {
        for(Component component : children){
            if(component.name.equals(name)){
                System.out.println("Error! This name already exist in the current directory");
                return;
            }
        }
        if(type.equals("Drive") || type.equals("Folder")){
            Component child;
            String childDirectory = directory + "\\" + name;
            child = new File(name, size, childDirectory);
            children.add(child);
            System.out.println("Created a File named " + name +" in the current directory");
        }

    }

    public void makeDrive(String name) {
        for(Component component : children){
            if(component.name.equals(name)){
                System.out.println("Error! This drive already exist in the root directory");
                return;
            }
        }
        name = name + ":";
        if(this.type.equals("Root")){
            Component childDrive;
            childDrive = new Container(name, "Drive", name);
            this.children.add(childDrive);
            System.out.println("Created a Drive named " + name +" in the Root directory");
        }
    }
}
