#include <iostream>
#include <chrono>
#include <vector>

using namespace std;

int main(){
	
	int size = 2000000;
	for(int i = 1; i < 20;i++)
	{
		vector<int> v;
		v.resize(size*i);
		v.reserve(2*size*i);
		const auto start = std::chrono::steady_clock::now();
		v.insert(v.begin(),42);
		const auto end = std::chrono::steady_clock::now();
		const std::chrono::duration<double> diff = end - start;
		cout << "Inserting at v.begin() for size " << v.size() << " " << diff.count() << endl;
	}	
}
