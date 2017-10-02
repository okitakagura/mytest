#include<iostream>
#include<string>
#include<vector>
using namespace std;

int main()
{
	int m, n;
	cin >> m >> n;
	vector<string>girls;
	vector<string>outs;
	for (int i = 0; i < m + 1; ++i)
	{
		string girl;
		getline(cin, girl);
		girls.push_back(girl);
	}
	for (int i = 0; i < n; ++i)
	{
		string findGirl;
		getline(cin, findGirl);
		int j;
		string::size_type position;
		for (j = 1; j < m + 1; ++j)
		{
			position = girls.at(j).rfind(findGirl);
			if (position != girls.at(j).npos)
				break;
		}
		if (position == 0)
		{
			string gf = girls.at(j);
			string::size_type p2 = gf.find(']');
			string address = gf.substr(p2 + 2, gf.size() - p2 - 2);
			outs.push_back(address);
		}
		else if (position == girls.at(j - 1).npos)
		{
			outs.push_back("ha?");
		}
		else
		{
			string gf = girls.at(j);
			string name = gf.substr(1, position - 3);
			outs.push_back(name);
		}
	}
	for (unsigned int i = 0; i < outs.size(); ++i)
	{
		cout << outs.at(i) << endl;
	}
	return 0;
}