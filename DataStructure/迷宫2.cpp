#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define STACK_INIT_SIZE 100//�洢�ռ��ʼ������
#define STACKINCREMENT 10//����ռ���������

//��������ֵ
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define OVERFLOW 0

#define M 10 //�Թ�����
#define N 10//�Թ�����

typedef struct{
	char s[M][N];//�Թ�
}MazeType;//�����Թ�

typedef struct{
	int pi;//���ڵ���к�
	int pj;//���ڵ���к�
	int i;//��ǰ�ڵ���к�
	int j;//��ǰ�ڵ���к�
}SElemType;//����ջԪ��

typedef struct{
	int i;//��ǰ�ڵ��к�
	int j;//��ǰ�ڵ��к�
}Node;//����ڵ�����

typedef struct{
	SElemType *top;
	SElemType *base;
	int stacksize;
}SqStack;//����ջ

//���庯������
typedef int Status;

Status InitStack(SqStack &S){
	//��ʼ��ջ
	S.base = (SElemType *)malloc(STACK_INIT_SIZE//�洢�ռ��ʼ������
		* sizeof(SElemType));
	if (!S.base) exit(OVERFLOW);
	S.top = S.base;
	S.stacksize = STACK_INIT_SIZE; //�洢�ռ��ʼ������
	return OK;
}//InitStack

Status StackEmpty(SqStack S){
	//�ж�ջ�Ƿ�Ϊ�գ��շ���TRUE�����򷵻�FALSE
	if (S.top == S.base) return TRUE;
	return FALSE;
}//StackEmpty

Status GetTop(SqStack S, SElemType &e){
	//��ջ��Ϊ�գ���e����ջ��Ԫ�ص�ֵ
	if (S.top == S.base) return ERROR;
	e = *(S.top - 1);
	return OK;
}//GetTop

Status Push(SqStack &S, SElemType e){
	//��ջ
	if (S.top - S.base >= S.stacksize){//ջ�� ���Ӵ洢�ռ�
		S.base = (SElemType *)realloc(S.base, (S.stacksize + STACK_INIT_SIZE)*sizeof(SElemType));
		if (!S.base) exit(OVERFLOW);//�洢�ռ����ʧ��
		S.top = S.base + S.stacksize;
		S.stacksize += STACK_INIT_SIZE;
	}
	*S.top++ = e;
	return OK;
}//Push

Status Pop(SqStack &S, SElemType &e){
	//��ջ
	//printf("%d ", S.top - S.base);
	if (S.top == S.base) return ERROR;
	e = *--S.top;
	//printf("%d ", e);
	return OK;
} // Pop

Status InitMaze(MazeType &m){
	//��ʼ���Թ�
	int i, j;
	char ms[M+1][N];
	printf("�������Թ���\n");
	for (i = 0; i < M; i++)
	{
			gets(ms[i]);
	}
	for (i = 0; i < M; i++){
		for (j = 0; j < N; j++){
			m.s[i][j] = ms[i][j];//����ʼ���浽�ṹ����
		}
	}
	return OK;
}//InitMaze

Status PrintMaze(MazeType &m){
//����Թ�
	int i, j;
	printf("����Թ���\n");
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

	InitStack(s);//��ʼ��openջ
	InitStack(d);//��ʼ��printջ

	//ָ��·��
	e1.i = 1; e1.j = 1;
	//ָ������
	end.i = 8; end.j = 8;
	//����ջԪ��
	se.pi = 0; se.pj = 0; se.i = e1.i; se.j = e1.j;
	Push(s, se);

	while (!StackEmpty(s)){
		Pop(s, se);
		//��se����closed����
		p[i].i = se.i;
		p[i].j = se.j;
		p[i].pi = se.pi;
		p[i].pj = se.pj;
		i++;
		
		//�ж��Ƿ񵽴��յ㣬��������յ�������whileѭ����
		if (se.i == end.i &&se.j == end.j){ printf("\nThe path have found:\n"); break; }
		
		//û�е����յ���se����һ�����нڵ���ջ
		e1.i = se.i; e1.j = se.j;
		for (di = 1; di <= 4; di++)
		{
			GetNextNode(e1,di,e2 );
			if (compassable(m, e2))
			{//����ջԪ��
				se1.i = e2.i;
				se1.j = e2.j;
				se1.pj = se.j;
				se1.pi = se.i;
				//��һ����ͨ�ڵ�
				Push(s, se1);
				//�����㼣
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
	}//elseend//�Ż�*/
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
