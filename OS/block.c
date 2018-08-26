//����˹���� 
//block.c
//�������gcc block.c -o block 
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

#define ROW 21     //��Ϸ�������
#define COL 18     //��Ϸ�������
#define NR   4     //�������
#define TYPE 7     //��������

//���������
char blocks[TYPE][NR][NR][NR] = 
{
	{//��һ�ַ���
		{//��һ������
			{1,1,0,0},
			{1,1,0,0},
			{0,0,0,0},
			{0,0,0,0},
         },
		 {//�ڶ�������
			 { 1,1,0,0 },
			 { 1,1,0,0 },
			 { 0,0,0,0 },
			 { 0,0,0,0 },
		 },
		 {//����������
			 { 1,1,0,0 },
			 { 1,1,0,0 },
			 { 0,0,0,0 },
			 { 0,0,0,0 },
		 },
		 {//���ĸ�����
			 { 1,1,0,0 },
			 { 1,1,0,0 },
			 { 0,0,0,0 },
			 { 0,0,0,0 },
		 },
	},
	{//�ڶ��ַ���
		{//��һ������
			{ 2,2,2,2 },
			{ 0,0,0,0 },
			{ 0,0,0,0 },
			{ 0,0,0,0 },
		},
		{//�ڶ�������
			{ 0,2,0,0 },
			{ 0,2,0,0 },
			{ 0,2,0,0 },
			{ 0,2,0,0 },
		},
		{//����������
			{ 2,2,2,2 },
			{ 0,0,0,0 },
			{ 0,0,0,0 },
			{ 0,0,0,0 },
		},
		{//���ĸ�����
			{ 0,2,0,0 },
			{ 0,2,0,0 },
			{ 0,2,0,0 },
			{ 0,2,0,0 },
		},
	},
	{//�����ַ���
		{//��һ������
			{ 3,0,0,0 },
			{ 3,3,3,0 },
			{ 0,0,0,0 },
			{ 0,0,0,0 },
		},
		{//�ڶ�������
			{ 0,3,3,0 },
			{ 0,3,0,0 },
			{ 0,3,0,0 },
			{ 0,0,0,0 },
		},
		{//����������
			{ 3,3,3,0 },
			{ 0,0,3,0 },
			{ 0,0,0,0 },
			{ 0,0,0,0 },
		},
		{//���ĸ�����
			{ 0,0,3,0 },
			{ 0,0,3,0 },
			{ 0,3,3,0 },
			{ 0,0,0,0 },
		},
	},
	{//�����ַ���
		{//��һ������
			{ 0,0,4,0 },
			{ 4,4,4,0 },
			{ 0,0,0,0 },
			{ 0,0,0,0 },
		},
		{//�ڶ�������
			{ 0,4,0,0 },
			{ 0,4,0,0 },
			{ 0,4,4,0 },
			{ 0,0,0,0 },
		},
		{//����������
			{ 0,4,4,4 },
			{ 0,4,0,0 },
			{ 0,0,0,0 },
			{ 0,0,0,0 },
		},
		{//���ĸ�����
			{ 0,4,4,0 },
			{ 0,0,4,0 },
			{ 0,0,4,0 },
			{ 0,0,0,0 },
		},
	},
	{//�����ַ���
		{//��һ������
			{ 0,5,0,0 },
			{ 5,5,5,0 },
			{ 0,0,0,0 },
			{ 0,0,0,0 },
		},
		{//�ڶ�������
			{ 0,5,0,0 },
			{ 0,5,5,0 },
			{ 0,5,0,0 },
			{ 0,0,0,0 },
		},
		{//����������
			{ 5,5,5,0 },
			{ 0,5,0,0 },
			{ 0,0,0,0 },
			{ 0,0,0,0 },
		},
		{//���ĸ�����
			{ 0,5,0,0 },
			{ 5,5,0,0 },
			{ 0,5,0,0 },
			{ 0,0,0,0 },
		},
	},
	{//�����ַ���
		{//��һ������
			{ 6,6,0,0 },
			{ 0,6,6,0 },
			{ 0,0,0,0 },
			{ 0,0,0,0 },
		},
		{//�ڶ�������
			{ 0,0,6,0 },
			{ 0,6,6,0 },
			{ 0,6,0,0 },
			{ 0,0,0,0 },
		},
		{//����������
			{ 6,6,0,0 },
			{ 0,6,6,0 },
			{ 0,0,0,0 },
			{ 0,0,0,0 },
		},
		{//���ĸ�����
			{ 0,0,6,0 },
			{ 0,6,6,0 },
			{ 0,6,0,0 },
			{ 0,0,0,0 },
		},
	},
	{//�����ַ���
		{//��һ������
			{ 0,7,7,0 },
			{ 7,7,0,0 },
			{ 0,0,0,0 },
			{ 0,0,0,0 },
		},
		{//�ڶ�������
			{ 0,7,0,0 },
			{ 0,7,7,0 },
			{ 0,0,7,0 },
			{ 0,0,0,0 },
		},
		{//����������
			{ 0,0,7,7 },
			{ 0,7,7,0 },
			{ 0,0,0,0 },
			{ 0,0,0,0 },
		},
		{//���ĸ�����
			{ 0,7,0,0 },
			{ 0,7,7,0 },
			{ 0,0,7,0 },
			{ 0,0,0,0 },
		},
	},
};

