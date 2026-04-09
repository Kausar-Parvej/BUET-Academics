#include <bits/stdc++.h>
#include "TSPSolver.cpp"
#include <chrono>

using namespace std;

auto start_time = chrono::high_resolution_clock::now();

long long get_time() {
    auto current_time = chrono::high_resolution_clock::now();
    return chrono::duration_cast<chrono::milliseconds>(current_time - start_time).count();
}



vector<City> paserFile(const string &filename) {
    ifstream file(filename);
    vector<City> cities;
    string line;
    bool node_coord = false;

    while (getline(file, line)) {
        //cout<<line<<"\n";
        if(line == "NODE_COORD_SECTION") {
            node_coord = true;
            continue;
        }
        if(line == "EOF" || line == "EOF\n") break;
        if(node_coord) {
            istringstream iss(line);
            int id;
            double x, y;
            iss >> id >> x >> y;
            cities.push_back({id-1, x, y}); //id starts from 1
        }
    }
    return cities;
}

void saveTour_toFile(const string &filename, const vector<int> &tour, const vector<City> &cities) {
    //csv file
    ofstream file(filename);
    file << "File,Construction_Method,Time(ms),Perturbative_Method,Time(ms), Tour_Cost\n";
    for(int i=0; i<tour.size(); i++) {
        City city = cities[tour[i]];
        file << city.id << "," << city.x << "," << city.y << "\n";
        //cout << city.id << " ->";
    }
    file.close();
}





int main(){
    std::vector<std::string> fileNames = {
    "berlin52.tsp",
    "bier127.tsp",
    "ch130.tsp",
    "eil51.tsp",
    "eil76.tsp",
    "eil101.tsp",
    "kroA100.tsp",
    "kroB100.tsp",
    "kroC100.tsp",
    "kroD100.tsp",
    "kroE100.tsp",
    "lin105.tsp",
    "pr76.tsp",
    "pr124.tsp",
    "pr144.tsp",
    "rat99.tsp",
    "st70.tsp",
    "ch150.tsp",
    "lin318.tsp",
    "a280.tsp",
    "rat195.tsp"
    };

    ofstream out_file("Report.csv");
    out_file << "File,Construction_Method,Time,Perturbative_Method,Time, Tour_Cost\n";
    vector<int> tour1;
    vector<int> tour2;
    vector<int> tour3;

    vector<int> tour_p;

    double cost1, cost2, cost3;
    unsigned long long time_diff, time1, time2;


    for(auto filename : fileNames){
        vector<City> cities = paserFile("Benchmark_data/"+filename);

        if(cities.empty()) {
            cout << "Error: file not found or empty "<< filename << "\n";
            continue;
        }

        TSPSolver solver(cities);

        cout << "Solving: " << filename << "...\n";

        //-------Nearest Neighbour---------
        time1 = get_time();
        tour1 = solver.nearestNeighbourTour();
        cost1 = calculateTourLength(tour1,cities);
        time2 = get_time();
        time_diff = time2 - time1;
        out_file<<filename<<",Nearest_Neighbour,"<<time_diff<<",None,"<<0.0<<","<<cost1<<"\n";
        //cout<<time_diff<<"\n";

        tour_p = solver.nodeSwapTour(tour1);
        cost1 = calculateTourLength(tour_p,cities);
        time1 = get_time();
        out_file<<filename<<",Nearest_Neighbour,"<<time_diff<<",Node_Swap,"<<(time1-time2)<<","<<cost1<<"\n";

        tour_p = solver.nodeShiftTour(tour1);
        cost1 = calculateTourLength(tour_p,cities);
        time2 = get_time();
        out_file<<filename<<",Nearest_Neighbour,"<<time_diff<<",Node_Shift,"<<(time2-time1)<<","<<cost1<<"\n";


        tour_p = solver.twoOptTour(tour1);
        cost1 = calculateTourLength(tour_p,cities);
        time1 = get_time();
        out_file<<filename<<",Nearest_Neighbour,"<<time_diff<<",2-opt,"<<(time1-time2)<<","<<cost1<<"\n";


        ///*
        
        //------------Cheapest Insertion------------
        tour2 = solver.cheapestInsertionTour();
        cost2 = calculateTourLength(tour2,cities);
        time2 = get_time();
        time_diff = time2 - time1;
        out_file<<filename<<",Cheapest_Insertion,"<<time_diff<<",None,"<<0.0<<","<<cost2<<"\n";

        tour_p = solver.nodeSwapTour(tour2);
        cost2 = calculateTourLength(tour_p,cities);
        time1 = get_time();
        out_file<<filename<<",Cheapest_Insertion,"<<time_diff<<",Node_Swap,"<<(time1-time2)<<","<<cost2<<"\n";

        tour_p = solver.nodeShiftTour(tour2);
        cost2 = calculateTourLength(tour_p,cities);
        time2 = get_time();
        out_file<<filename<<",Cheapest_Insertion,"<<time_diff<<",Node_Shift,"<<(time2-time1)<<","<<cost2<<"\n";


        tour_p = solver.twoOptTour(tour2);
        cost2 = calculateTourLength(tour_p,cities);
        time1 = get_time();
        out_file<<filename<<",Cheapest_Insertion,"<<time_diff<<",2-opt,"<<(time1-time2)<<","<<cost2<<"\n";


        //------------Nearest Insertion-------------
        tour3 = solver.cheapestInsertionTour();
        cost3 = calculateTourLength(tour3,cities);
        time2 = get_time();
        time_diff = time2 - time1;
        out_file<<filename<<",Cheapest_Insertion,"<<time_diff<<",None,"<<0.0<<","<<cost3<<"\n";

        tour_p = solver.nodeSwapTour(tour3);
        cost3 = calculateTourLength(tour_p,cities);
        time1 = get_time();
        out_file<<filename<<",Cheapest_Insertion,"<<time_diff<<",Node_Swap,"<<(time1-time2)<<","<<cost3<<"\n";

        tour_p = solver.nodeShiftTour(tour3);
        cost3 = calculateTourLength(tour_p,cities);
        time2 = get_time();
        out_file<<filename<<",Cheapest_Insertion,"<<time_diff<<",Node_Shift,"<<(time2-time1)<<","<<cost3<<"\n";


        tour_p = solver.twoOptTour(tour3);
        cost3 = calculateTourLength(tour_p,cities);
        time1 = get_time();
        out_file<<filename<<",Cheapest_Insertion,"<<time_diff<<",2-opt,"<<(time1-time2)<<","<<cost3<<"\n";
        //*/

    }

    out_file.close();
    cout <<"------------> Done, check Report.csv<-------------\n";
    return 0;


}

