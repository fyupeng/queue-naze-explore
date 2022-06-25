#include<stdio.h>
#include<stdlib.h>
#include <windows.h> //ͷ�ļ�
#include "mouse.h"
#include "color.h"
#include<time.h>
#define MAXSIZE 500
#define M 10 /*�Թ��߶ȣ�����Χǽ*/
#define N 20 /*�Թ���ȣ�����Χǽ*/

typedef struct
{
	int i,j;/*�����λ��*/
	int pre;/*����·������һ�������ڶ����е�λ��*/ 
} ElemType;
typedef struct
{
	ElemType data[MAXSIZE];/*˳����е����ݴ洢��*/
	int front,rear;/*���е�ͷβָ��*/ 
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
				printf("��");
			}	
		}
	MazeShortestPath(1,1,10,20);
	return 0;
}

bool MazeShortestPath(int xi,int yi,int xe,int ye)/*���㷨����̽����һ�������п��߷��鲢�����̽���Ӷ����ķ��飬���̽����·�����ڣ���ֹͣ����̽������������������Ҳ�������̽�����ʸ�·�����*/
{/*�����ӣ�si,yi)��(xe,ye)�����·��*/
	int i,j,di;
	ElemType e;
	SqQueue qu;   /*����һ��˳�����*/
	qu.front=qu.rear=0;               /*��ʼ��˳�����*/ 
	e.i=xi;e.j=yi;e.pre=-1; /*��ڵ��ʼ������Ԫ��e���*/
	maze[e.i][e.j]=-1; /*��ʼ��ԭʼλ��*/
	gotoxy(yi*2,xi);Sleep(500);printf("��");gotoxy(ye*2,xe);printf("��");
	qu.data[qu.rear]=e;
	qu.rear++;
	while(qu.front!=qu.rear){
		e=qu.data[qu.front];
		qu.front++;
		if(e.i==xe&&e.j==ye){
			print(qu,qu.front-1);/*quΪ����·���Ķ��У�qu.front-1Ϊ�����ڶ����е�λ��*/
			gotoxy(20,25);
			return true;
		}
		for(di=0;di<4;di++){  //��ջ̽���Թ���ͬ���ڶ��п��Դ��ĸ�����ͬʱ���У����ĸ���λ�ķ���������ӣ����Ƹ����� 
			switch(di){
				case 0:i=e.i-1;j=e.j;break;
				case 1:i=e.i;j=e.j+1;break;
				case 2:i=e.i+1;j=e.j;break;
				case 3:i=e.i;j=e.j-1;break;
			}
			if(maze[i][j]==0){/*�ҵ�����һ�����ڿ��߷��飬���*/ 
				qu.data[qu.rear].i=i;
				qu.data[qu.rear].j=j;
				gotoxy(j*2,i);Sleep(150);printf("��");
				qu.data[qu.rear].pre=qu.front-1;
				qu.rear++;
				maze[i][j]=-1;/*����ӵĵ��maze��Ϊ-1��������ѭ���ĸ�����ʱ�ظ��ߵ��÷���*/
			}
		}			
	}
	gotoxy(30,30);
	printf("�Թ��޽⣡");
	return false; 
}

void print(SqQueue Q,int cur)
{/*����һ����̬����ģ��ջ*/ 
	int i=cur,ns=0;
	ElemType *SqStack=(ElemType *)malloc(sizeof(ElemType)*cur);
	int top=0;/*��ʼ��ջ*/
	do{
		SqStack[top++]=Q.data[i];
		i=Q.data[i].pre;
	}while(i!=0);
	/*printf("The maze path:\n");*/
	while(top!=0){
		ns++;
		top--;
		gotoxy(SqStack[top].j*2,SqStack[top].i);Sleep(100);color(10);printf("��");color(0);
		
	/*	printf("(%d,%d)",SqStack[top].i,SqStack[top].j);
		if(ns%5==0)
			printf("\n");*/ 
	}
}
