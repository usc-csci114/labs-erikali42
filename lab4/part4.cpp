#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
	
	int size = 2000000;
	for(int i = 1; i < 20;i++)
	{
		vector<int> v;
		//1. Resize the vector to size*i
		for (int j = 0; j < size * i; j++) {
            v.push_back(rand() % 100);  // Add random numbers to the vector
        }
		//2. Reserve 2*size*i (so we don't resize)
		v.reserve(2 * size * i);

		//3. log the start time
		const auto start = chrono::steady_clock::now();

		sort(v.begin(),v.end());
		
		//4. log the stop time and calculate the diff
		const auto end = chrono::steady_clock::now();
        const chrono::duration<double> diff = end - start;

		// cout << "Sorting vector for size " << v.size() << ": ";
		cout << diff.count() << endl;
	}	
}
