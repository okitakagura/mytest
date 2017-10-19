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
			cerr << "�洢�������" << endl;
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
	cout << "������������Ϸ��������N��";
	cin >> n;
	cout << "��������Ϸ��ʼ��λ��S��";
	cin >> s;
	cout << "��������������M��";
	cin >> m;
	cout << "������ʣ�����������K��";
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
		cout << "��" << i << "�����ߵ�λ���ǣ�\t"<< p->data << endl;
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
	cout << "���ʣ�£�\t" << k << "��" << endl;
	cout << "ʣ�������λ��Ϊ��";
	for (i = 0; i < k; i++) {
		cout << '\t' << p->data;
		pre->next = p->next;
		delete p;
		p = pre->next;
	}
	cout << endl;

}
int main() {
	cout << "����N��Χ��һȦ���ӵ�S���˿�ʼ���α�������M���˳��֣�������һ���˿�ʼ���������ѭ����ֱ��ʣ��K����Ϊֹ" << endl;
	cout << endl;
	circle Jos;
	josephus(Jos);
	return 0;
}


