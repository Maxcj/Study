#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//定义函数返回值
#define OK            1
#define ERROR         0
#define TRUE          1
#define FALSE         0
#define OVERFLOW      -2

//定义函数类型
typedef char Status;
typedef char SElemType;
typedef char OperandType;

//定义栈
#define STACK_INIT_SIZE 100//存储空间初始分配量
#define STACKINCREMENT  10 //存储空间分配增量
typedef struct{
	SElemType *top;
	SElemType *base;
	int stacksize;
}SqStack;


Status InitStack(SqStack &s){
	//构造一个空栈
	s.base = (SElemType *)malloc(STACK_INIT_SIZE*sizeof(SElemType));
	if (!s.base)exit(OVERFLOW);//存储分配失败
	s.top = s.base;
	s.stacksize = STACK_INIT_SIZE;
	return OK;
}//InitStack

Status Push(SqStack &s, SElemType e){
	//插入元素e为新的栈顶
	if (s.top - s.base > STACK_INIT_SIZE){//栈满，追加空间
		s.base = (SElemType*)realloc(s.base, (STACK_INIT_SIZE + STACKINCREMENT)*sizeof(SElemType));
		if (s.base)exit(OVERFLOW);//存储空间分配失败
		s.top = s.base + s.stacksize;
		s.stacksize += STACKINCREMENT;
	}
	*s.top++ = e;
	return OK;
};//Push

Status Pop(SqStack &s, SElemType &e){
	//删除栈顶元素，并用e返回
	if (s.top == s.base)return ERROR;
	e = *--s.top;
	return OK;
};//Pop

Status GetTop(SqStack s){
	//若栈不为空，则返回s的栈顶元素
	SElemType e;
	if (s.top == s.base)return ERROR;
	e = *(s.top - 1);
	return e;
}//GetTop

Status Precede(SElemType x,SElemType y){
//判断运算符优先级
	SElemType ch[] = {'+','-','*','/','(',')','#'};
	SElemType OP_class[][7] =
	{ '>', '>', '<', '<', '<', '>', '>',//'+'
	'>', '>', '<', '<', '<', '>', '>',//'- '
	'>', '>', '>', '>', '<', '>', '>',//'*'
	'>', '>', '>', '>', '<', '>', '>',//'/'
	'<', '<', '<', '<', '<', '=', ' ',//'('
	'>', '>', '>', '>', ' ', '>', '>',//')'
	'<', '<', '<', '<', '<', ' ', '=',//'#'
	};//算符之间的优先关系
	int i = 0, j = 0;
	while (ch[i] != x)i++;
	while (ch[j] != y)j++;
	if (i > 6 || j > 6)return 0;
	return OP_class[i][j];
}

int In(SElemType c)
{//判断当前元素是否为运算符
	SElemType ch[] = { '+', '-', '*', '/', '(', ')', '#' };
	int i=0;
	while (ch[i] != c) i++; 
	if (i > 6)return 0;
	return 1;
}

SElemType Operate(SElemType a, SElemType thera, SElemType b){
	//返回运算结果
	int s1, s2;
	s1 = a - '0';
	s2 = b - '0';
	switch (thera){
	case'+':return (s1 + s2)+'0';
	case'-':return (s1 - s2 )+ '0';
	case'*':return (s1 * s2 )+ '0';
	case'/':return (1.0*s1 / s2) + '0';
	}
	return 1;
}

OperandType EvaluateExpression(){
	//算术表达式求值的优先算法，设OPTR和OPND分别为运算符栈和运算数栈
	SElemType a,b,c,thera;
	SqStack OPTR, OPND;//定义栈
	InitStack(OPTR);//初始化运算符栈
	InitStack(OPND);//初始化运算数栈
	Push(OPTR, '#');//将#压入栈底
	c = getchar();
	while (c != '#' || GetTop(OPTR) != '#'){
		if (!In(c)){ Push((OPND), c); c = getchar(); }//不是运算符则进运算数栈
		else
			switch (Precede(GetTop(OPTR),c)){
			case'<'://栈顶元素优先级低
				Push(OPTR, c); c = getchar();
				break;
			case '='://脱括号并接受下一字符
				Pop(OPTR, c); c = getchar();
				break;
			case '>'://栈顶元素优先级高
				Pop(OPTR, thera);
				Pop(OPND, b); Pop(OPND, a);
				Push(OPND, Operate(a, thera, b));
				break;
			}//switch
	}//while
	return GetTop(OPND);
}//EvaluateExpression

void main(){
	printf("请输入算术表达式\n");
	printf("%d\n", EvaluateExpression()-'0');
}