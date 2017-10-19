#include<iostream>
#include<vector>
using namespace std;
const int m = 5, n = 5;
char maze[m + 2][n + 2];
int mark[m + 2][n + 2];
struct movedir {
	int a;//x�����ƫ����
	int b;//y�����ƫ����
};
struct items {
	int x, y;   //λ��
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
	//һ��λ��һ�����ĸ���������ƶ�
	movedir move[4] = { { -1,0 },{ 0,1 },{ 1,0 },{ 0,-1 } };
	mark[1][1] = 1;   //���Ϊ[1][1]
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
			ny = j + move[direct].b;  //����һ��λ�ã�nx��ny��
			if (nx == m&&ny == n) {
				for (unsigned int k = 0; k < st.size(); k++) {
					maze[st[k].x][st[k].y] = 'x';
				}
				maze[m][n] = 'x';
				printmaze();
				cout << "�Թ�·����" << endl <<endl;
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
				st.push_back(temp);//������ͨ����λ��
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
	cout << "�Թ���ͼ��" << endl << endl;
	cout << "  \t";
	for (int k = 0; k < n + 2; k++) {
		cout << k << "��\t";
	}
	cout << endl;
	for (int i = 0; i < m+2; i++) {
		cout << i << "��\t";
		for (int j = 0; j < n+2; j++) {
			cout << maze[i][j] << '\t';
		}
		cout << endl <<endl;
	}
}