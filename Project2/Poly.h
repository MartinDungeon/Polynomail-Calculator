#include<iostream>
#include<stdlib.h>
#include<string>
#include<vector>
#include<algorithm>
#include<map>
#include <fstream>
using namespace std;

class PolyData
{
public:
	int power;
	int coeff;
};

class Poly
{
public:
	vector<PolyData> stringDeclaration(string s);
	string add(vector<PolyData> v1, vector<PolyData> v2);
	string subtract(vector<PolyData> v1, vector<PolyData> v2);
	string multiply(vector<PolyData> v1, vector<PolyData> v2);
	string addResults(vector<PolyData>v1);
	string print(map<int, int>m);
};

class SavedOperation
{
public:
	string poly1, poly2, ans;
	int operation;
};