//������������
enum key {
	DOWN,     //��
	FALL,     //ֱ�µ���
	LEFT,     //��
	RIGHT,    //��
	CHANGE,   //�仯
	PAUSE,    //��ͣ
	EXIT,     //�˳�
	UNKNOW,   //δ֪
};

//��������
void initGame();                        //��ʼ����Ϸ
void drawBlock(char bl[NR][NR]);        //������
void cleanBlock(char bl[NR][NR]);       //�������
void turnBlock(char bl[NR][NR]);        //��ת����
void overGame();                        //������Ϸ
void pauseGame();                       //��ͣ��Ϸ
void show();                            //��ʾ��Ϸ����
void gameRun(int signo);                //��Ϸ����
void checkLine();                       //����Ƿ���һ��
void checkOver(char bl[NR][NR]);        //����Ƿ���Ϸ����
int  checkMove(char bl[NR][NR], int flag); //��鷽���Ƿ���ƶ�
int  getInput(void);                       //��ȡ����

//ȫ�ֱ���
static char gameArea[ROW][COL] = { 0 };   //��Ϸ����
static int startX = 7, startY = 6;        //�������λ��
static int type = 0;                      //��ǰ��������
static int nextType = 0;                  //�¸���������
static int direct = 0;                    //���鷽��
char *gameState = "\033[33m Playing...\033[0m";//��Ϸ״̬
static unsigned int level = 0;            //�ȼ�
static unsigned int score = 0;            //����
static unsigned int highScore = 0;        //��߷�
static FILE *fp = NULL;                   //��¼�������ļ���

int main()
{
	struct itimerval itiv = { {0,700000},{0,700000} }; //���ö�ʱ��
	setitimer(ITIMER_REAL, &itiv, NULL);
	initGame();
	signal(SIGALRM, gameRun);

	srand(time(0));                                    //�������������
	type = rand() % 7;                                 //��ʼ����������
	nextType = rand() % 7;

	fp = fopen("./record", "r+");                      //��ȡ��߼�¼
	if (fp == NULL)
	{   //�ļ�������ʱ����
		fp = fopen("./record", "w");
	}
	fscanf(fp, "%u", &highScore);

	int order;
	while (1)
	{
		order = getInput();                           //�û�����
		switch (order)
		{
		case RIGHT:checkMove(blocks[type][direct], RIGHT);
			break;
		case LEFT:checkMove(blocks[type][direct], LEFT);
			break;
		case FALL:checkMove(blocks[type][direct], FALL);
			break;
		case CHANGE:turnBlock(blocks[type][(direct + 1) % 4]);
			break;
		case PAUSE:pauseGame();
			break;
		case EXIT:overGame();
			break;
		case UNKNOW:continue;
		}

		drawBlock(blocks[type][direct]);             //������
		show();                                      //��ʾ����
		cleanBlock(blocks[type][direct]);            //�������
	}
	return 0;
}

