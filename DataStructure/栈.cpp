//栈的定义、基本操作

#include <stdio.h>
#include <stdlib.h>

#define STACK_INIT_SIZE 100

typedef int SelemType;
typedef int Status;

//定义数据类型
typedef struct{
	SelemType *base;
	SelemType *top;
	int stacksize;
}Sqstack;

//栈的初始化
Status InitStack(Sqstack &s)
{
	s.base=(SelemType *)malloc(STACK_INIT_SIZE*sizeof(SelemType));
	if(!s.base) exit(-2);
	s.top=s.base;
	s.stacksize=STACK_INIT_SIZE;
	return 1;
}

//入栈操作
Status push(Sqstack &s,SelemType &e)
{
	if(s.top-s.base>=s.stacksize)//栈满
	{
		s.base=(SelemType *)realloc(s.base,(s.stacksize+STACK_INIT_SIZE*sizeof(SelemType)));
		if(!s.base) exit(-2);
		s.top=s.base+s.stacksize;
		s.stacksize+=STACK_INIT_SIZE;
	}
	*s.top++=e;//压栈
	return 1;
}

//出栈操作
Status pop(Sqstack &s,SelemType &e)
{
	if(s.top=s.base) return 0;
	e=*--s.top;
	return 1;
}

//取栈顶	
Status GetTop(Sqstack &s,SelemType &e)
{
	if(s.top=s.base) return 0;
	e=*--s.top;
	return 1;
}

//运算操作
float operate(char a,char theat,char b)
{
	int s1,s2;
	s1=a-'0';
	s2=b-'0';
	switch(theat)
	{
		case '+':return s1+s2;
		case '-':return s1-s2;
		case '*':return s1*s2;
		case '/':return 1.0*s1/s2;
	}
}


Precede(char x,char y)
{
	char ch[]={'+','-','*','/','(',')','#'};
	char op_class[][]={{'+','-','*','/','(',')','#'};{'+','-','*','/','(',')','#'}};
	int i=0,j=0;
	while(char[i]!=x)
		i++;
	while(char[j]!=y)
		j++;
	if(i>6||j>6)
		return 0;
	return op_class[j][i];
}


Status EvaluateExpression(){
	int a,b;
	char c[];
	InitStack(OPTR);//初始化运算符栈
	push(OPTR,'#');//在运算符栈压入#
	InitStack(OPND);//初始化运算数栈
	c=getchar();
	while(c!='#'||GetTop(OPTR)!='#')
	{
		if(!A(c))
		{push(OPTR,c);c=getchar();}
		else
			switch(Precede(GetTop(OPRT),c)
		{
			case '<'://栈顶元素优先级更低
				push(OPTR,c);c=getchar();break;
			case '=':
				pop(OPTR,x);c=getchar();break;
			case '>':
				pop(OPTR,theat);
				pop(OPND,b);
				pop(OPND,a);
				push(OPND,operate(a,theat,b));
				break;
		}
	}
	return GetTop(OPND);
}