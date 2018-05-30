#include <iostream>
#include "sistema_ecuaciones.cpp"
#include <map>
#include <utility>
#include <string>
#include <vector>


using namespace std;
using pdd = pair<double, double>;

const int n = 3;

double *newton_sistema(double F[n], double JF[n][n], double X[n], double tolerancia);
vector<double> evalua(vector< map<string, pdd> > F_[n], double X0[n]);

int main()
{
	/*
	f[0] = map[x] map[y] map[z] -> map_evalua(map, x,y,z)
	f[1] = map[x] map[y] map[z]
	f[n-1] = map[x] map[y] map[z]
	*/
	
	/*
	x²+y²+z²=2
	x+y+z = 1
	x²+y²-z=0
	*/
	
	/*
	cos(x-y) + e^(cosx-y) = 1
	arctan(xy) + ln(x²+y³) = 2
	*/
	
	//.......................
	//.......................
	vector< map<string, pdd> > F_;
	
	map<string, pdd> f1;
	f1["x"] = pdd(1,2);
	f1["y"] = pdd(1,2);
	f1["z"] = pdd(1,2);
	f1["c"] = pdd(-2,1);
	F_.push_back(f1);
	
	map<string, pdd> f2;
	f2["x"] = pdd(1,1);
	f2["y"] = pdd(1,1);
	f2["z"] = pdd(1,1);
	f2["c"] = pdd(-1,1);
	F_.push_back(f2);
	
	map<string, pdd> f3;
	f3["x"] = pdd(1,2);
	f3["y"] = pdd(1,2);
	f3["z"] = pdd(-1,1);
	f3["c"] = pdd(0,1);
	F_.push_back(f3);
	
	double X0[n] = {1,0,0};
	vector<double> F = evalua(F_, X0);
	//.......................
	//.......................
	vector< map<string, pdd> > F2_;
	/*
	map<string, pdd> f1_2;
	f1_2["x"] = pair<1,2>;
	f1_2["y"] = pair<1,2>;
	f1_2["z"] = pair<1,2>;
	f1_2["c"] = pair<-2,1>;
	F2_[0] = f1_2;
	
	map<string, pdd> f2_2;
	f2_2["x"] = pair<1,1>;
	f2_2["y"] = pair<1,1>;
	f2_2["z"] = pair<1,1>;
	f2_2["c"] = pair<-1,1>;
	F2_[1] = f2_2;
	
	map<string, pdd> f3_2;
	f3_2["x"] = pair<1,2>;
	f3_2["y"] = pair<1,2>;
	f3_2["z"] = pair<-1,1>;
	f3_2["c"] = pair<0,1>;
	F2_[2] = f3_2;*/
	
	
	return 0;
}

double *newton_sistema(double F[n], double JF[n][n], double X[n], double tolerancia)
{
	
}

vector<double> evalua(vector< map<string, pdd> > F_[n], double X0[n])
{
	
}





