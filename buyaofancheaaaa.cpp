#include<iostream>
#include<string>
#include<vector>
using namespace std;

int main()
{
	int n;
	int index = 0;
	vector<string>file_name;
	cin >> n;
	for (int j = 0; j < n+1; j++)
	{
		int count = 0;
		string line;
		getline(cin, line);
		if (line[0] == 'c')
		{
			if (line[3] == '/')
			{
				
				for (int i = 3; i < line.size(); i++)
				{
					if (line[i] == '/')
						count++;
				}
				index = 0;
				file_name.clear();
				string::size_type loc1;
				string::size_type loc2 = 1;
				for (int i = 0; i < count; i++)
				{
					string name;
					loc1 = line.find('/', loc2 - 1);
					loc2 = line.find('/', loc1 + 1);
					name = line.substr(loc1 + 1, loc2 - loc1 - 1);
					if (name[0] != '.' && name != "")
					{
						file_name.push_back(name);
						index++;
					}
					else if(name[0] == '.')
					{
						file_name.pop_back();
						index--;
					}
				}
				

			}
			else if (line[3] != '/')
			{
				for (int i = 3; i < line.size(); i++)
				{
					if (line[i] == '/')
						count++;
				}
				string::size_type loc1;
				string::size_type loc2 = 1;
				for (int i = 0; i < count + 1; i++)
				{
					string name;
					if (i == 0)
					{
						string::size_type loc = line.find('/');
						name = line.substr(3, loc - 3);
					}
					else
						{
							loc1 = line.find('/', loc2 - 1);
							loc2 = line.find('/', loc1 + 1);
							name = line.substr(loc1 + 1, loc2 - loc1 - 1);
						}
					if (name[0] != '.' && name != "")
					{
						file_name.push_back(name);
						index++;
					}
					else if (name[0] == '.')
					{
						file_name.pop_back();
						index--;
					}
					
				}
			}

		}
		if (line[0] == 'p')
		{
			cout << '/';
			for (int i = 0; i < index; i++) {
				cout << file_name.at(i) << '/';
			}
			cout <<endl;
		}
	}
	return 0;
}