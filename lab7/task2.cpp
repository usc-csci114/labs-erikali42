#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <matplot/matplot.h>
using namespace matplot;

int main() {
    std::ifstream file("atmosphere.txt");
    if (!file) {
        std::cerr << "Error: Could not open file!" << std::endl;
        return 1;
    }

    std::string line;
    // Skip the first 4 lines
    for (int i = 0; i < 4; ++i) {
        std::getline(file, line);
    }

    std::vector<double> h, p, t; // Height, Pressure, Temperature
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        double pres, hght, temp;
        ss >> pres >> hght >> temp;
        p.push_back(pres);
        h.push_back(hght);
        t.push_back(temp);
    }
    file.close();

    // Plot pressure vs. height
    auto fig = figure(true);
    plot(h, p, "-b")->line_width(2);
    xlabel("Height (m)");
    ylabel("Pressure (hPa)");
    title("Pressure vs. Height");
    grid(on);
    save("task2a.png");

	// Find min and max temperature
    double t_min = *std::min_element(t.begin(), t.end());
    double t_max = *std::max_element(t.begin(), t.end());

    // Add secondary plot
    hold(on);
    plot(h, t, "-rx")->use_y2(true);
    y2lim({t_min, t_max});
    y2label("Temperature (°C)");

    // Save the plot
    save("task2b.png");
    return 0;
   }



