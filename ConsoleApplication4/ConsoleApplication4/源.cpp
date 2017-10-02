#include<iostream>
#include<vector>
using namespace std;

bool SellTicket(const vector<int>&vec,int n)
{
	int flag25 = 0, flag50 = 0, flag100 = 0 ,sell = 0;
	for (int i = 0; i < n; i++)
	{
		switch (vec[i])
		{
		case 25:flag25++;
			break;
		case 50:flag50++;
			break;
		case 100:flag100++;
			break;
		}
		if (vec[i] == 25)
			sell++;
		else if (vec[i] == 50 && flag25 >= 1)
		{
			flag25--;
			sell++;
		}
		else if (vec[i] == 100 && (flag50 >= 1 && flag25 >= 1))
		{
			flag50--;
			flag25--;
			sell++;
		}
		else if (vec[i] == 100 && flag25 >= 3)
		{
			flag25 -= 3;
			sell++;
		}
	}
	if (sell == n)
		return true;
	else
		return false;

}
int main()
{
	int amount,member;
	cin >> amount;
	vector<int>vec;
	for(int i = 0; i < amount; i++)
	{
		cin >> member;
		vec.push_back(member);
	}
	if (SellTicket(vec,amount))
		cout << "YES" << endl;
	else
		cout << "NO" << endl;
}