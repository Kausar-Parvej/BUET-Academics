#include<bits/stdc++.h>
using namespace std;

#include "car.cpp"


random_device rd;
mt19937_64 gen(rd());

class TreeNode{
public:
    string attribute;
    map<string, TreeNode*> children;

    bool isLeaf;
    string class_label;

    TreeNode(string attribute){
        this->attribute = attribute;
        isLeaf = false;
        class_label = "null";
    }

    TreeNode(string label, bool isLeaf){
        this->isLeaf = isLeaf;
        class_label = label;
        attribute = "null";
    }
};


class DecisionTree{
private:
    TreeNode* root;
    string majorityClass;

    string finfMajorityClass(const vector<Car>& dataset);
    double calculateEntropy(const vector<Car>& dataset);
    double calculateInfoGain(const vector<Car>& dataset, const string& attribute);

    double calculateGini(const vector<Car>& dataset);
    double giniGain(const vector<Car>& dataset, const string& attribute);

    string selectBestAttribute(const vector<Car>& dataset, vector<string>& attributes, bool isInfo_gain);
    TreeNode* buildTree(const vector<Car>& dataset, vector<string>& attributes, bool isInfo_gain, bool isRandomSelection = false);

    vector<pair<string, double>> rankAttributes(const vector<Car>& dataset, const vector<string>& attributes, bool isInfo_gain);
    void deleteTree(TreeNode* node);


public:
    DecisionTree(){
        root = nullptr;
    }
    ~DecisionTree(){
        deleteTree(root);
    }

    void train(const vector<Car>& dataset, bool isInfo_gain);
    void train_randomSelection(const vector<Car>& dataset, bool isInfo_gain);
    string predict(const Car& car);

};




//private functions

void DecisionTree::deleteTree(TreeNode* node){
    if(node == nullptr) return;

    for(auto& child : node->children){
        deleteTree(child.second);
    }
    delete node;
}

string DecisionTree::finfMajorityClass(const vector<Car>& dataset){
    map<string, int> class_count;
    for(auto car : dataset){
        class_count[car.class_label]++;
    }

    string max_label;
    int max_count = 0;
    for(auto l_map : class_count){
        if(l_map.second > max_count){
            max_count = l_map.second;
            max_label = l_map.first;
        }
    }
    return max_label;
}

double DecisionTree::calculateEntropy(const vector<Car>& dataset){
    if(dataset.empty()) return 0.0;

    map<string, int> class_count;
    for(auto& car : dataset){
        class_count[car.class_label]++;
    }

    double entropy = 0.0;
    double dataset_size = static_cast<double>(dataset.size());
    for(auto l_map : class_count){
        double prob = static_cast<double>(l_map.second) / dataset_size;
        if(prob > 0)   //avoid log(0)
            entropy -= prob * log2(prob);
    }
    return entropy;
}

double DecisionTree::calculateInfoGain(const vector<Car>& dataset, const string& attribute){
    map<string, vector<Car>> attribute_map;
    for(auto car : dataset){
        if(attribute == "buying") attribute_map[car.buying].push_back(car);
        else if(attribute == "maint") attribute_map[car.maint].push_back(car);
        else if(attribute == "doors") attribute_map[car.doors].push_back(car);
        else if(attribute == "persons") attribute_map[car.persons].push_back(car);
        else if(attribute == "lug_boot") attribute_map[car.lug_boot].push_back(car);
        else if(attribute == "safety") attribute_map[car.safety].push_back(car);
    }

    double parentEntropy = calculateEntropy(dataset);
    double weighted_childEntropy = 0.0;
    for(auto attr_map : attribute_map){
        if(!attr_map.second.empty()){
            double weight = static_cast<double>(attr_map.second.size()) / dataset.size();
            weighted_childEntropy += weight * calculateEntropy(attr_map.second);
        }
    }
    return parentEntropy - weighted_childEntropy;
}

double DecisionTree::calculateGini(const vector<Car>& dataset){
    map<string, int> class_count;
    for(auto car : dataset){
        class_count[car.class_label]++;
    }

    double gini = 1.0;
    for(auto l_map : class_count){
        double prob = static_cast<double>(l_map.second) / dataset.size();
        gini -= prob * prob;
    }
    return gini;
}

double DecisionTree::giniGain(const vector<Car>& dataset, const string& attribute){
    map<string, vector<Car>> attribute_map;
    for(auto car : dataset){
        if(attribute == "buying") attribute_map[car.buying].push_back(car);
        else if(attribute == "maint") attribute_map[car.maint].push_back(car);
        else if(attribute == "doors") attribute_map[car.doors].push_back(car);
        else if(attribute == "persons") attribute_map[car.persons].push_back(car);
        else if(attribute == "lug_boot") attribute_map[car.lug_boot].push_back(car);
        else if(attribute == "safety") attribute_map[car.safety].push_back(car);
    }

    double parentGini = calculateGini(dataset);
    double weighted_childGini = 0.0;
    for(auto attr_map : attribute_map){
        if(!attr_map.second.empty()){
            double weight = static_cast<double>(attr_map.second.size()) / dataset.size();
            weighted_childGini += weight * calculateGini(attr_map.second);
        }
    }
    return parentGini - weighted_childGini;
}


