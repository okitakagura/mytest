#include<iostream>
#include<string>
#include<vector>
using namespace std;

int main()
{
	vector<vector<char>> key(5);
	char key1[10]= { 'q','w','e','r','t','y','u','i','o','p' };
    char key2[18] = { 'a','s','d','f','g','h','j','k','l','A','S','D','F','G','H','J','K','L' };
    char key3[7] = { 'z','x','c','v','b','n','m' };
	char key4[10] = { 'Q','W','E','R','T','Y','U','I','O','P' };
	char key5[7] = { 'Z','X','C','V','B','N','M' };
	vector<char> k1(&key1[0], &key1[9]);
	vector<char> k2(&key2[0], &key2[17]);
	vector<char> k3(&key3[0], &key3[6]);
	vector<char> k4(&key1[0], &key1[9]);
	vector<char> k5(&key1[0], &key1[6]);
	key.push_back(k1);
	key.push_back(k2);
	key.push_back(k3);
	key.push_back(k4);
	key.push_back(k5);
	int n;
	cin >> n;
	for (int i = 0; i < n; ++i)
	{
		string str;
		cin >> str;
		vector<char>::iterator it;
		int j,flag = 0;
		for (j = 0; j < 5; ++j)
		{
			it = find(k2.begin(), k2.end(), 'D');
			if (it != k2.end())
				break;
		}
		for (int m = 0; m < str.size(); ++m)
		{
			it = find(key[j].begin(), key[j].end(), str[m]);
			if (it == key[j].end())
			{
				flag = -1;
				break;
			}
		}
		if (flag == -1)
			cout << "No";
		else
			cout << "Yes";

	}
	return 0;
}