//��ʼ����Ϸ
void initGame()
{
	printf("\033[2J");            //����
	system("stty -icanon");       //�ػ���
	system("stty -echo");         //�ػ���
	fprintf(stdout, "\033[?25l"); //�ر������ʾ
	//����һЩ�߽�
	int i;
	for (i = 0; i < COL; i++) {
		gameArea[0][i] = 8;
		gameArea[5][i] = 8;
		gameArea[ROW - 1][i] = 8;
	}
	for (i = 0; i < ROW; i++)
	{
		gameArea[i][0] = 8;
		gameArea[i][COL - 1] = 8;
	}
	for (i = 1; i < 5; i++)
	{
		gameArea[i][6] = 8;
	}
}

//��ʾ����
void drawBlock(char block[NR][NR])
{
	int x, y;
	//��ǰ����
	for (y = 0; y < NR; y++)
	{
		for (x = 0; x < NR; x++)
		{
			if (block[y][x] != 0)
			{
				gameArea[startY + y][startX + x] = block[y][x];
			}
		}
	}

	//��һ������
	for (x = 0; x < 2; x++)
	{
		for (y = 0; y < NR; y++)
		{
			if (blocks[nextType][0][x][y] != 0)
				gameArea[3 + x][2 + y] = blocks[nextType][0][x][y];
			else
				gameArea[3 + x][2 + y] = 0;
		}
	}
}

//�������
void cleanBlock(char block[NR][NR])
{
	int x, y;
	for (y = 0; y < NR; y++)
	{
		for (x = 0; x < NR; x++)
		{
			if (block[y][x] != 0)
			{
				gameArea[startY + y][startX + x] = 0;
			}
		}
	}
}

//��ת����
void turnBlock(char block[NR][NR])
{
	int x, y;
	//����Ƿ�Խ��
	for (y = 0; y < NR; y++)
	{
		for (x = 0; x < NR; x++)
		{
			if (block[y][x] != 0 && gameArea[startY + y][startX + x] != 0)
			{
				return;
			}
		}
	}
	direct = (direct + 1) % 4;    //�ı䷽��
}

//��ʾ��Ϸ����
void show()
{
	fprintf(stdout, "\033[1;1H");  //��λ����һ�е�һ��
	fflush(stdout);
	int i, j;
	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < COL; j++)
		{
			if (gameArea[i][j] == 0)     //�հ�����
			{
				fprintf(stdout, "  ");
			}
			else if (gameArea[i][j] == 8) //�߽�����
			{
				fprintf(stdout, "\033[40m  \033[0m");
			}
			else                          //��������
			{
				fprintf(stdout, "\033[%dm[]\033[0m", gameArea[i][j] + 40);
			}
		}
		fputc('\n', stdout);
	}
	//��Ϸ��Ϣ
	fprintf(stdout, "\033[2;3H\033[33m��NEXT��\033[0m\n");
	fprintf(stdout, "\033[2;15H Level:\033[36m%u\033[0m\n", level);
	fprintf(stdout, "\033[3;15H Score:\033[32m%u\033[0m\n", score);
	fprintf(stdout, "\033[4;15H HighScore:\033[35m%u\033[0m\n", highScore);
	fprintf(stdout, "\033[5;15H State:%s\n", gameState);
}

//�����Զ�����
void gameRun(int signo)
{
	drawBlock(blocks[type][direct]);
	show();
	cleanBlock(blocks[type][direct]);
	//�������Ѿ�����ʱ
	if (!checkMove(blocks[type][direct], DOWN))
	{
		checkOver(blocks[type][direct]);  //�����Ϸ�Ƿ����
		drawBlock(blocks[type][direct]);  //�����ѵ��׵ķ���
		show();                           //��ʾ��Ϸ���
		checkLine();                      //����Ƿ��������
		//���¿�ʼ��һ������
		struct itimerval itiv = { { 0,700000 },{ 0,700000 } }; //���ö�ʱ��
		setitimer(ITIMER_REAL, &itiv, NULL);
		startY = 6;
		startX = 7;
		type = nextType;
		nextType = rand() % 7;
		direct = 0;
	}
}

