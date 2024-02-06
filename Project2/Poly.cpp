#include "Poly.h"

vector<PolyData> Poly::stringDeclaration(string s)
{
	vector<PolyData>v;
	for (int i = 0; i < s.size(); i++)
	{
		///Coefficient
		PolyData polyData;
		bool negative = false;
		string num = "";

		///negative
		if (i != 0 && s[i - 1] == '-') negative = true;
		else if (i == 0 && s[i] == '-') negative = true, i++;

		if (s[i] >= 'A' && s[i] <= 'z')
			num = "1";
		else
		{
			while (true)
			{
				if ((s[i] >= 'A' && s[i] <= 'z') || s[i] == '+' || s[i] == '-')
					break;
				num += s[i];
				if (i == s.size() - 1)
					break;
				else i++;
			}
		}
		polyData.coeff = stoi(num);
		if (negative) polyData.coeff *= -1.0;

		///Power

		num = "";
		if (((s[i] >= 'A' && s[i] <= 'z') && i == s.size() - 1) || ((s[i] >= 'A' && s[i] <= 'z') && (s[i + (i != s.size() - 1)] == '+' || s[i + (i != s.size() - 1)] == '-')))
		{
			i++;
			polyData.power = 1;
			goto finish;
		}
		else if (i == s.size() - 1 || s[i] == '+' || s[i] == '-')
		{
			polyData.power = 0;
			goto finish;
		}
		i++;
		if (s[i] == '^')
			i++;
		while (true)
		{
			if (s[i] == '+' || s[i] == '-')
				break;
			num += s[i];
			if (i == s.size() - 1)
				break;
			else i++;
		}
		polyData.power = stoi(num);
	finish:
		v.push_back(polyData);
	}
	return v;
}

string Poly::add(vector<PolyData> v1, vector<PolyData> v2)
{
	for (PolyData i : v2)
		v1.push_back(i);
	return addResults(v1);
}

string Poly::subtract(vector<PolyData> v1, vector<PolyData> v2)
{
	for (PolyData i : v2)
	{
		i.coeff *= -1;
		v1.push_back(i);
	}
	return addResults(v1);
}

string Poly::multiply(vector<PolyData> v1, vector<PolyData> v2)
{
	PolyData p;
	vector<PolyData> result;
	for (int i = 0; i < v1.size(); i++) {
		for (int j = 0; j < v2.size(); j++) {
			p.coeff = v1[i].coeff*v2[j].coeff;
			p.power = v1[i].power + v2[j].power;
			result.push_back(p);
		}
	}
	return addResults(result);
}

string Poly::addResults(vector<PolyData>v1)
{
	map<int, int>mp;     /// first -> Power, second -> Coefficient
	for (PolyData i : v1)
		mp[i.power] += i.coeff;
	return print(mp);
}

string Poly::print(map<int, int>m)
{
	bool firstElement = true;
	string temp="";
	for (auto it=m.rbegin(); it!=m.rend(); it++)
	{
		if (it->second != 0)
		{
			if (!firstElement && it->second>0) temp += "+";
			else firstElement = false;

			if (it->second == -1 && it->first==0) temp += "-1";
			else if (it->second == 1 && it->first==0) temp += "1";
			else if (it->second == -1) temp += "-";
			else if (it->second != 1) temp +=  to_string(it->second);

			if (it->first == 1) temp += "x";
			else if (it->first > 1) temp += "x^" + to_string(it->first);
		}
	}
	cout << temp << endl;
	return temp;
}
