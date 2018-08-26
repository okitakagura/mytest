//������Ϸ 
//ball.c
//�������gcc ball.c -lcurses -o ball 
#include <curses.h>
#include <sys/time.h>
#include <signal.h>
#include <unistd.h>

#define RIGHT COLS-1     //��Ļ����
#define BOTTOM LINES-1   //��Ļ���
#define LEFT 0           //��Ļ����
#define TOP 1            //��Ļ�
#define BOARD_LENGTH 10  //���峤��

//��������
int set_ticker(int i);
void initGame();   //��ʼ����Ϸ
void pauseGame();  //��ͣ��Ϸ 
void showTime();   //��ʾʱ�� 
void moveBall();   //����˶�
void control();    //�û�����Ŀ�������

//ȫ�ֱ���
char BALL = 'O';   //�����״
char BLANK = ' ';  //�ո�

int left_board;    //����������
int right_board;   //����������
int is_lose = 0;   //��־���Ƿ����
int ntime = 100;   //��ʱ��ʱ��

int hdir;   //������ˮƽ�˶��ı���
int vdir;   //������ֱ�˶��ı���
int pos_X;  //��ĺ�����
int pos_Y;  //���������

int totTime, hour, minute, second; //ʱ����

int main()
{
	initscr(); //curses����ʼ
	crmode();  //�ն�ģʽ
	noecho();  //�رջ���

	move(6, 28);
	attron(A_BOLD);
	addstr("Welcome to the BallGame!");
	move(8, 20);
	attroff(A_BOLD);
	addstr("Help:");
	move(9, 23);
	addstr("'N':Start a new game.");
	move(10, 23);
	addstr("'Q':Quit game.");
	move(11, 23);
	addstr("'SPACE':Pause game.");
	move(12, 23);
	addstr("'KEY_LEFT' :Control baffle left  shift.");
	move(13, 23);
	addstr("'KEY_RIGHT':Control baffle right shift.");
	move(14, 23);
	addstr("'KEY_UP'   :Control of the ball speed.");
	move(15, 23);
	addstr("'KEY_DOWN' :Control of the ball reducer.");
	int flag = 1;
	char choice;
	move(17, 24);
	addstr("Please choose your choice!(n/q):");
	refresh();
	choice = getch();
	while (flag)
	{
		if (choice == 'q' || choice == 'Q' || choice == 'n' || choice == 'N')
		{
			flag = 0;
		}
		else
			choice = getch();
	}
	if (choice == 'n' || choice == 'N')  //��ʼ��Ϸ
	{
		clear();
		move(10, 25);
		addstr("BallGame will start! Are you read?");
		refresh();
		sleep(2);
		control();
	}
	else if (choice == 'q' || choice == 'Q') //�˳���Ϸ
	{
		clear();
		move(10, 25);
		addstr("You quit the game successfully!");
		refresh();
		sleep(2);
		endwin();
	}
	endwin();
	return 0;
}

//���ö�ʱ��
int set_ticker(int i)
{
	struct itimerval itv;
	long n_sec, n_usecs;
	n_sec = i / 1000;
	n_usecs = (i % 1000) * 1000L;
	//���ʱ��
	itv.it_interval.tv_sec = n_sec;
	itv.it_interval.tv_usec = n_usecs;
	//��ʼ����ʱ��
	itv.it_value.tv_sec = n_sec;
	itv.it_value.tv_usec = n_usecs;
	return setitimer(ITIMER_REAL, &itv, NULL);
}

//��ʾʱ����Ϣ
void showTime()
{
	totTime++;
	if (totTime >= 1000000)
		totTime = 0;
	if (1 != totTime % (1000 / ntime))
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
}
//��ʼ����Ϸ
void initGame()
{
	totTime = 0;
	hour = minute = second = 0;
	int i, j;
	clear();
	if (start_color() == OK) //������ɫ
	{
		attron(A_BOLD);
		init_pair(1, COLOR_CYAN, COLOR_BLACK);
		attron(COLOR_PAIR(1));
	}
	pos_X = 20;             //���ʼ�ĺ�����
	pos_Y = BOTTOM - 1;     //���ʼ��������
	hdir = 1;               //���ʼ���˶����������Ϸ�
	vdir = -1;

	//��ʼ������
	left_board = 15;
	right_board = left_board + BOARD_LENGTH;
	for (i = left_board; i <= right_board; i++)
	{
		move(BOTTOM, i);
		addch('-');
	}

	signal(SIGALRM, moveBall);
	set_ticker(ntime);           //���ö�ʱ
	keypad(stdscr, TRUE);      //�򿪼�������
	curs_set(0);               //�����Ϊ���ɼ�
	attroff(A_BLINK);          //�ر�A_BLINK����

	is_lose = 0;
	move(pos_Y, pos_X);
	addch(BALL);
	move(LINES - 1, COLS - 1);
	refresh();
	usleep(100000);
	move(LINES - 1, COLS - 1);
	refresh();
}

