#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <matplot/matplot.h>

using namespace std;
using namespace matplot;

struct DataPoint {
	double x;
	double y;
	int class_id;
	double distance;
};

struct CompClass {
  bool operator() (DataPoint a, DataPoint b) { return (a.distance < b.distance);}
} distanceComp;

size_t indexOfMax(vector<int> v)
{
	size_t idx = 0;
	int max = v[0];
	for(size_t i = 0; i < v.size(); i++)
	{
		if(v[i] > max)
		{
			max = v[i];
			idx = i;
		}
	}
	return idx;
}

double Dist(DataPoint a, DataPoint b)
{
	double xd = a.x - b.x;
	double yd = a.y - b.y;
	return sqrt(xd*xd + yd*yd);
}

int main(int argc, char* argv[])
{
	
	ifstream ifile("iris.tsv");
	string temp;
	//throw away header
	getline(ifile, temp);
	vector<DataPoint> training_data;
	vector<DataPoint> test_data;
	
	//for plotting
	vector< vector<double> > plot_x;
	vector< vector<double> > plot_y;
	plot_x.resize(3);
	plot_y.resize(3);
	
	for(size_t i = 0; i < 150; i++)
	{
		double sl, sw, pl, pw;
		ifile >> sl >> sw >> pl >> pw >> temp;
		int class_id = i/50;
		DataPoint p({pl,pw,class_id,0.0});
		if(i % 3)
		{
			training_data.push_back(p);
		}
		else {
			test_data.push_back(p);
		}
		plot_x[i/50].push_back(pl);
		plot_y[i/50].push_back(pw);
	}
	vector<int> ks = {1, 3, 5, 7};
	for(auto k: ks)
	{
		size_t mismatches = 0;
		for(auto& test_point : test_data)
		{
			for(auto& trained_point : training_data)
			{
				trained_point.distance = Dist(trained_point, test_point);
			}
			sort(training_data.begin(), training_data.end(), distanceComp);
			vector<int> votes(3);
			for(size_t i = 0; i<k;i++)
			{
				int v = training_data[i].class_id;
				votes[v]++;
			}
			size_t classified_id = indexOfMax(votes);
			if(test_point.class_id != classified_id) mismatches++;
		}
		cout << "Classification accuracy knn-" << k << ": " << 100 - 100*double(mismatches)/test_data.size() << "%" << endl;
	}
	hold(on);
	plot(plot_x[0], plot_y[0], "r*"); 
	plot(plot_x[1], plot_y[1], "gx"); 
	plot(plot_x[2], plot_y[2], "bs");
	show();
	vector< vector<double> >field_x, field_y;
	field_x.resize(3);
	field_y.resize(3);
	
	for(double x = 1.0; x < 7.0; x+=0.1)
	{
		for(double y = 0.0; y < 2.5; y+=0.1)
		{
			DataPoint test_point = {x, y, 0 , 0};
			for(auto& trained_point : training_data)
			{
				trained_point.distance = Dist(trained_point, test_point);
			}
			sort(training_data.begin(), training_data.end(), distanceComp);
			vector<int> votes(3);
			for(size_t i = 0; i<7;i++)
			{
				int v = training_data[i].class_id;
				votes[v]++;
			}
			size_t classified_id = indexOfMax(votes);
			field_x[classified_id].push_back(x);
			field_y[classified_id].push_back(y);
		}
	}
	plot(field_x[0], field_y[0], "ro");
	plot(field_x[1], field_y[1], "go");
	plot(field_x[2], field_y[2], "bo");
	show();
}
