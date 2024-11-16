#include <iostream>
#include <stack>
#include <string>

using namespace std;

// function to check if brackets match 
bool isMatchingPair(char open, char close) {
    return (open == '(' && close == ')') ||
           (open == '{' && close == '}') ||
           (open == '[' && close == ']') ||
           (open == '<' && close == '>');
}

int main() {
    string input;
    stack<pair<char, int> > bracketStack;

    cout << "Enter a string with brackets ((), {}, [], <>): ";
    getline(cin, input);

    for (size_t i = 0; i < input.length(); i++) { // iterating through input
        char ch = input[i];

        if (ch == '(' || ch == '{' || ch == '[' || ch == '<') {
             bracketStack.push(pair<char, int>(ch, i)); // Push opening bracket with its index
        } 
        else if (ch == ')' || ch == '}' || ch == ']' || ch == '>') { // if there is not a match
            if (bracketStack.empty()) {
                cout << "Error. Found " << ch << " at position " << i
                     << ", expecting any open." << endl;
                return 1;
            }

            char topBracket = bracketStack.top().first;
            if (!isMatchingPair(topBracket, ch)) { // if there is no corresponding match at all 
                cout << "Error. Found " << ch << " at position " << i
                     << ", expecting " << topBracket << "." << endl;
                return 1;
            }
            bracketStack.pop(); 
        } else {
            cout << "Invalid character " << ch << " in input." << endl;
            return 1;
        }
    }

    if (!bracketStack.empty()) {  // if at the end of the string the stack isn't empty, there's a mismatch
        cout << "Error. Unmatched open parentheses/brackets." << endl;
        return 1;
    }

    cout << "The sequence is correct." << endl;
    return 0;
}
