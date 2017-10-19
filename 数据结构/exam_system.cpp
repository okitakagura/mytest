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
	cout << "首先请建立考生信息系统！" << endl;
	cout << "请输入考生人数：";
	cin >> amount;
	cout << "请依次输入考生的考号，姓名，性别，年龄及报考类别！" << endl;
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
	cout << "请选择您要进行的操作（1为插入，2为删除，3为查找，4为修改，5为统计，0为取消操作）" << endl;
	return true;
}

bool list::search() {
	int number;
	int sign = 0;
	cout << "请输入要查找的考生的考号：";
	cin >> number;
	student * p;
	p = head;
	while (p != NULL) {
		if (p->_number == number) {
			sign = 1;
			cout << "考号\t姓名\t性别\t年龄\t报考类别" << endl;
			cout << p->_number << '\t' << p->_name << '\t' << p->_sex << '\t' << p->_age << '\t' << p->_subject << endl;
			break;
		}
		p = p->next;
	}
	if (sign == 0)
		cout << "该考生号不存在！" << endl;
	return true;

}
bool list::print() {
	student * p;
	cout << endl << "考号\t姓名\t性别\t年龄\t报考类别" << endl;
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
	cout << "请输入你要插入的考生的位置：";
	cin >> n;
	cout << "请依次输入要插入的考生的考号，姓名，性别，年龄及报考类别！" << endl;
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
	cout << "请输入要删除的考生的考号:";
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
			cout << "你删除的考生信息是：";
			cout << p1->next->_number << '\t' << p1->next->_name << '\t' << p1->next->_sex << '\t' << p1->next->_age << '\t' << p1->next->_subject << endl;
			del = p1->next;
			p1->next = del->next;
			delete del;
			amount--;
			print();
		}

		else {
			cout << "该考生号不存在！" << endl;
		}
	}
	else {
		cout << "你删除的考生信息是：";
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
	cout << "请输入要修改的考生的考号：";
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
		cout << "请依次输入修改后的考生的考号，姓名，性别，年龄及报考类别！" << endl;
		cin >> p1->_number >> p1->_name >> p1->_sex >> p1->_age >> p1->_subject;
		print();
	}
	else {
		cout << "该考生号不存在！" << endl;
	}
	return true;
}
bool list::total() {
	cout << "总共有" << amount << "位考生报名考试" << endl;
	return true;
}

int main() {
	list stu;
	int i;
	stu.creat();
	do {
		cout << "请选择您要进行的操作：";
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
		default:cout << "您输入的数据有误！" << endl;
		}
	} while (1);
	return 0;
}