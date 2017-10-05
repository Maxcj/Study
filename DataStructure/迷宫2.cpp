#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define STACK_INIT_SIZE 100//存储空间初始分配量
#define STACKINCREMENT 10//储存空间增量分配

//函数返回值
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define OVERFLOW 0

#define M 10 //迷宫行数
#define N 10//迷宫列数

typedef struct{
	char s[M][N];//迷宫
}MazeType;//定义迷宫

typedef struct{
	int pi;//父节点的行号
	int pj;//父节点的列号
	int i;//当前节点的行号
	int j;//当前节点的列号
}SElemType;//定义栈元素

typedef struct{
	int i;//当前节点行号
	int j;//当前节点列号
}Node;//定义节点类型

typedef struct{
	SElemType *top;
	SElemType *base;
	int stacksize;
}SqStack;//定义栈

//定义函数类型
typedef int Status;

Status InitStack(SqStack &S){
	//初始化栈
	S.base = (SElemType *)malloc(STACK_INIT_SIZE//存储空间初始分配量
		* sizeof(SElemType));
	if (!S.base) exit(OVERFLOW);
	S.top = S.base;
	S.stacksize = STACK_INIT_SIZE; //存储空间初始分配量
	return OK;
}//InitStack

Status StackEmpty(SqStack S){
	//判断栈是否为空，空返回TRUE，否则返回FALSE
	if (S.top == S.base) return TRUE;
	return FALSE;
}//StackEmpty

Status GetTop(SqStack S, SElemType &e){
	//若栈不为空，用e返回栈顶元素的值
	if (S.top == S.base) return ERROR;
	e = *(S.top - 1);
	return OK;
}//GetTop

Status Push(SqStack &S, SElemType e){
	//堆栈
	if (S.top - S.base >= S.stacksize){//栈满 增加存储空间
		S.base = (SElemType *)realloc(S.base, (S.stacksize + STACK_INIT_SIZE)*sizeof(SElemType));
		if (!S.base) exit(OVERFLOW);//存储空间分配失败
		S.top = S.base + S.stacksize;
		S.stacksize += STACK_INIT_SIZE;
	}
	*S.top++ = e;
	return OK;
}//Push

Status Pop(SqStack &S, SElemType &e){
	//弹栈
	//printf("%d ", S.top - S.base);
	if (S.top == S.base) return ERROR;
	e = *--S.top;
	//printf("%d ", e);
	return OK;
} // Pop

Status InitMaze(MazeType &m){
	//初始化迷宫
	int i, j;
	char ms[M+1][N];
	printf("请输入迷宫：\n");
	for (i = 0; i < M; i++)
	{
			gets(ms[i]);
	}
	for (i = 0; i < M; i++){
		for (j = 0; j < N; j++){
			m.s[i][j] = ms[i][j];//将初始保存到结构体中
		}
	}
	return OK;
}//InitMaze

Status PrintMaze(MazeType &m){
//输出迷宫
	int i, j;
	printf("输出迷宫：\n");
	for (i = 0; i < M; i++)
	{
		for (j = 0; j < N; j++)
		{
			printf("%c",m.s[i][j]);
		}
	    printf("\n");
	}
	return OK;
}

Status GetNextNode(Node e1,int di,Node &e2){
	switch (di){
	case 1:
	{
			   e2.i = e1.i + 1;
			   e2.j = e1.j;
			   break;
	}
	case 2:
	{
			  e2.i = e1.i;
			  e2.j = e1.j+1;
			  break;
	}
	case 3:
	{
			  e2.i = e1.i-1;
			  e2.j = e1.j ;
			  break;
	}
	case 4:
	{
			  e2.i = e1.i;
			  e2.j = e1.j -1;
			  break;
	}
	}
	return OK;
};

int compassable(MazeType &m, Node e){
	if(m.s[e.i][e.j]==' ')return OK;
	return 0;
}

void SearchPath(MazeType &m)
{
	SqStack s,d;
	Node e1, e2, end;
	SElemType se, se1, p[100];
	int i = 0, di, j;

	InitStack(s);//初始化open栈
	InitStack(d);//初始化print栈

	//指定路口
	e1.i = 1; e1.j = 1;
	//指定出口
	end.i = 8; end.j = 8;
	//构造栈元素
	se.pi = 0; se.pj = 0; se.i = e1.i; se.j = e1.j;
	Push(s, se);

	while (!StackEmpty(s)){
		Pop(s, se);
		//将se插入closed表中
		p[i].i = se.i;
		p[i].j = se.j;
		p[i].pi = se.pi;
		p[i].pj = se.pj;
		i++;
		
		//判断是否到达终点，如果到达终点则跳出while循环。
		if (se.i == end.i &&se.j == end.j){ printf("\nThe path have found:\n"); break; }
		
		//没有到达终点则将se的下一代可行节点入栈
		e1.i = se.i; e1.j = se.j;
		for (di = 1; di <= 4; di++)
		{
			GetNextNode(e1,di,e2 );
			if (compassable(m, e2))
			{//构造栈元素
				se1.i = e2.i;
				se1.j = e2.j;
				se1.pj = se.j;
				se1.pi = se.i;
				//下一代可通节点
				Push(s, se1);
				//留下足迹
				m.s[e2.i][e2.j] = '+';
			}//endif
		}//endfor
	}//endwhile
	if (StackEmpty(s))printf("\nfound no");
	else
		for (j = 0; j < i; j++)
		printf("i=%d,j=%d,pj=%d,pj=%d\n", p[j].i, p[j].j, p[j].pi, p[j].pj);
	/*{
		j = i - 2;
		Push(d, p[i - 1]);
		while (j)
		{
			GetTop(d, e);
			if (e.pi != p[j].i || e.pj != p[j].j)j--;
			else
				Push(d, p[j]);
		}//whileend
		if (!StackEmpty(d)){
			Pop(d, e);
			printf("(%d,%d)\n", e.i, e.j);
		}//ifend
	}//elseend//优化*/
}

void main()
{
	MazeType m;
	InitMaze(m);
	//PrintMaze(m);
	SearchPath(m);
	PrintMaze(m);
	system("pause");
}
