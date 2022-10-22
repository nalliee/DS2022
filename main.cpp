#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <cmath>
#include "AvlTree.h"

using namespace std;

int main() {

    clock_t start, end;
    long time = 0;
    
    AvlTree<int> T1;
    vector<int> list1 {5000, 50000, 500000, 5000000, 50000000};

    for(size_t i{0}; i <= list1.size(); ++i)
    {
        int k1 = list1[i];
        int k2 = k1;

        for(size_t j{0}; i <= k1; ++j)
        {
            T1.insert(j);
        }
        start = clock();
        T1.printComparable(k1,k2);
        end = clock();

        time = (end-start) / CLOCKS_PER_SEC;
        cout << "The process costs: " << time << " s." << endl;
    }

    AvlTree<int> T2;
    vector<int> list2 {int(pow(2,10)), int(pow(2,20)), int(pow(2,30)), int(pow(2,40))};

    for(size_t i{0}; i < list2.size(); ++i)
    {
        int k1 = list2[i];
        int k2 = log2(k1);

        for(size_t j{0}; j <= k1; ++j)
        {
            T2.insert(j);
        }

        start = clock();
        T2.printComparable(k1,k2);
        end = clock();

        time = (end-start) / CLOCKS_PER_SEC;
        cout << "The process costs: " << time << " s." << endl;
    }

    return 0;
}