#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include "Sorting.h"

using namespace std;

vector <int> order(int n, double i) {
    vector <int> v;
    int range;
    int t;
    srand((unsigned int) time(0));

    if(i < 0.5) {
        range = n * sqrt(i);
        t = rand() % (n-2*range);
        for(int j = 1; j < t; j++) {
            v.push_back(j);
        }
        for(int j = t; j < t+range; ++j) {
            v.push_back(j + range);
        }
        for(int j = t+range; j < t + 2*range; ++j) {
            v.push_back(j - range);
        }
        for(int j = t + 2*range; j < n; ++j) {
            v.push_back(j);
        }
    }
    else {
        range = n * sqrt(1 - i);
        t = rand() % (n-range);
        for(int j = 1; j < t; j++) {
            v.push_back(n-j);
        }
        for(int j = t; j < t+range; j++) {
            v.push_back(n-j-range);
        }
        for(int j = t+range; j < t + 2*range; j++) {
            v.push_back(n-j+range);
        }
        for(int j = t + 2*range; j < n; j++) {
            v.push_back(n-j);
        }
    }
    return v;
}

int main() {

    vector <double> efficiency {0.01, 0.1, 0.9, 0.99};
    vector <int> size {10000, 100000, 1000000};

    for(auto &n : size) {
        cout << "\n\tsize: " << n << endl;
        for(auto &i : efficiency) {
            cout << "\nefficiency: " << i << endl;
            clock_t start1, end1, start2, end2;
            double time;

            vector <int> v1 = order(n, i);
            start1 = clock();
            heapsort(v1);
            end1 = clock();

            cout << "heapsort: " << (double)(end1 - start1) / CLOCKS_PER_SEC << " seconds." << endl;

            vector <int> v2 = v1;
            start2 = clock();
            quicksort(v2);
            end2 = clock();
    
            cout << "quicksort: " << (double)(end2 - start2) / CLOCKS_PER_SEC << " seconds." << endl;
        }
    }

    return 0;

}