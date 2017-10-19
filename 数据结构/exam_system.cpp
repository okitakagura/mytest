#include<iostream>
#include<string>
using namespace std;
struct student {

	int _number;
	string _name;
	string _sex;
	int _age;
	string _subject;
	student * next;
};
class list {
private:
	student * head;
	int amount;
public:
	list() { head = NULL; amount = 0; };
	~list() {
		student *temp;
		for (int i = 0; i < amount; i++) {
			temp = head;
			head = head->next;
			delete temp;
		}
	}
	bool creat();
	bool search();
	bool insert();
	bool modify();
	bool cancel();
	bool print();
	bool total();

};
bool list::creat() {
	cout << "�����뽨��������Ϣϵͳ��" << endl;
	cout << "�����뿼��������";
	cin >> amount;
	cout << "���������뿼���Ŀ��ţ��������Ա����估�������" << endl;
	int n = amount;
	student *p, *s;
	s = new student;
	p = new student;
	cin >> s->_number >> s->_name >> s->_sex >> s->_age >> s->_subject;
	int j = n - 1;
	while (j--) {
		if (NULL == head) {
			head = s;
		}
		else {
			p->next = s;
		}
		p = s;
		s = new student;
		cin >> s->_number >> s->_name >> s->_sex >> s->_age >> s->_subject;
	}
	if (NULL == head) {
		head = s;
	}
	else {
		p->next = s;
	}
	p = s;
	p->next = NULL;
	print();
	cout << "��ѡ����Ҫ���еĲ�����1Ϊ���룬2Ϊɾ����3Ϊ���ң�4Ϊ�޸ģ�5Ϊͳ�ƣ�0Ϊȡ��������" << endl;
	return true;
}

bool list::search() {
	int number;
	int sign = 0;
	cout << "������Ҫ���ҵĿ����Ŀ��ţ�";
	cin >> number;
	student * p;
	p = head;
	while (p != NULL) {
		if (p->_number == number) {
			sign = 1;
			cout << "����\t����\t�Ա�\t����\t�������" << endl;
			cout << p->_number << '\t' << p->_name << '\t' << p->_sex << '\t' << p->_age << '\t' << p->_subject << endl;
			break;
		}
		p = p->next;
	}
	if (sign == 0)
		cout << "�ÿ����Ų����ڣ�" << endl;
	return true;

}
bool list::print() {
	student * p;
	cout << endl << "����\t����\t�Ա�\t����\t�������" << endl;
	p = head;
	if (head != NULL) {
		do {
			cout << p->_number << '\t' << p->_name << '\t' << p->_sex << '\t' << p->_age << '\t' << p->_subject << endl;
			p = p->next;
		} while (p != NULL);
	}
	return true;
}

bool list::insert() {
	int n;
	cout << "��������Ҫ����Ŀ�����λ�ã�";
	cin >> n;
	cout << "����������Ҫ����Ŀ����Ŀ��ţ��������Ա����估�������" << endl;
	student *s;
	s = new student;
	cin >> s->_number >> s->_name >> s->_sex >> s->_age >> s->_subject;
	student *p0, *p1, *p2;
	p1 = head;
	p0 = s;
	if (head == NULL) {
		head = s; s->next = NULL;
	}
	else {
		if (n == 1) {
			head = p0;
			p0->next = p1;
		}
		else {
			int m = n - 1;
			while ((m--) && (p1->next != NULL)) {
				p2 = p1;
				p1 = p1->next;
			}
			p1->next = p0; p0->next = NULL;
		}

	}
	amount++;
	print();
	return true;
}
bool list::cancel() {
	cout << "������Ҫɾ���Ŀ����Ŀ���:";
	int number;
	cin >> number;
	student *p1, *p2, *del;
	p1 = head;
	p2 = new student;
	if (number != p1->_number) {

		while (number != p1->next->_number && p1->next->next != NULL) {
			p2 = p1;
			p1 = p1->next;
		}

		if (number == p1->next->_number) {
			cout << "��ɾ���Ŀ�����Ϣ�ǣ�";
			cout << p1->next->_number << '\t' << p1->next->_name << '\t' << p1->next->_sex << '\t' << p1->next->_age << '\t' << p1->next->_subject << endl;
			del = p1->next;
			p1->next = del->next;
			delete del;
			amount--;
			print();
		}

		else {
			cout << "�ÿ����Ų����ڣ�" << endl;
		}
	}
	else {
		cout << "��ɾ���Ŀ�����Ϣ�ǣ�";
		cout << p1->_number << '\t' << p1->_name << '\t' << p1->_sex << '\t' << p1->_age << '\t' << p1->_subject << endl;
		del = head;;
		head = head->next;
		delete del;
		amount--;
		print();
	}
	return true;
}

bool list::modify() {
	cout << "������Ҫ�޸ĵĿ����Ŀ��ţ�";
	int number;
	cin >> number;
	student *p1, *p2;
	p1 = head;
	while (number != p1->_number && p1->next != NULL) {
		p2 = p1;
		p1 = p1->next;
	}
	if (number == p1->_number)
	{
		cout << "�����������޸ĺ�Ŀ����Ŀ��ţ��������Ա����估�������" << endl;
		cin >> p1->_number >> p1->_name >> p1->_sex >> p1->_age >> p1->_subject;
		print();
	}
	else {
		cout << "�ÿ����Ų����ڣ�" << endl;
	}
	return true;
}
bool list::total() {
	cout << "�ܹ���" << amount << "λ������������" << endl;
	return true;
}

int main() {
	list stu;
	int i;
	stu.creat();
	do {
		cout << "��ѡ����Ҫ���еĲ�����";
		cin >> i;
		switch (i) {
		case 1:stu.insert();
			break;
		case 2:stu.cancel();
			break;
		case 3:stu.search();
			break;
		case 4:stu.modify();
			break;
		case 5:stu.total();
			break;
		case 0:exit(0);
		default:cout << "���������������" << endl;
		}
	} while (1);
	return 0;
}