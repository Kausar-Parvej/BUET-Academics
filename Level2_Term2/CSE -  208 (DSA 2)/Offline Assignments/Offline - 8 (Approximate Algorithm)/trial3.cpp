
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <climits>

using namespace std;

const int MAX_N = 16; // Maximum number of cities, adjust as needed
const int INF = INT_MAX / 2; // Represents infinity

int numCities; // Number of cities
int graph[MAX_N][MAX_N]; // Distance matrix
vector<vector<int>> dp; // DP table
vector<int> bestPath; // Stores the best path found

// Function to compute the TSP using dynamic programming and bitmasking
int tsp(int currentCity, int visited) {
    if (visited == (1 << numCities) - 1) {
        // All cities have been visited, return to the starting city
        bestPath.push_back(0);
        return graph[currentCity][0];
    }

    // If the result is already computed, return it
    if (dp[currentCity][visited] != -1) {
        return dp[currentCity][visited];
    }

    int minCost = INF;
    int nextCityIdx = -1;

    for (int nextCity = 0; nextCity < numCities; ++nextCity) {
        if (!(visited & (1 << nextCity))) { // Check if nextCity is not visited
            int newVisited = visited | (1 << nextCity);
            int cost = graph[currentCity][nextCity] + tsp(nextCity, newVisited);
            if (cost < minCost) {
                minCost = cost;
                nextCityIdx = nextCity;
            }
        }
    }

    // Memoize the result and update the best path
    dp[currentCity][visited] = minCost;
    if (nextCityIdx != -1) {
        bestPath.push_back(nextCityIdx);
    }

    return dp[currentCity][visited];
}

int main() {
    cout << "Enter the number of cities: ";
    cin >> numCities;

    cout << "Enter the distance matrix (enter -1 for infinity):\n";
    for (int i = 0; i < numCities; ++i) {
        for (int j = 0; j < numCities; ++j) {
            cin >> graph[i][j];
        }
    }

    // Initialize the DP table
    dp.assign(numCities, vector<int>(1 << numCities, -1));

    int minCost = tsp(0, 1); // Start from city 0 (the starting city)

    cout << "Minimum Cost: " << minCost << endl;

    cout << "Best Path: ";
    for (int city : bestPath) {
        cout << city << " ";
    }
    cout << "0" << endl; // Return to the starting city

    return 0;
}
