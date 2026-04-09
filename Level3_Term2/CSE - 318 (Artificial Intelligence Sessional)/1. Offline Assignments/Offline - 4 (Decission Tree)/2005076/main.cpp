#include<bits/stdc++.h>
#include <iomanip>
using namespace std;

#include "decision_tree.cpp"

string data_file = "car evaluation dataset/car.data";
int runTimes = 20;
double train_ratio = 0.8;
double test_ratio = 0.2;

double calculateAccuracy(const vector<Car>& testSet, DecisionTree& tree){
    int correct = 0;
    for(auto car : testSet){
        string predicted = tree.predict(car);
        if(predicted == car.class_label) correct++;
        //else cout<<predicted<<" "<<car.class_label<<"\n";
    }
    //cout<<"Accuracy: "<<static_cast<double>(correct) / testSet.size() * 100<<"\n";
    return static_cast<double>(correct) / testSet.size() * 100;
}


void print_result(double avg_accuracy_bestInfoGain, double avg_accuracy_bestGini,
                  double avg_accuracy_randInfoGain, double avg_accuracy_randGini) {
    cout << std::fixed << std::setprecision(2); // Set precision for percentages
    cout << "+------------------------------------------------------------------------------+\n";
    cout << "| Attribute selection strategy       | Information gain  | Gini impurity       |\n";
    cout << "+------------------------------------------------------------------------------+\n";
    cout << "| Always select the best attribute   | "
         << setw(16) << avg_accuracy_bestInfoGain << "% | "
         << setw(12) << avg_accuracy_bestGini << "%       |\n";
    cout <<"|                                                                              |\n";
    cout << "| Select one randomly from the top 3 | "
         << setw(16) << avg_accuracy_randInfoGain << "% | "
         << setw(12) << avg_accuracy_randGini << "%       |\n";
    cout << "+------------------------------------------------------------------------------+\n\n";
}



int main(){
    vector<Car> dataSet = parse_dataSet(data_file);
    int data_size = dataSet.size();

    double avg_accuracy_bestInfoGain = 0.0;
    double avg_accuracy_bestGini = 0.0;
    double avg_accuracy_randInfoGain = 0.0;
    double avg_accuracy_randGini = 0.0;

    //random seed foe reproducibility
    random_device rd;
    mt19937_64 g(rd());
    //mt19937_64 g(87);

    cout << "\nRunning " << runTimes << " times.......\n\n";


    for(int i = 0; i < runTimes; i++){
        shuffle(dataSet.begin(), dataSet.end(),g);

        //cout<<"running "<<i<<"\n";

        int train_size = static_cast<int> (data_size * train_ratio);
        vector<Car> trainSet(dataSet.begin(), dataSet.begin() + train_size);
        vector<Car> testSet(dataSet.begin() + train_size, dataSet.end());


        //always select the best attribute
        DecisionTree tree_bestInfoGain, tree_bestGini;
        tree_bestInfoGain.train(trainSet, true);
        tree_bestGini.train(trainSet, false);

        avg_accuracy_bestInfoGain += calculateAccuracy(testSet, tree_bestInfoGain);
        avg_accuracy_bestGini += calculateAccuracy(testSet, tree_bestGini);


        //randomly select from the top three attribute
        DecisionTree tree_randInfoGain, tree_randGini;
        tree_randInfoGain.train_randomSelection(trainSet, true);
        tree_randGini.train_randomSelection(trainSet, false);

        avg_accuracy_randInfoGain += calculateAccuracy(testSet, tree_randInfoGain);
        avg_accuracy_randGini += calculateAccuracy(testSet, tree_randGini);


    }

    avg_accuracy_bestInfoGain /= runTimes;
    avg_accuracy_bestGini /= runTimes;
    avg_accuracy_randInfoGain /= runTimes;
    avg_accuracy_randGini /= runTimes;

    print_result(avg_accuracy_bestInfoGain, avg_accuracy_bestGini, avg_accuracy_randInfoGain, avg_accuracy_randGini);

    return 0;

}
