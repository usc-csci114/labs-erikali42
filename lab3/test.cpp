#include <iostream>
#include <iomanip>
#include "ArrayList.h"

using namespace std;


template <typename T>
void printList(List<T>& list)
{
	size_t i;
	for(i=0;i<list.size()-1;i++)
	{
		cout << list.at(i) << ",";
	}
	cout << list.at(i) << endl;
}


int main(int argc, char* argv[])
{
	ArrayList<int> list;
	//or LinkedList<int> list;
	//this is an example of inheritance. We can update our code
	//to use a different list by changing one line of code.
	
	cout << "List is size: " << list.size() << endl;
	cout << boolalpha << "List.empty() is " << list.empty() << endl;
	
 	list.append(1);
	list.append(2);
	list.append(3);
	list.append(4);
	list.append(5);
	
	printList<int>(list);
	
	cout << "List is size: " << list.size() << endl;
	cout << boolalpha << "List.empty() is " << list.empty() << endl;
	
	list.insert(0,99);
	
	printList<int>(list);
	
	list.remove(list.size()/2);
	
	printList<int>(list);
}