//����Ƿ����ȥ
void checkLine()
{
	int i, j, x, y;
	for (i = 3; i >= 0; i--)
	{
		for (j = 1; j < COL - 1; j++)
		{
			if (gameArea[startY + i][j] == 0) //�����Ƿ���һ��
				break;
			else if (gameArea[startY + i][j] == 8)//�����߽�����
				break;
		}
		if (j == COL - 1) //������һ����������
		{
			for (j = 1; j < COL - 1; j++)
			{
				gameArea[startY + i][j] = 0;
			}

			score += 100; //�����ۼ�
			if (score > highScore) //��߷�
			{
				highScore = score;
				rewind(fp);
				fprintf(fp, "%u\n", highScore);
			}
			if (score % 300 == 0) //ÿ300����һ��
			{
				level++;
			}

			for (x = 1; x < COL - 1; x++) //�����ƶ�һ��
			{
				for (y = startY + i; y >= 7; y--)
				{
					gameArea[y][x] = gameArea[y - 1][x];
				}
			}
			i++;
		}
	}
}

//�����Ϸ�Ƿ����
void checkOver(char block[NR][NR])
{
	int i;
	for (i = 0; i < NR; i++)
	{   //���������Ϸ��߽�
		if (block[0][i] != 0 && gameArea[startY - 1][startX + i] == 8)
		{
			overGame();
		}
	}
}

//��鷽���ܷ��ƶ�
int checkMove(char block[NR][NR], int flag)
{
	int x, y;//��ʾ���ƶ��ķ���
	switch (flag)
	{
	case RIGHT:x = 1; y = 0; break;
	case LEFT:x = -1; y = 0; break;
	case DOWN:x = 0; y = 1; break;
	case FALL:x = 0; y = 1;
		struct itimerval itiv = { { 0,10000 },{ 0,10000 } }; //���ö�ʱ��
		setitimer(ITIMER_REAL, &itiv, NULL);
		break;
	}

	int i, j;
	for (i = 0; i < NR; i++)
	{
		for (j = 0; j < NR; j++)
		{   //�ᴥ���߽�
			if (block[i][j] != 0 && gameArea[startY + y + i][startX + x + j] != 0)
			{
				return 0;
			}
		}
	}
	startY += y;
	startX += x;

	return 1;
}

//��ȡ�û���������
int getInput()
{
	char key;
	key = fgetc(stdin);

	if (key == '\033' && fgetc(stdin) == '[')  //�����
	{
		switch (fgetc(stdin))
		{
		case 'A':return CHANGE;
		case 'B':return FALL;
		case 'C':return RIGHT;
		case 'D':return LEFT;
		default:return UNKNOW;
		}
	}
	else if (key == ' ')   //�ո��
	{
		return PAUSE;
	}
	else if (key == 'q')  //�˳���
	{
		return EXIT;
	}
	else                 //�����
	{
		return UNKNOW;
	}
}

//��ͣ��Ϸ
void pauseGame()
{
	struct  itimerval stop = { 0 }, older; //����һ����ͣʱ��
	setitimer(ITIMER_REAL, &stop, &older);

	gameState = "\033[32m Pause...\033[0m";
	startY--;   //��ֹ������ͣ���󷽿��»�һ��
	drawBlock(blocks[type][direct]);
	show();
	cleanBlock(blocks[type][direct]);

	int key;
	while (1)
	{
		key = fgetc(stdin);
		if (key == ' ')
			break;
		else if (key == 'q')
			overGame();
	}
	//�ָ���Ϸ
	setitimer(ITIMER_REAL, &older, NULL);

	gameState = "\033[33m Playing...\033[0m";
}

//������Ϸ
void overGame()
{
	gameState = "\033[32m Game Over...\033[0m";
	drawBlock(blocks[type][direct]);
	show();

	//�ָ��ն�����
	system("stty icanon");          //�ָ�����
	system("stty echo");            //�ָ�����
	fprintf(stdout, "\033[?25h");   //�ָ������ʾ

    //β������
	fprintf(stdout, "\033[200;1H"); //��λ��굽���һ��
	fclose(fp);                     //�ر��ļ�
	exit(0);                        //�˳�����
}
