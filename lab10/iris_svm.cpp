#include <iostream>
#include <vector>
#include <fstream>
#include <dlib/svm.h>
#include <matplot/matplot.h>

using namespace std;
using namespace dlib;
using namespace matplot;

int main(int argc, char* argv[])
{
	//2D samples 2 row, 1 column
	typedef dlib::matrix<double, 2, 1> sample_type;

	//samples and labels are seperate
	std::vector<sample_type> samples;
	std::vector<double> labels;
	
	std::vector<sample_type> tests;
	
	ifstream ifile("iris.tsv");
	string temp;
	//throw away header
	getline(ifile, temp);
	
	//The linear kernel is good for linearally seperable data
	typedef linear_kernel<sample_type> kernel_type;

	for(size_t i = 0; i < 150; i++)
	{
		double sl, sw, pl, pw;
		ifile >> sl >> sw >> pl >> pw >> temp;
		if(i < 50) continue;
		
		sample_type sample;
		sample(0) = sl;
		sample(1) = pw;
		double label = i < 100 ? -1 : 1;
		//save some data for testing
		if(i % 3 == 0)
		{
			tests.push_back(sample);		
		}
		else
		{
			samples.push_back(sample);
			labels.push_back(label);
		}
	}
	//instantiate the trainer and train
	svm_c_linear_trainer<kernel_type> linear_trainer;
	linear_trainer.set_c(10);
	decision_function<kernel_type> df = linear_trainer.train(samples, labels);
	
	std::vector<double> xvals_plusone;
	std::vector<double> yvals_plusone;
	std::vector<double> xvals_negone;
	std::vector<double> yvals_negone;

	for(int i = 0; i < samples.size(); i++)
	{
		if(labels[i] > 0)
		{
			xvals_plusone.push_back(samples[i](0));
			yvals_plusone.push_back(samples[i](1));
		}
		else
		{
			xvals_negone.push_back(samples[i](0));
			yvals_negone.push_back(samples[i](1));
		}
	}
	
	plot(xvals_plusone, yvals_plusone, "ro");
	hold(on);
	plot(xvals_negone, yvals_negone, "bx");
	
	std::vector<double> xs_p1;
	std::vector<double> ys_p1;
	
	std::vector<double> xs_n1;
	std::vector<double> ys_n1;
	
	for(double x = 4.5; x <= 8; x+=0.1)
	{
		for(double y = 1; y <= 2.6; y+=0.1)
		{
			sample_type sample;
			sample(0) = x;
			sample(1) = y;
			if(df(sample) > 0)
			{
				xs_p1.push_back(x);
				ys_p1.push_back(y);
			}
			else
			{
				xs_n1.push_back(x);
				ys_n1.push_back(y);
			}
		}
	}
	plot(xs_p1, ys_p1, "y^");
	plot(xs_n1, ys_n1, "gv");
	show();
}
