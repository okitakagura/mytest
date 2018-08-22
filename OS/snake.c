//snake.c
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<curses.h>
#include<signal.h>
#inclde<sys/time.h>
#include<time.h>


//�ݺ��᷽��
typedef struct direct
{
	int cx;
	int cy;
}direct;

//������
typedef struct node
{
	int cx;
	int cy;
	struct node *last;
	struct node *next;
}node;

void initGame();                   //��ʼ����Ϸ
int setTicker(int i);              //���ü�ʱ��
void show();                       //��������
void showInfo();                   //��ʾ��Ϣ
void showSnake();                  //��ʾ��
void getInput();                   //��ȡ�����������Ϣ
void overGame(int i);              //��Ϸ����

void creatLink();
void insertNode(int x, int y);
void deleteNode();
void deleteLink();

int ch;                            //���������
int hour, minute, second;          //ʱ����
int length;                        //�ߵĳ���
int totTime, level;                //��ʱ���ȼ�
direct dir;                        //��ǰ������
direct food;                       //ʳ���λ��
node *head, *tail;                 //�����ͷβ���

int main()
{
	initscr();                     //curses����ʼ
	initGame();
	signal(SIGALRM, show);
	getOrder();
	endwin();                      //curses�������
	return 0;
}

//��ʼ����Ϸ
void initGame()
{
	cbreak();                      //���ն˵�CBREAKģʽ
	noecho();                      //�رջ���
	curs_set(0);                   //�����Ϊ���ɼ�
	keypad(stdscr, true);          //Ϊ��׼��Ļ����ܼ�
	srand(time(0));                //�������������
	hour = minute = second = 0;    //��ʼ������
	totTime = 0;
	length = 1;
	dir.cx = 1;
	dir.cy = 0;
	ch = 'A';
	food.cx = rand() % COLS;
	food.cy = rand() % (LINES - 2) + 2;    //ǰ������ʾ��Ϣ
	creatLink();
	setTicker(20);
}

//���ü�ʱ��
int setTicker(int i)
{
	struct itimerval itv;
	long  n_sec, n_usecs;
	n_sec = i / 1000;
	n_usecs = (i % 1000) * 1000L;
	//���ʱ��
	itv.it_interval.tv_sec = n_sec;
	itv.it_interval.tv_usec = n_usecs;
	i = 1;
	n_sec = i / 1000;
	n_usecs = (i % 1000) * 1000L;
	//��ʼ����ʱ��
	itv.it_value.tv_sec = n_sec;
	itv.it_value.tv_usec = n_usecs;
	return setitimer(ITIMER_REAL, &itv, NULL);
}

//���û���
void show()
{
	signal(SIGALRM, show);         //�����ж��ź�
	showInfo();
	showSnake();
	refresh();                     //ˢ����ʵ��Ļ
}

//��ʾ�Ϸ����е���Ϸ��Ϣ
void showInfo()
{
	totTime++;
	if (totTime >= 1000000)
		totTime = 0;
	if (1 != totTime % 50)
		return;             //����1��
	move(0, 3);
	//��ʾʱ��
	printw("time: %d:%d:%d %c", hour, minute, second);
	second++;
	if (second > 60)
	{
		second = 0;
		minute++;
	}
	if (minute > 60)
	{
		minute = 0;
		hour++;
	}
	move(1, 0);
	int i;
	for (i = 0; i < COLS; i++)
		addstr("-");
	move(0, COLS / 2 - 5);
	printw("length: %d", length);         //��ʾ�ߵĳ���
	move(0, COLS - 10);
	level = length / 3 + 1;
	printw("level: %d", level);           //��ʾ�ȼ�
}

//��ʾ��
void showSnake()
{
	if (1 != totTime % (30 - level))
		return;
	bool lengCh = false;                
	move(food.cy, food.cx);               
	printw("@");                           //��ʾʳ��
	//��������ǽ������Ϸ����
	if ((COLS - 1 == head->next->cx && 1 == dir.cx)
		|| (0 == head->next->cx && -1 == dir.cx)
		|| (LINES - 1 == head->next->cy && 1 == dir.cy)
		|| (2 == head->next->cy && -1 == dir.cy))
	{
		overGame(1);
		return;
	}
	//���߳Ե��Լ����壬����Ϸ����
	if ('*' == mvinch(head->next->cy + dir.cy, head->next->cx + dir.cx))
	{
		overGame(2);
		return;
	}
	insertNode(head->next->cx + dir.cx, head->next->cy + dir.cy);
	//���߳���ʳ�������䳤
	if (head->next->cx == food.cx && head->next->cy == food.cy)
	{
		lengCh = true;
		length++;
		//���ɹ�����50��ʳ��ʱ������
		if (length >= 50)
		{
			overGame(3);
			return;
		}
		//����������һ��ʳ���λ��
		food.cx = rand() % COLS;
		food.cy = rand() % (LINES - 2) + 2; 
	}
	//������ǰ����ɾ��β����㣬����ͷ�����
	if (!lengCh)
	{
		move(tail->last->cy, tail->last->cx);
		printw(" ");
		deleteNode();
	}
	move(head->next->cy, head->next->cx);
	printw("*");
}

//��Ϸ����
void overGame(int i)
{
	move(0, 0);
	int j;
	for (j = 0; j < COLS; j++)
		addstr(" ");
	move(0, 2);                  //��ʾ��������
	if (i == 1)
		addstr("Crash the wall. Game over!");
	else if (i == 2)
		addstr("Crash itself. Game over!");
	else if (i == 3)
		addstr("Pass the Game!");
	setTicker(0);                 //�رռ�ʱ��
	deleteLink();                 //�ͷ���������
}

//��ȡ�������������
void getInput()
{
	while (1)
	{
		ch = getch();
		if (ch == KEY_RIGHT)
		{
			dir.cx = 1;
			dir.cy = 0;
		}
		if (ch == KEY_LEFT)
		{
			dir.cx = -1;
			dir.cy = 0;
		}
		if (ch == KEY_UP)
		{
			dir.cx = 0;
			dir.cy = -1;
		}
		if (ch == KEY_DOWN)
		{
			dir.cx = 0;
			dir.cy = 1;
		}
		setTicker(20);
	}
}

//����������һ��˫������
void creatLink()
{
	node * temp = (node *)malloc(sizeof(node));
	head = (node *)malloc(sizeof(node));
	tail = (node *)malloc(sizeof(node));
	temp->cx = 5;
	temp->cy = 10;
	head->last = tail->next = NULL;
	head->next = temp;
	temp->next = tail;
	tail->last = temp;
	temp->last = head;
}

//������ͷ������һ�����
void insertNode(int x, int y)
{
	node * temp = (node *)malloc(sizeof(node));
	temp->cx = x;
	temp->cy = y;
	temp->next = head->next;
	head->next = temp;
	temp->last = head;
	temp->next->last = temp;
}

//������β��ɾ��һ�����
void deleteNode()
{
	node *temp = tail->last;
	node *btemp = temp->last;
	btemp->next = tail;
	tail->last = btemp;
	temp->next = temp->last = NULL;
	free(temp);
	temp = NULL;
}

//ɾ����������
void deleteLink()
{
	while (head->next != tail)
		deleteNode();
	head->next = tail->last = NULL;
	free(head);
	free(tail);
}