//��ͣ��Ϸ 
void pauseGame()
{
	struct  itimerval stop = { 0 }, older; //����һ����ͣʱ��
	setitimer(ITIMER_REAL, &stop, &older);
	moveBall();
	int key;
	while(1)
	{
		key = getch();
		if (key == ' ')
			break;
	}
	setitimer(ITIMER_REAL, &older, NULL);
}

//����˶�
void moveBall()
{
	showTime();
	if (is_lose)     //���ѵ���
		return;
	signal(SIGALRM, moveBall);
	move(pos_Y, pos_X);
	addch(BLANK);
	pos_X += hdir;
	pos_Y += vdir;
	//������ķ����˶�
	if (pos_X >= RIGHT)
	{
		hdir = -1;
		beep();
	}
	if (pos_X <= LEFT)
	{
		hdir = 1;
		beep();
	}
	if (pos_Y <= TOP + 1)
	{
		vdir = 1;
		beep();
	}
	if (pos_Y >= BOTTOM - 1)
	{
		if (pos_X >= left_board && pos_X <= right_board) //�����ڵ�����
			vdir = -1; //���Ϸ���
		else
		{
			is_lose = 1;
			move(pos_Y, pos_X);
			addch(BALL);
			move(LINES - 1, COLS - 1);
			refresh();
			usleep(100000);
			move(pos_Y, pos_X);
			addch(BLANK);
			pos_X += hdir;
			pos_Y += vdir;
			move(pos_Y, pos_X);
			addch(BALL);
			move(LINES - 1, COLS - 1);
			refresh();
		}
	}
	move(pos_Y, pos_X);
	addch(BALL);
	move(LINES - 1, COLS - 1);
	refresh();
}

//��ȡ�û�����Ŀ�������
void control()
{
	initGame();
	int cmd;
	while (1)
	{
		if (!is_lose)
		{
			cmd = getch();
			if (cmd == 'q' || cmd == 'Q' || cmd == 27)   //�˳���Ϸ
				break;
			if (cmd == ' ')        //��ͣ��Ϸ
			    pauseGame(); 
			if (cmd == KEY_LEFT)   //��������
			{
				if (left_board > 0)//�жϱ߽�
				{
					move(BOTTOM, right_board);
					addch(' ');
					right_board--;
					left_board--;
					move(BOTTOM, left_board);
					addch('-');
					move(BOTTOM, RIGHT);
					refresh();
				}
			}
			else if (cmd == KEY_RIGHT)//��������
			{
				if (right_board < RIGHT)//�жϱ߽�
				{
					move(BOTTOM, left_board);
					addch(' ');
					right_board++;
					left_board++;
					move(BOTTOM, right_board);
					addch('-');
					move(BOTTOM, RIGHT);
					refresh();
				}
			}
			else if (cmd == KEY_UP)  //�����
			{
				ntime /= 2;
				set_ticker(ntime);
			}
			else if (cmd == KEY_DOWN)//�����
			{
				ntime *= 2;
				set_ticker(ntime);
			}
		}

		else   //������Ĳ���
		{
			int flag = 1;
			char choice;
			move(8, 15);
			addstr("Game Over!try again?(y/n):");
			curs_set(1);
			refresh();
			choice = getch();
			while (flag)
			{
				if (choice == 'y' || choice == 'Y' || choice == 'n' || choice == 'N')
				{
					flag = 0;
				}
				else
					choice = getch();
			}
			if (choice == 'y' || choice == 'Y') //��ʼ����Ϸ
			{
				ntime = 100;
				initGame();
				continue;
			}
			else if (choice == 'n' || choice == 'N')//������Ϸ
			{
				break;
			}
		}
	}
}

