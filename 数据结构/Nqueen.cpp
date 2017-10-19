#include<iostream>
#include<math.h>
using namespace std;
bool place(int k, int *board) {
	for (int i = 1; i < k; i++) {
		if (board[i] == board[k] || abs(board[i] - board[k]) == abs(i - k))
			return false;
	}
	return true;
}

int queen(int n, int *board) {
	int count = 0;
	int k = 1;
	board[1] = 0;
	while (k > 0) {
		board[k] = board[k] + 1;
		while (board[k] <= n && !place(k, board)) {
			board[k] = board[k] + 1;
		}
		if (board[k] <= n) {
			if (k == n) {
				for (int i = 0; i < n; i++) {
					for (int j = 0; j < n; j++) {
						if (board[i + 1] == j + 1)
							cout << "X ";
						else
							cout << "0 ";
					}
					cout << endl;
				}
				cout << endl;
				count++;
			}
			else {
				k = k + 1;
				board[k] = 0;
			}
		}
		else {
			k = k - 1;
		}
	}
	return count;
}

int main() {
	int n;
	cout << "����N��N�����̣�����N���ʺ�Ҫ�����лʺ���ͬһ�С��к�ͬһб���ϣ�" << endl;
	cout << endl << "������ʺ�ĸ�����";
	cin >> n;
	int *board = new int[n];
	cout << endl << "�ʺ�ڷ���" << endl << endl;
	int count = queen(n, board);
	cout << "����" << count << "�ֽⷨ��" << endl;
}