#include<stdio.h>
#include<Windows.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>

#define KONG 0
#define WALL 1
#define BODY 2
#define FOOD 3
#define HEAD 4

#define ROW 22
#define COL 42

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define SPACE 32
#define ESC 27

struct body
{
	int x;
	int y;
}Body[ROW*COL];

struct snake
{
	int x;
	int y;
	int len;
}Snake; 

int face[ROW][COL];

void HideCursor();//
void CursorJump(int h,int j);//
void InitFace();//
void InitSnake();//
void MoveSnake(int ,int );//
void MakeSnake(int );//0覆盖，1打印 
void Game();//
void Color(int hhhh );//
void Readgrade();//
void Writegrade();// 
void Judgegrade(int ,int );
void RandFood();//
void Run(int ,int );//

int grade,max;
int main()
{
	grade=0,max=0;
	system("mode con cols=84 lines=23");
	system("title 贪吃蛇");
	HideCursor();
	Readgrade();
	InitFace();
	InitSnake();
	srand((unsigned)time(NULL));
	RandFood();
	Game();
	return 0;
}

void HideCursor()
{
	CONSOLE_CURSOR_INFO curinfo;
	curinfo.dwSize=1;
	curinfo.bVisible=FALSE;
	HANDLE handle=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(handle,&curinfo);
}
void CursorJump(int x,int y)
{
	COORD pos;
	pos.X=x;
	pos.Y=y;
	HANDLE handle=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(handle,pos);
}
void Color(int c)
{
	HANDLE handle=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle,c);
}
void InitFace()
{
	Color(6);
    for(int i=0;i<ROW;i++)
    {
		for(int j=0;j<COL;j++)
		{
			if(j==0 || j==COL-1)
			{
				CursorJump(j*2,i);
				printf("■");
				face[i][j]=WALL; 
			}
			else if(i==0 || i==ROW-1)
			{
				printf("■");
				face[i][j]=WALL;
			}
			else
			face[i][j]=KONG;
		}
	}
	Color(7);
	CursorJump(0,ROW);
	printf("当前得分:%d   一般",grade);
	CursorJump(COL,ROW);
	printf("最高得分:%d",max);
}
void InitSnake()
{
	Snake.len=2;
	Snake.x=COL/2;
	Snake.y=ROW/2;
	Body[0].x=COL/2-1;
	Body[0].y=ROW/2;
	Body[1].x=COL/2-2;
	Body[1].y=ROW/2;
	face[Snake.y][Snake.x]=HEAD;
	face[Body[0].y][Body[0].x]=BODY;
	face[Body[1].y][Body[1].x]=BODY;
	MakeSnake(1);
}
void MakeSnake(int n)
{
	if(n==0)
	{
		if(Body[Snake.len-1].x!=0)
		{
		  CursorJump(Body[Snake.len-1].x*2,Body[Snake.len-1].y);
		  printf("  ");
		}
	}
	else
	{
		CursorJump(2*Snake.x,Snake.y);
		Color(9);
		printf("■");
		for(int i=0;i<Snake.len;i++)
		{
			CursorJump(2*Body[i].x,Body[i].y);
			printf("□");
		} 
	}
}
void RandFood()
{
	int x,y;
	Color(4);
	x=rand()%COL;
	y=rand()%ROW;
	while(face[y][x]!=KONG)
	{
		x=rand()%COL;
		y=rand()%ROW;
	}
	CursorJump(x*2,y);
	face[y][x]=FOOD;
	printf("●"); 
}
void MoveSnake(int x,int y)
{
	MakeSnake(0);
	if(Body[Snake.len-1].x!=0)
	{
		face[Body[Snake.len-1].y][Body[Snake.len-1].x]=KONG;
	}
	face[Snake.y][Snake.x]=BODY;
	for(int i=Snake.len-1;i>0;i--)
	{
		Body[i].x=Body[i-1].x;
		Body[i].y=Body[i-1].y;
	}
	Body[0].x=Snake.x;
	Body[0].y=Snake.y;
	Snake.x=Snake.x+x;
	Snake.y=Snake.y+y;
	face[Snake.y][Snake.x]=HEAD;
	MakeSnake(1);
}
void Writegrade()
{
	FILE* pf=fopen("贪吃蛇最高得分记录.txt","w");
	if(pf==NULL)
	{
		printf("保存最高得分记录失败\n");
		exit(0);
	}
	fwrite(&grade,sizeof(int),1,pf);
	fclose(pf);
	pf=NULL;
}
void Readgrade()
{
	FILE* pf = fopen("贪吃蛇最高得分记录.txt", "r"); 
	if (pf == NULL) 
	{
		pf = fopen("贪吃蛇最高得分记录.txt", "w"); 
		fwrite(&max, sizeof(int), 1, pf); 
	}
	fseek(pf, 0, SEEK_SET);
	fread(&max, sizeof(int), 1, pf); 
	fclose(pf); 
	pf = NULL;
}
void Game()
{
	int tmp=0;
	int n=RIGHT;
	while(1)
	{
		switch(n)
		{
			case RIGHT:
				Run(1,0);
				tmp=RIGHT;
				break;
			case LEFT:
				Run(-1,0);
				tmp=LEFT;
				break;
			case UP:
				Run(0,-1);
				tmp=UP;
				break;
			case DOWN:
				Run(0,1);
				tmp=DOWN;
				break;
			case SPACE:
				system("pause>nul");
				break;
			case ESC:
				system("cls");
				CursorJump(COL,ROW/2);
				printf("游戏结束");
				CursorJump(0,ROW); 
				exit(-1);
			case 'r':
			case 'R':
				system("cls");
				main();
		}
		n=getch();
	switch(n)
		{
			case RIGHT:
				if(tmp!=UP && tmp!=DOWN)
				n=tmp;
				break;
			case LEFT:
				if(tmp!=UP && tmp!=DOWN)
				n=tmp;
				break;
			case UP:
				if(tmp!=LEFT && tmp!=RIGHT)
				n=tmp;
				break;
			case DOWN:
				if(tmp!=LEFT && tmp!=RIGHT)
				n=tmp;
				break;
			case SPACE:
			case ESC:
			case 'r':
			case 'R':break;
			default:
				n=tmp;
			    break;
		}
	}
}
void Run(int x,int y)
{
	int t=2800;
	while(1)
	{
		t=2800;
		while(t)
		{
			if(kbhit()!=0)
			break;
			t--;
		}
		if(t==0)
		{
			Judgegrade(x,y);
			MoveSnake(x,y);
		}
		else
		break;
	}
}
void Judgegrade(int x,int y)
{
	if(face[Snake.y+y][Snake.x+x]==FOOD)
	{
		Snake.len++;
		grade+=10;
		Color(7);
		CursorJump(0,ROW);
		if(grade<100)
		printf("当前得分:%d   一般",grade);
		else if(grade<250)
		printf("当前得分:%d   普通",grade);
		else
		printf("当前得分:%d   厉害",grade);
		RandFood();
	}
	else if(face[Snake.y+y][Snake.x+x]==BODY || face[Snake.y+y][Snake.x+x]==WALL)
	{
		Sleep(1000);
		system("cls");
		Color(7);
		CursorJump(COL-4,ROW/2);
		if(grade>max)
		 {
		 	printf("超过最高得分，当前得分：%d",grade);
		 	Writegrade();
		 }
		else if(grade==max)
		{
			printf("与最高分相同，当前得分：%d",grade);
		}
		else if(grade<max)
		{
			printf("与最高得分相差%d,当前得分：%d,再接再厉",max-grade,grade);
		}
		CursorJump(COL-4,ROW/3);
		printf("游戏结束");
		char n;
		while(1) 
		{
			CursorJump(COL-4,ROW/3+3);
			printf("再来一次（y/n):");
			scanf("%c",&n);
			if(n=='n' || n=='N')
			exit(-1);
			if(n=='y' || n=='Y')
			{
				system("cls");
				main();
			}	
		}
	}
}
