#include<iostream>
#include<vector>
using namespace std;
const int m = 5, n = 5;
char maze[m + 2][n + 2];
int mark[m + 2][n + 2];
struct movedir {
	int a;//x方向的偏移量
	int b;//y方向的偏移量
};
struct items {
	int x, y;   //位置
};
int main() {
	for (int i = 0; i < m + 2; i++) {
		for (int j = 0; j < n + 2; j++) {
			cin >> maze[i][j];
		}
	}
	for (int i = 0; i < m + 2; i++) {
		for (int j = 0; j < n + 2; j++) {
			if (i == 0 || i == m + 1 || j == 0 || j == n + 1) {
				mark[i][j] = 1;
			}
			else
			{
				mark[i][j] = 0;
			}
		}
	}
	void findpath();
	findpath();
	return 0;
}
void findpath() {
	void printmaze();
	//一个位置一共有四个方向可以移动
	movedir move[4] = { { -1,0 },{ 0,1 },{ 1,0 },{ 0,-1 } };
	mark[1][1] = 1;   //入口为[1][1]
	int i, j, direct = 0, nx, ny;
	vector<items>st;
	items temp;
	temp.x = 1;
	temp.y = 1;
	st.push_back(temp);
	while (!st.empty()) {
		i = temp.x;
		j = temp.y;
		while (direct < 4) {
			nx = i + move[direct].a;
			ny = j + move[direct].b;  //找下一个位置（nx，ny）
			if (nx == m&&ny == n) {
				for (unsigned int k = 0; k < st.size(); k++) {
					maze[st[k].x][st[k].y] = 'x';
				}
				maze[m][n] = 'x';
				printmaze();
				cout << "迷宫路径：" << endl <<endl;
				for (unsigned int k = 0; k < st.size(); k++) {
					maze[st[k].x][st[k].y] = 'x';
					cout << '<' << st[k].x << ',' << st[k].y << "> ---> ";
				}
				cout << '<' << m << ',' << n << '>' << endl;
				return;
			}
			else if (maze[nx][ny] == '0' && mark[nx][ny] == 0) {
				mark[nx][ny] = 1;
				temp.x = nx;
				temp.y = ny;
				st.push_back(temp);//记忆已通过的位置
				i = nx;
				j = ny;
				direct = 0;
			}
			else
				direct++;
		}

		st.pop_back();
		direct = 0;
		if (!st.empty()) {
			temp.x = st[st.size() - 1].x;
			temp.y = st[st.size() - 1].y;

		}

	}
	cout << "no path in maze" << endl;
}

void printmaze() {
	cout << "迷宫地图：" << endl << endl;
	cout << "  \t";
	for (int k = 0; k < n + 2; k++) {
		cout << k << "列\t";
	}
	cout << endl;
	for (int i = 0; i < m+2; i++) {
		cout << i << "行\t";
		for (int j = 0; j < n+2; j++) {
			cout << maze[i][j] << '\t';
		}
		cout << endl <<endl;
	}
}