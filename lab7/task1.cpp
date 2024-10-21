#include <cmath>
#include <matplot/matplot.h>
using namespace matplot;

int main() {
	
	std::vector<double> x = linspace(0, 10);
	std::vector<double> y = x;
			
	plot(x, y, "-xr");
	show();
	save("task1.png");
	return 0;
}
