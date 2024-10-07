#include <iostream>
#include <chrono>
#include <list>

using namespace std;


int main(){
	size_t size = 100000;
	
	for(int x = 0; x < 20; x++)
	{
		list<int> my_list;
		
		//1. Resize my_list to have size*x items
		
		//2. log the start time (see part 1)
		
		//3. Use a for loop with an iterator to iterate through all items in the list
		//   The body of the for loop can be empty
		
		//4. log the end time and calculate the diff

		cout << "Iterating linked list for size " << my_list.size() << ": ";
		cout << diff.count() << endl;
	}
}
