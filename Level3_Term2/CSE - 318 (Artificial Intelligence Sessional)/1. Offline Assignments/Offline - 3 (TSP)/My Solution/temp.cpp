#include <bits/stdc++.h>
using namespace std;

int get_random_number() {
  std::random_device rd;
  std::mt19937 generator(rd());

  // Lambda value for the Poisson distribution
  double lambda = 100001.234;
  std::poisson_distribution<int> poissonDist(lambda);
  return poissonDist(generator);
}

int main() {
    cout << "Hello, World!" << endl;
    for(int i=0; i<10; i++)
        cout << get_random_number() << endl;
    cout << get_random_number() << endl;

    return 0;
}