#include <bits/stdc++.h>
#include "City.h"

using namespace std;

class TSPSolver {
private:
    // void twoOptSwap(vector<int>& tour, int i, int k);
    vector<City> cities;
    int city_number;

public:
    TSPSolver(const vector<City>& cities);

    vector<int> nearestNeighbourTour();
    vector<int> cheapestInsertionTour();
    vector<int> nearestInsertionTour();


    vector<int> twoOptTour(const vector<int> &initialTour);
    vector<int> nodeSwapTour(const vector<int> &initialTour);
    vector<int> nodeShiftTour(const vector<int> &initialTour);
    


};



TSPSolver::TSPSolver(const vector<City> &cities) {
    this->cities = cities;
    this->city_number = cities.size();   
}

vector<int> TSPSolver::nearestNeighbourTour() {
    vector<int> tour;
    vector<bool> visited(city_number, false);
    int current_city = 0;
    visited[current_city] = true;
    tour.push_back(current_city);

    for (int i = 0; i < city_number; i++) {
        current_city = tour.back();
        double nearest_dist = numeric_limits<double>::max();
        int nearest_city = -1;

        for(int j = 0; j < city_number; j++) {
            if(!visited[j]){
                double dist = calculateDistance(cities[current_city], cities[j]);
                if(dist < nearest_dist){
                    nearest_dist = dist;
                    nearest_city = j;
                }
            }
        }
        if(nearest_city > -1){
            visited[nearest_city] = true;
            tour.push_back(nearest_city);
        }
        else break; // no more cities to visit      

    }
    return tour;
}

vector<int> TSPSolver::cheapestInsertionTour() {
    vector<bool> included(city_number, false);
    int current_city = 0;
    included[current_city] = true;
    vector<int> tour = {current_city, current_city};  // Start and end with the initial city

    for(int i=0; i<city_number; i++){
        double cheapestIncrease = numeric_limits<double>::max();
        int cheapestCity = -1;
        int position = 1;

        for(int j=0; j<city_number; j++){
            if(!included[j]){
                for(int k=1; k<tour.size(); k++){
                    double increase = calculateDistance(cities[tour[k-1]], cities[j]) 
                                    + calculateDistance(cities[j], cities[tour[k]])
                                    - calculateDistance(cities[tour[k-1]], cities[tour[k]]);
                    if(increase < cheapestIncrease){
                        cheapestIncrease = increase;
                        cheapestCity = j;
                        position = k;
                    }
                }
            }
        }
        if(cheapestCity > -1){
            included[cheapestCity] = true;
            tour.insert(tour.begin() + position, cheapestCity);
        }
        else break; // no more cities to visit
        
    }
    //cout << "last city: " << tour.back() << endl;
    tour.pop_back(); // remove the last city
    return tour;
}

vector<int> TSPSolver::nearestInsertionTour(){
    vector<int> tour;
    vector<bool> included(city_number, false);

    int start_city = 0, next_city = -1;
    double min_dist = numeric_limits<double>::max();
    for(int i = 0; i < city_number; i++){
        if(i != start_city){
            double dist = calculateDistance(cities[start_city], cities[i]);
            if(dist < min_dist){
                min_dist = dist;
                next_city = i;
            }
        }
    }
    tour.push_back(start_city);
    tour.push_back(next_city);
    included[start_city] = true;
    included[next_city] = true;
    tour.push_back(start_city); //close the loop

    for(int i=2; i<city_number; i++){  //find nearest unvisited city
        int nearest_city = -1;
        double neraest_dist = numeric_limits<double>::max();

        for(int j=0; j<city_number; j++){
            if(!included[j]){
                for(int k=0; k<tour.size()-1; k++){
                    double dist = calculateDistance(cities[j], cities[tour[k]]);
                    if(dist < neraest_dist){
                        neraest_dist = dist;
                        nearest_city = j;
                    }
                }
            }
        }

        double min_increase = numeric_limits<double>::max();
        int best_position = -1;
        for(int k=1; k<tour.size(); k++){   //find the best position to insert the nearest city
            double increase_dist =    calculateDistance(cities[tour[k-1]], cities[nearest_city]) 
                                    + calculateDistance(cities[nearest_city], cities[tour[k]])
                                    - calculateDistance(cities[tour[k-1]], cities[tour[k]]);
            if(increase_dist < min_increase){
                min_increase = increase_dist;
                best_position = k;
            }
        }
        tour.insert(tour.begin() + best_position, nearest_city);
        included[nearest_city] = true;
    }
    tour.pop_back(); //remove the last city (0)
    return tour;
}


vector<int> TSPSolver::twoOptTour(const vector<int> &initialTour) {
    vector<int> tour = initialTour;
    bool improvement = true;
    while(improvement){
        improvement = false;
        for(int i = 1; i < city_number - 1; i++){
            for(int k = i + 1; k < city_number-1; k++){
                double delta =  - calculateDistance(cities[tour[i-1]], cities[tour[i]]) 
                                - calculateDistance(cities[tour[k]], cities[tour[k+1]]) 
                                + calculateDistance(cities[tour[i-1]], cities[tour[k]]) 
                                + calculateDistance(cities[tour[i]], cities[tour[k+1]]);

                if(delta < -0.000000000001){
                    reverse(tour.begin() + i, tour.begin() + k + 1);  //reverse [i,K+1) => [i, k]
                    improvement = true;
                    //cout << "Improvement: " << delta <<" i: "<<i<<" k: "<<k << endl;
                }
            }
        }
    }
    return tour;
}


vector<int> TSPSolver::nodeShiftTour(const vector<int> &initialTour){
    vector<int> tour = initialTour;
    bool improvement = true;

    while(improvement){
        improvement = false;

        for(int i=1; i<city_number; i++){
            for(int j=1; j<city_number; j++){
                if(i == j) continue;
                vector<int> new_tour = tour;
                int shift_node = new_tour[i];
                new_tour.erase(new_tour.begin() + i);
                new_tour.insert(new_tour.begin() + j, shift_node);

                double old_length = calculateTourLength(tour, cities);
                double new_length = calculateTourLength(new_tour, cities);
                if(new_length - old_length < -0.00000000001){
                    tour = new_tour;
                    improvement = true;
                    //cout << "Improvement: " << new_length - old_length << endl;
                }
            }
        }
    }

    return tour;
}

vector<int> TSPSolver::nodeSwapTour(const vector<int> &initialTour){
    vector<int> tour = initialTour;
    bool improvement = true;

    while(improvement){
        improvement = false;

        for(int i=1; i<city_number-1; i++){
            for(int j=i+1; j<city_number; j++){
                if(i == j) continue;
                vector<int> new_tour = tour;
                swap(new_tour[i], new_tour[j]);

                double old_length = calculateTourLength(tour, cities);
                double new_length = calculateTourLength(new_tour, cities);
                if(new_length - old_length < -0.00000000001){
                    tour = new_tour;
                    improvement = true;
                    //cout << "Improvement: " << new_length - old_length << endl;
                }
            }
        }
    }

    return tour;
}
