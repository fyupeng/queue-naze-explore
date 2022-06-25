#include<stdio.h>
#include<stdlib.h>
#include <windows.h> //头文件
#include "mouse.h"
#include "color.h"
#include<time.h>
#define MAXSIZE 500
#define M 10 /*迷宫高度，不含围墙*/
#define N 20 /*迷宫宽度，不含围墙*/

typedef struct
{
	int i,j;/*方块的位置*/
	int pre;/*搜索路径的上一个方块在队列中的位置*/ 
} ElemType;
typedef struct
{
	ElemType data[MAXSIZE];/*顺序队列的数据存储区*/
	int front,rear;/*队列的头尾指针*/ 
}SqQueue;
bool MazeShortestPath(int xi,int yi,int xe,int ye);
void print(SqQueue Q,int cur);
int maze[M+2][N+2]={1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
					1,0,0,0,0,1,0,0,1,0,0,0,0,0,0,1,1,0,0,1,0,1,
					1,0,1,1,0,1,0,0,1,1,0,1,1,0,0,1,1,1,0,1,0,1,
					1,0,0,0,0,1,0,1,1,1,0,1,1,0,1,0,0,1,0,0,0,1,
					1,0,1,1,0,1,0,1,0,1,0,0,1,0,1,1,0,1,1,0,1,1,
					1,1,0,0,0,0,1,1,0,1,1,0,1,0,0,0,0,0,1,0,0,1,
					1,0,0,1,0,0,0,1,0,0,0,1,1,1,1,1,0,1,0,0,1,1,
					1,0,0,1,0,1,1,1,0,1,0,0,0,1,1,1,0,1,1,0,1,1,
					1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
					1,0,1,1,1,1,0,1,0,1,1,1,1,0,1,1,1,1,0,1,0,1,
					1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,
					1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
					};
int main()
{
	int i,j,k;
	for(i=0;i<M+2;i++)
		for(j=0;j<N+2;j++){
			k=j*2;	
			if(maze[i][j]==1){
				gotoxy(k,i);
				printf("█");
			}	
		}
	MazeShortestPath(1,1,10,20);
	return 0;
}

bool MazeShortestPath(int xi,int yi,int xe,int ye)/*该算法是先探索子一代的所有可走方块并入队再探索子二代的方块，如果探索到路径出口，则停止继续探索，就是有其他出口也不会继续探索，故该路径最短*/
{/*搜索从（si,yi)到(xe,ye)的最短路径*/
	int i,j,di;
	ElemType e;
	SqQueue qu;   /*定义一个顺序队列*/
	qu.front=qu.rear=0;               /*初始化顺序队列*/ 
	e.i=xi;e.j=yi;e.pre=-1; /*入口点初始化数据元素e入队*/
	maze[e.i][e.j]=-1; /*初始化原始位置*/
	gotoxy(yi*2,xi);Sleep(500);printf("※");gotoxy(ye*2,xe);printf("※");
	qu.data[qu.rear]=e;
	qu.rear++;
	while(qu.front!=qu.rear){
		e=qu.data[qu.front];
		qu.front++;
		if(e.i==xe&&e.j==ye){
			print(qu,qu.front-1);/*qu为搜索路径的队列，qu.front-1为出口在队列中的位置*/
			gotoxy(20,25);
			return true;
		}
		for(di=0;di<4;di++){  //与栈探索迷宫不同在于队列可以从四个方向同时进行，对四个方位的方块依次入队，类似父子树 
			switch(di){
				case 0:i=e.i-1;j=e.j;break;
				case 1:i=e.i;j=e.j+1;break;
				case 2:i=e.i+1;j=e.j;break;
				case 3:i=e.i;j=e.j-1;break;
			}
			if(maze[i][j]==0){/*找到了下一个相邻可走方块，入队*/ 
				qu.data[qu.rear].i=i;
				qu.data[qu.rear].j=j;
				gotoxy(j*2,i);Sleep(150);printf("☆");
				qu.data[qu.rear].pre=qu.front-1;
				qu.rear++;
				maze[i][j]=-1;/*新入队的点的maze设为-1，避免在循环四个方向时重复走到该方块*/
			}
		}			
	}
	gotoxy(30,30);
	printf("迷宫无解！");
	return false; 
}

void print(SqQueue Q,int cur)
{/*定义一个动态数组模拟栈*/ 
	int i=cur,ns=0;
	ElemType *SqStack=(ElemType *)malloc(sizeof(ElemType)*cur);
	int top=0;/*初始化栈*/
	do{
		SqStack[top++]=Q.data[i];
		i=Q.data[i].pre;
	}while(i!=0);
	/*printf("The maze path:\n");*/
	while(top!=0){
		ns++;
		top--;
		gotoxy(SqStack[top].j*2,SqStack[top].i);Sleep(100);color(10);printf("█");color(0);
		
	/*	printf("(%d,%d)",SqStack[top].i,SqStack[top].j);
		if(ns%5==0)
			printf("\n");*/ 
	}
}