string DecisionTree::selectBestAttribute(const vector<Car>& dataset, vector<string>& attributes, bool isInfo_gain){
    if(isInfo_gain){
        double max_gain = 0.0;
        string best_attribute = attributes[0];
        for(auto attr : attributes){
            double gain = calculateInfoGain(dataset, attr);
            if(gain > max_gain){
                max_gain = gain;
                best_attribute = attr;
            }
        }
        return best_attribute;
    }
    else{
        double max_gain = 0.0;
        string best_attribute = attributes[0];
        for(auto attr : attributes){
            double gain = giniGain(dataset, attr);
            if(gain > max_gain){
                max_gain = gain;
                best_attribute = attr;
            }
        }
        return best_attribute;
    }
}


TreeNode* DecisionTree::buildTree(const vector<Car>& dataset, vector<string>& attributes, bool isInfo_gain, bool isRandomSelection){
    if(dataset.empty()) return nullptr;

    map<string, int> class_count;
    for(auto car : dataset){
        class_count[car.class_label]++;
    }
    if(class_count.size() == 1){   //if all examples belong to the same class
        return new TreeNode(class_count.begin()->first, true);
    }

    if(attributes.empty()){ //if no attributes left, return the majority class
        return new TreeNode(finfMajorityClass(dataset), true);
    }

    string best_attribute;
    if(!isRandomSelection)
        best_attribute = selectBestAttribute(dataset, attributes, isInfo_gain);

    if(isRandomSelection){
        auto ranked_attributes = rankAttributes(dataset, attributes, isInfo_gain);
        int topCount = min(3, static_cast<int>(ranked_attributes.size()));

        
        uniform_int_distribution<int> dist(0, topCount - 1);
        int random_index = dist(gen);

        //cout<<"Random index: "<<random_index<<"\n";
        best_attribute = ranked_attributes[random_index].first;
    }

    TreeNode* node = new TreeNode(best_attribute);
    vector<string> new_attributes = attributes;
    auto it = find(new_attributes.begin(), new_attributes.end(), best_attribute);
    if(it != new_attributes.end()) new_attributes.erase(it);

    //split dataset and recurse
    map<string, vector<Car>> attribute_map;
    for(auto car : dataset){    
        if(best_attribute == "buying") attribute_map[car.buying].push_back(car);
        else if(best_attribute == "maint") attribute_map[car.maint].push_back(car);
        else if(best_attribute == "doors") attribute_map[car.doors].push_back(car);
        else if(best_attribute == "persons") attribute_map[car.persons].push_back(car);
        else if(best_attribute == "lug_boot") attribute_map[car.lug_boot].push_back(car);
        else if(best_attribute == "safety") attribute_map[car.safety].push_back(car);
    }

    for(auto attr_map : attribute_map){
        if(attr_map.second.empty()){
            node->children[attr_map.first] = new TreeNode(finfMajorityClass(dataset), true);
        }
        else
            node->children[attr_map.first] = buildTree(attr_map.second, new_attributes, isInfo_gain, isRandomSelection);
    }

    return node;
}


vector<pair<string, double>> DecisionTree::rankAttributes(const vector<Car>& dataset, const vector<string>& attributes, bool isInfo_gain){
    vector<pair<string, double>> ranked_attributes;

    for(auto attr : attributes){
        double gain;
        if(isInfo_gain) gain = calculateInfoGain(dataset, attr);
        else gain = giniGain(dataset, attr);
        ranked_attributes.push_back({attr, gain});
    }

    sort(ranked_attributes.begin(), ranked_attributes.end(), 
        [](const pair<string, double>& a, const pair<string, double>& b){
        return a.second > b.second;
    });
    return ranked_attributes;
}





//public functions

void DecisionTree::train(const vector<Car>& dataset, bool isInfo_gain){
    if(dataset.empty()) return;

    majorityClass = finfMajorityClass(dataset);
    vector<string> attributes = {"buying", "maint", "doors", "persons", "lug_boot", "safety"};
    root = buildTree(dataset, attributes, isInfo_gain, false);
}

void DecisionTree::train_randomSelection(const vector<Car>& dataset, bool isInfo_gain){
    if(dataset.empty()) return;

    majorityClass = finfMajorityClass(dataset);
    vector<string> attributes = {"buying", "maint", "doors", "persons", "lug_boot", "safety"};
    root = buildTree(dataset, attributes, isInfo_gain, true);
}


string DecisionTree::predict(const Car& car){
    TreeNode* current = root;
    while(!current->isLeaf && !current->children.empty()){
        //cout << "Current node attribute: " << current->attribute << "\n";
        string attr_value = current->attribute;
        if(attr_value == "buying") current = current->children[car.buying];
        else if(attr_value == "maint") current = current->children[car.maint];
        else if(attr_value == "doors") current = current->children[car.doors];
        else if(attr_value == "persons") current = current->children[car.persons];
        else if(attr_value == "lug_boot") current = current->children[car.lug_boot];
        else if(attr_value == "safety") current = current->children[car.safety];

        if (current == nullptr) {
            //cout << "current node is nullptr\n";
            return majorityClass;
        }
    }
    return current->class_label;
}