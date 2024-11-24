#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cmath>
#include <iomanip>

struct DataPoint {
    double GPA;
    double SAT;
};

double calculateMean(const std::vector<double>& values) {
    double sum = 0.0;
    for (double value : values) {
        sum += value;
    }
    return sum / values.size();
}

int main() {
    std::ifstream file("gpa_sat.csv");

    std::vector<DataPoint> data;
    std::string line;
    // Skip header line
    std::getline(file, line);

    // Read data
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string gpaStr, satStr;
        if (std::getline(ss, gpaStr, ',') && std::getline(ss, satStr)) {
            DataPoint point;
            point.GPA = std::stod(gpaStr);
            point.SAT = std::stod(satStr);
            data.push_back(point);
        }
    }
    file.close();

    // Extract x (GPA) and y (SAT) values
    std::vector<double> x, y;
    for (const auto& point : data) {
        x.push_back(point.GPA);
        y.push_back(point.SAT);
    }

    // Calculate means
    double xMean = calculateMean(x);
    double yMean = calculateMean(y);

    // Calculate beta
    double numerator = 0.0, denominator = 0.0;
    for (size_t i = 0; i < x.size(); ++i) {
        numerator += (x[i] - xMean) * (y[i] - yMean);
        denominator += (x[i] - xMean) * (x[i] - xMean);
    }
    double beta = numerator / denominator;

    // Calculate alpha
    double alpha = yMean - beta * xMean;

    // Calculate predicted y values 
    std::vector<double> predictedY;
    for (double xi : x) {
        predictedY.push_back(alpha + beta * xi);
    }

    // Calculate SSres and SStot
    double SSres = 0.0, SStot = 0.0;
    for (size_t i = 0; i < y.size(); ++i) {
        SSres += (y[i] - predictedY[i]) * (y[i] - predictedY[i]);
        SStot += (y[i] - yMean) * (y[i] - yMean);
    }

    // Calculate R-squared
    double rSquared = 1 - (SSres / SStot);

    // Print results
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Model: SAT score = " << alpha << " + " << beta << "*GPA" << std::endl;
    std::cout << "R-squared: " << rSquared << std::endl;

    return 0;
}
