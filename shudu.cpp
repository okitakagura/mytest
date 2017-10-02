#include<iostream>
#include <deque>
using namespace std;

struct Vec {
	int row;
	int col;
	Vec(int r, int c) { row = r; col = c;}
};
deque <Vec> Matrix;

int highscore = 0;
int shudu[9][9];

bool check(int x, int y, int a)
{
	for (int j = 0; j < 9; j++)
	{
		if (shudu[x][j] == a && j != y)
			return false;
	}
	for (int i = 0; i < 9; i++)
	{
		if (shudu[i][y] == a && i != x)
			return false;
	}
	for (int i = x / 3 * 3; i < x / 3 * 3 + 3; ++i)
	{
		for (int j = y / 3 * 3; j < y / 3 * 3 + 3; ++j)
		{
			if (shudu[i][j] == a && i != x && j != y)
				return false;
		}
	}
	return true;
}

void fill_with(deque<Vec> & Matrix)
{
	if (Matrix.empty())
	{
		int score = 0;
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				score = score + shudu[i][j];
			}
		}

		for (int i = 1; i < 4; i++) {
			for (int j = 1; j < 8; ++j)
			{
				if (j != 4)
				{
					score = score + 2 * shudu[i][j];
				}
			}
		}
		score = score + 5 * shudu[2][4] + 3 * (shudu[2][2] + shudu[2][6]) + 8 * (shudu[6][3] + shudu[6][5]);
		if (score > highscore) {
			highscore = score;
		}
		return;
	}
	int x = Matrix.front().row;
	int y = Matrix.front().col;
	Matrix.pop_front();
	for (int a = 1; a < 10; ++a) {
		if (check(x, y, a))
		{
			shudu[x][y] = a;
			fill_with(Matrix);
			shudu[x][y] = 0;
		}
	}
	Matrix.push_front(Vec(x, y));
}

int main()
{
	for (int i = 0; i < 9; ++i)
	{
		for (int j = 0; j < 9; ++j)
			cin >> shudu[i][j];
	}
	for (int i = 0; i < 9; ++i)
	{
		for (int j = 0; j < 9; ++j)
			if(shudu[i][j] == 0)
				Matrix.push_back(Vec(i,j));
	}

	fill_with(Matrix);

	if (highscore != 0)
		cout << highscore;
	else
		cout << -1;
	return 0;
}