#include <iostream>
#include <string>

using namespace std;

int main(int argc, char* argv[])
{
	int a = 10;
	double b = 3.1415;
	
	auto f = [a,&b](const string s) -> double {
		std::cout << s << " " << "a: " << a << " b: " << b << endl;
		return b/a;
	};
	
	double v = f("What are a and b?");
	cout << "v is " << v << endl;
	
	a -= 5;
	b /= 2;
	
	v = f("Have they changed?");
	cout << "v is " << v << endl;
	
}
