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
		//2. Reserve 2*size*i (so we don't resize)
		//3. log the start time

		sort(v.begin(),v.end());
		
		//4. log the stop time and calculate the diff

		cout << "Sorting vector for size " << v.size() << ": ";
		cout << diff.count() << endl;
	}	
}
