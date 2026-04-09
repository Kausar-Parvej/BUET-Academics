#ifndef CITY_H
#define CITY_H

#include <bits/stdc++.h>
#include <vector>
using namespace std;

struct City {
    int id;
    double x, y;

    City(int id, double x, double y){
        this->id = id;
        this->x = x;
        this->y = y;
    }
};

double calculateDistance(const City& city1, const City& city2) {
    return sqrt(pow(city1.x - city2.x, 2) + pow(city1.y - city2.y, 2));
}

double calculateTourLength(const vector<int>& tour, const vector<City>& cities) {
    double length = 0;
    for (int i = 0; i < tour.size(); i++) {
        length += calculateDistance(cities[tour[i]], cities[tour[(i + 1) % tour.size()]]);
    }
    return length;
}

#endif