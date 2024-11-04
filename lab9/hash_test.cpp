#include <utility>
#include <vector>
#include <map>
#include <iostream>
#include <string>
#include <random>
#include "hashtable.h"

using namespace std;

int main(int argc, char* argv[])
{
	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(1, 1000);
	  
	HashTable<string, int> t;
	t.insert("hello", 5);
	cout << t.find("hello") << endl;
	t.remove("hello");
	for(char c='a'; c<='z'; c++)
	{
		string s = "key-";
		int val = distribution(generator);
		cout << "Inserting " << c << " -> " << val << endl;
		t.insert(s+c, val);
	}
	for(char c='a'; c<='z'; c++)
	{
		string s = "key-";
		int val = t.find(s+c);
		cout << "Found " << c << " -> " << val << endl;
	}
}