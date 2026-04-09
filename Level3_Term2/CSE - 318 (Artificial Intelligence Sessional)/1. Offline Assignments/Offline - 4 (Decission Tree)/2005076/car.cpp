#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;


class Car {
public:
    string buying;
    string maint;
    string doors;
    string persons;
    string lug_boot;
    string safety;
    string class_label;


    Car(vector<string>& attributes){
        if(attributes.size() == 7){
            buying = attributes[0];
            maint = attributes[1];
            doors = attributes[2];
            persons = attributes[3];
            lug_boot = attributes[4];
            safety = attributes[5];
            class_label = attributes[6];
        }
    }
};

vector<Car> parse_dataSet(string file_name){
    vector<Car> carData;
    ifstream file(file_name);
    string line;

    while(getline(file, line)){
        vector<string> attributes(7);
        stringstream ss(line);

        for(int i = 0; i < 7; i++){
            getline(ss, attributes[i], ',');
        }

        Car car(attributes);
        carData.push_back(car);
    }
    return carData;
}

// int main(){
//     vector<Car> carData = parse_dataSet("car evaluation dataset/car.data");
//     for(int i = 0; i < carData.size(); i++){
//         cout    << carData[i].buying << " " << carData[i].maint << " " << carData[i].doors << " " << carData[i].persons 
//                 << " " << carData[i].lug_boot << " " << carData[i].safety << " " << carData[i].class_label << endl;
//     }
//     cout << carData.size() << endl;
//     return 0;
// }