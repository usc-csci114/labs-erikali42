#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int main() {
    vector<int> numbers;
    stack<int> mystack;
    int num;

    // Read integers from the user until they hit ctrl d 
    cout << "Enter integers (Ctrl-D to end):" << endl;
    while (cin >> num) {
        numbers.push_back(num); // add number to the vector
    }

    sort(numbers.begin(), numbers.end()); // sort the vector

    // Print the vector in order
    cout << endl << "Vector in order:" << endl;
    for (int n : numbers) {
        cout << n << " ";
        mystack.push(n); // Push to stack, so that the first numbers in the vector go to the bottom of the stack
    }
    cout << endl;

    // Print in reverse order using the stack
    cout << "Vector in reverse order:" << endl;
    while (!mystack.empty()) { // printing from the top of the stack 
        cout << mystack.top() << " ";
        mystack.pop();
    }
    cout << endl;

    return 0;
}
