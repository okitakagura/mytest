#include<iostream>
using namespace std;
struct Node {
	int data;
	Node * next;
};
class circle {
public:
	circle() { first = NULL; };
	bool input(int N);
	Node *first;
};
bool circle::input(int N) {
	Node * p, *last;
	last = first;
	for (int n = 1; n <= N; n++) {
		p = new Node;
		p->data = n;
		if (p == NULL) {
			cerr << "存储分配错误！" << endl;
			exit(1);
		}
		if (n == 1) {
			first = p;
			last = p;
		}
		else {
			last->next = p;
			last = p;
		}
	}
	last->next = first;
	return true;
}

void josephus(circle c) {
	int n, s, m, k;
	cout << "请输入生死游戏的总人数N：";
	cin >> n;
	cout << "请输入游戏开始的位置S：";
	cin >> s;
	cout << "请输入死亡数字M：";
	cin >> m;
	cout << "请输入剩余的生者人数K：";
	cin >> k;
	cout << endl;
	c.input(n);
	Node *p = c.first;
	Node *pre = NULL;
	int i, j;
	for (int w = 1; w < s; w++) {
		pre = p;
		p = p->next;
	}
	for (i = 1; i < n - k + 1; i++) {
		for (j = 1; j < m; j++) {
			pre = p;
			p = p->next;
		}
		cout << "第" << i << "个死者的位置是：\t"<< p->data << endl;
		pre->next = p->next;
		delete p;
		p = pre->next;
	}
	cout << endl;
	pre = p;
	p = p->next;
	while (p->data > pre->data) {
		pre = p;
		p = p->next;
	}
	cout << "最后剩下：\t" << k << "人" << endl;
	cout << "剩余的生者位置为：";
	for (i = 0; i < k; i++) {
		cout << '\t' << p->data;
		pre->next = p->next;
		delete p;
		p = pre->next;
	}
	cout << endl;

}
int main() {
	cout << "现有N人围成一圈，从第S个人开始依次报数，报M的人出局，再有下一个人开始报数，如此循环，直至剩下K个人为止" << endl;
	cout << endl;
	circle Jos;
	josephus(Jos);
	return 0;
}


