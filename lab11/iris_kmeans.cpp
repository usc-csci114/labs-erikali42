#include <iostream>
#include <vector>
#include <fstream>
#include <matplot/matplot.h>

using namespace std;
using namespace matplot;

struct DataPoint {
	double x;
	double y;
	int cluster;
};

struct Mean {
	double x;
	double y;
};

size_t indexOfMin(vector<double> v)
{
	size_t idx = 0;
	double min = v[0];
	for(size_t i = 0; i < v.size(); i++)
	{
		if(v[i] < min)
		{
			min = v[i];
			idx = i;
		}
	}
	return idx;
}

double Dist(DataPoint d, Mean m)
{
	double xd = d.x - m.x;
	double yd = d.y - m.y;
	return sqrt(xd*xd + yd*yd);
}

int main(int argc, char* argv[])
{
	
	
	ifstream ifile("iris.tsv");
	string temp;
	//throw away header
	getline(ifile, temp);
	vector<Mean> means(3);
	vector<DataPoint> data;
	
	vector< vector<double> > plot_x;
	vector< vector<double> > plot_y;
	plot_x.resize(3);
	plot_y.resize(3);
	
	for(size_t i = 0; i < 150; i++)
	{
		double sl, sw, pl, pw;
		ifile >> sl >> sw >> pl >> pw >> temp;
		DataPoint p({pl,pw,0});
		data.push_back(p);
		plot_x[i/50].push_back(pl);
		plot_y[i/50].push_back(pw);
	}
	
		
	//initial guesses
	means[0] = {0, 0};
	means[1] = {2, 0};
	means[2] = {6,0};
	
	hold(on);
	plot(plot_x[0], plot_y[0], "r*"); 
	plot(plot_x[1], plot_y[1], "gx"); 
	plot(plot_x[2], plot_y[2], "bs"); 
	plot({means[0].x}, {means[0].y}, "ko")->line_width(2)
	.marker_size(20).marker_color("b").marker_face_color({.5, .5, .5}); 
	
	plot({means[1].x}, {means[1].y}, "ko")->line_width(2)
	.marker_size(20).marker_color("b").marker_face_color({.5, .5, .5});
	
	plot({means[2].x}, {means[2].y}, "ko")->line_width(2)
	.marker_size(20).marker_color("b").marker_face_color({.5, .5, .5});	
	show();
	cla();
	
	
	size_t changes = data.size();
	size_t iterations = 0;
	while(changes != 0)
	{
		iterations++;
		//Assign each data point to the closest mean
		changes = 0;
		for(auto& dp: data)
		{
			vector<double> distances(3);
			for(size_t i = 0; i<3;i++)
			{
				distances[i] = Dist(dp, means[i]);
			}
			size_t cm = indexOfMin(distances);
			if(dp.cluster != cm) changes++;
			dp.cluster = cm;
		}
		cout << "Points changing cluster: " << changes << endl;
		//Update means
		means[0] = {0,0};
		means[1] = {0,0};
		means[2] = {0,0};
		vector<int> counts(3);
		
		for(auto& dp: data)
		{
			counts[dp.cluster]++;
			means[dp.cluster].x += dp.x;
			means[dp.cluster].y += dp.y;
		}
		for(size_t i = 0; i < 3; i++)
		{
			means[i].x /= counts[i];
			means[i].y /= counts[i];
		}
		cout << "{" << means[0].x << "," << means[0].y << "}";
		cout << "{" << means[1].x << "," << means[1].y << "}";
		cout << "{" << means[2].x << "," << means[2].y << "}" << endl;
		hold(on);
		plot(plot_x[0], plot_y[0], "r*"); 
		plot(plot_x[1], plot_y[1], "gx"); 
		plot(plot_x[2], plot_y[2], "bs"); 
		plot({means[0].x}, {means[0].y}, "ko")->line_width(2)
		.marker_size(20).marker_color("b").marker_face_color({.5, .5, .5}); 
		
		plot({means[1].x}, {means[1].y}, "ko")->line_width(2)
		.marker_size(20).marker_color("b").marker_face_color({.5, .5, .5});
		
		plot({means[2].x}, {means[2].y}, "ko")->line_width(2)
		.marker_size(20).marker_color("b").marker_face_color({.5, .5, .5});	
		show();
		cla();
	}
	cout << "Converged in " << iterations << " iterations." << endl;
	//Check "classification" accuracy
	size_t mismatches = 0;
	for(size_t i = 0; i < data.size(); i++)
	{
		cout << "Index: " << i << " cluster " << data[i].cluster << endl;
		if(i/50 != data[i].cluster) mismatches++;
	}
	cout << "Mismatches " << mismatches << " accuracy: " << 100- 100*double(mismatches)/data.size() << "%" << endl;
}
