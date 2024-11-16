#include <iostream>
#include <vector>
#include <queue>
#include <list>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;

void fillrand(vector<int>& v) {
    for (int& num : v) {
        num = rand() % 1000; // Random numbers between 0 and 999
    }
}

int main() {
    // random vector size 100
    vector<int> v(100);
    fillrand(v);

    // priority queu from the bector
    priority_queue<int> pq(v.begin(), v.end());

    // make a list and sort the elements
    list<int> sortedList;
    while (!pq.empty()) {
        sortedList.push_front(pq.top()); // Push max to the front
        pq.pop();
    }

    // print the sorted list
    cout << "Sorted list:" << endl;
    for (int n : sortedList) {
        cout << n << " ";
    }
    cout << endl;

    // measuring time it takes to sort vector while increasing the size
    // looking at this, as size increases by a factor of 10, time also increases by a factor of 10
    cout << "Measuring performance..." << endl;
    for (size_t size = 100; size <= 10000000; size *= 10) {
        vector<int> largeVec(size);
        fillrand(largeVec);

        auto start = chrono::high_resolution_clock::now();
        priority_queue<int> largePQ(largeVec.begin(), largeVec.end());
        while (!largePQ.empty()) {
            largePQ.pop();
        }
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed = end - start;

        cout << "Size: " << size << ", Time: " << elapsed.count() << " seconds" << endl;
    }

    return 0;
}
