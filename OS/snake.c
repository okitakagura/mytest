//snake.c
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<curses.h>
#include<signal.h>
#inclde<sys/time.h>
#include<time.h>


//纵横轴方向
typedef struct direct
{
	int cx;
	int cy;
}direct;

//蛇身结点
typedef struct node
{
	int cx;
	int cy;
	struct node *last;
	struct node *next;
}node;

void initGame();                   //初始化游戏
int setTicker(int i);              //设置计时器
void show();                       //画面设置
void showInfo();                   //显示信息
void showSnake();                  //显示蛇
void getInput();                   //获取方向键输入信息
void overGame(int i);              //游戏结束

void creatLink();
void insertNode(int x, int y);
void deleteNode();
void deleteLink();

int ch;                            //输入的命令
int hour, minute, second;          //时分秒
int length;                        //蛇的长度
int totTime, level;                //计时，等级
direct dir;                        //蛇前进方向
direct food;                       //食物的位置
node *head, *tail;                 //链表的头尾结点

int main()
{
	initscr();                     //curses程序开始
	initGame();
	signal(SIGALRM, show);
	getOrder();
	endwin();                      //curses程序结束
	return 0;
}

//初始化游戏
void initGame()
{
	cbreak();                      //打开终端的CBREAK模式
	noecho();                      //关闭回显
	curs_set(0);                   //光标置为不可见
	keypad(stdscr, true);          //为标准屏幕激活功能键
	srand(time(0));                //设置随机数种子
	hour = minute = second = 0;    //初始化数据
	totTime = 0;
	length = 1;
	dir.cx = 1;
	dir.cy = 0;
	ch = 'A';
	food.cx = rand() % COLS;
	food.cy = rand() % (LINES - 2) + 2;    //前两行显示信息
	creatLink();
	setTicker(20);
}

//设置计时器
int setTicker(int i)
{
	struct itimerval itv;
	long  n_sec, n_usecs;
	n_sec = i / 1000;
	n_usecs = (i % 1000) * 1000L;
	//间隔时间
	itv.it_interval.tv_sec = n_sec;
	itv.it_interval.tv_usec = n_usecs;
	i = 1;
	n_sec = i / 1000;
	n_usecs = (i % 1000) * 1000L;
	//初始启动时间
	itv.it_value.tv_sec = n_sec;
	itv.it_value.tv_usec = n_usecs;
	return setitimer(ITIMER_REAL, &itv, NULL);
}

//设置画面
void show()
{
	signal(SIGALRM, show);         //设置中断信号
	showInfo();
	showSnake();
	refresh();                     //刷新真实屏幕
}

//显示上方两行的游戏信息
void showInfo()
{
	totTime++;
	if (totTime >= 1000000)
		totTime = 0;
	if (1 != totTime % 50)
		return;             //不到1秒
	move(0, 3);
	//显示时间
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
	printw("length: %d", length);         //显示蛇的长度
	move(0, COLS - 10);
	level = length / 3 + 1;
	printw("level: %d", level);           //显示等级
}

//显示蛇
void showSnake()
{
	if (1 != totTime % (30 - level))
		return;
	bool lengCh = false;                
	move(food.cy, food.cx);               
	printw("@");                           //显示食物
	//当蛇碰到墙，则游戏结束
	if ((COLS - 1 == head->next->cx && 1 == dir.cx)
		|| (0 == head->next->cx && -1 == dir.cx)
		|| (LINES - 1 == head->next->cy && 1 == dir.cy)
		|| (2 == head->next->cy && -1 == dir.cy))
	{
		overGame(1);
		return;
	}
	//当蛇吃到自己身体，则游戏结束
	if ('*' == mvinch(head->next->cy + dir.cy, head->next->cx + dir.cx))
	{
		overGame(2);
		return;
	}
	insertNode(head->next->cx + dir.cx, head->next->cy + dir.cy);
	//当蛇吃了食物，则蛇身变长
	if (head->next->cx == food.cx && head->next->cy == food.cy)
	{
		lengCh = true;
		length++;
		//当成功吃完50个食物时，过关
		if (length >= 50)
		{
			overGame(3);
			return;
		}
		//重新设置下一个食物的位置
		food.cx = rand() % COLS;
		food.cy = rand() % (LINES - 2) + 2; 
	}
	//蛇正常前进，删除尾部结点，增加头部结点
	if (!lengCh)
	{
		move(tail->last->cy, tail->last->cx);
		printw(" ");
		deleteNode();
	}
	move(head->next->cy, head->next->cx);
	printw("*");
}

//游戏结束
void overGame(int i)
{
	move(0, 0);
	int j;
	for (j = 0; j < COLS; j++)
		addstr(" ");
	move(0, 2);                  //显示结束理由
	if (i == 1)
		addstr("Crash the wall. Game over!");
	else if (i == 2)
		addstr("Crash itself. Game over!");
	else if (i == 3)
		addstr("Pass the Game!");
	setTicker(0);                 //关闭计时器
	deleteLink();                 //释放整个链表
}

//读取键盘输入的命令
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

//创建蛇身，即一个双向链表
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

//在链表头部插入一个结点
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

//在链表尾部删除一个结点
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

//删除整个链表
void deleteLink()
{
	while (head->next != tail)
		deleteNode();
	head->next = tail->last = NULL;
	free(head);
	free(tail);
}