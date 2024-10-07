## CSCI 114 Lab 4 Measuring Runtime

In this lab we will practice measuring the time it takes for pieces of code to run. The goal is to verify or prove that the code has a particular runtime e.g. O(n) or O(n^2).

The basic process is as follows:

* log the start time (using the `<chrono>` library in C++
* Perform some work that depends on an input size `n`
* log the end time
* Calculate the elapsed time
* Increase `n` and repeat the process, collecting enough data points to curve fit the relationship between `n` and the elapsed time

### Part 1

For part 1 you will replicate the results of the experiment described in the lecture slides: "show the runtime of inserting at the begining of a <vector> is O(n)"

Here is the code:

```
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
```
Save, compile and run this code (you can call it vector_test.cpp). Copy-and-paste the `n` and runtime values into Google Sheets to do the linear fit using the LINEST function.

### Part 2

For this part we will prove that iterating through a linked list *without* an iterator is O(n^2). The `<list>` doubly-linked list from C++ smartly does not give a `.at()` implementation. We could use our own linked list implementation, but we can also simulate the behavior by starting an iterator over each time we need to access an index in the linked list.

Here is the starter code:

```
#include <iostream>
#include <chrono>
#include <list>

using namespace std;

template <typename T>
T at(list<T>& ll, size_t idx)
{
	//implement an access-by-index for a linked list

	//1. Use auto to create an iterator for the list ll and set it to the .begin() iterator
	
	//2. Increment the iterator idx times
	
	//3. Return *it
	
	
}

int main(){
	size_t size = 1000;
	
	for(int x = 0; x < 20; x++)
	{
		list<int> my_list;
		
		//1. Resize my_list to have size*x items
		
		//2. log the start time (see part 1)
		
		//3. Use a for loop to iterate through all indexs of my_list by calling 
		//   at<int>(my_list, i)
		
		//4. log the end time and calculate the diff

		cout << "Iterating linked list for size " << my_list.size() << ": ";
		cout << diff.count() << endl;
	}
}
```
Fill in/finish the code as specified in the comments. After running the code, copy-paste into Google sheets. The easiest way to get the fit is with a scatter chart and then adding a polynomial of order 2 trendline. The LINEST function can do it too (see below) Does this data fit O(n^2)?

`LINEST` for polynomial degree 2:

```
=LINEST(y_data,ARRAYFORMULA(x_data^{1,2}),true,true)
```

### Part 3

Now we can show that iterators fix this problem with linked lists:

```
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
```

### Part 4

Now we can look at sorting. We're going to take a closer look at sorting shortly, but we can use built-in sorting algoritms here. If you include `<algorithm>` there is a `sort()` function that will work with vectors. The documentation claims the algorithm runs in O(n * log n), can you prove that?

```
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

		cout << "Sorting vector for size " << v.size() << ": " << diff.count() << endl;
	}	
}
```
Once you have values for this test, there is a bit of a problem: the fitting algorithms don't have a selection for n*log(n). However, if we have a relationship in the form y = n \* log(n) could you convert it into a linear relationship? Can you prove sorting is O(n\*log n)?

### Deliverable

Create a Google Sheet with a tab for each part. Include your data, the output of the LINEST() function and a scatter chart with trendline for each.
