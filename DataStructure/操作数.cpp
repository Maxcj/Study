#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//���庯������ֵ
#define OK            1
#define ERROR         0
#define TRUE          1
#define FALSE         0
#define OVERFLOW      -2

//���庯������
typedef char Status;
typedef char SElemType;
typedef char OperandType;

//����ջ
#define STACK_INIT_SIZE 100//�洢�ռ��ʼ������
#define STACKINCREMENT  10 //�洢�ռ��������
typedef struct{
	SElemType *top;
	SElemType *base;
	int stacksize;
}SqStack;


Status InitStack(SqStack &s){
	//����һ����ջ
	s.base = (SElemType *)malloc(STACK_INIT_SIZE*sizeof(SElemType));
	if (!s.base)exit(OVERFLOW);//�洢����ʧ��
	s.top = s.base;
	s.stacksize = STACK_INIT_SIZE;
	return OK;
}//InitStack

Status Push(SqStack &s, SElemType e){
	//����Ԫ��eΪ�µ�ջ��
	if (s.top - s.base > STACK_INIT_SIZE){//ջ����׷�ӿռ�
		s.base = (SElemType*)realloc(s.base, (STACK_INIT_SIZE + STACKINCREMENT)*sizeof(SElemType));
		if (s.base)exit(OVERFLOW);//�洢�ռ����ʧ��
		s.top = s.base + s.stacksize;
		s.stacksize += STACKINCREMENT;
	}
	*s.top++ = e;
	return OK;
};//Push

Status Pop(SqStack &s, SElemType &e){
	//ɾ��ջ��Ԫ�أ�����e����
	if (s.top == s.base)return ERROR;
	e = *--s.top;
	return OK;
};//Pop

Status GetTop(SqStack s){
	//��ջ��Ϊ�գ��򷵻�s��ջ��Ԫ��
	SElemType e;
	if (s.top == s.base)return ERROR;
	e = *(s.top - 1);
	return e;
}//GetTop

Status Precede(SElemType x,SElemType y){
//�ж���������ȼ�
	SElemType ch[] = {'+','-','*','/','(',')','#'};
	SElemType OP_class[][7] =
	{ '>', '>', '<', '<', '<', '>', '>',//'+'
	'>', '>', '<', '<', '<', '>', '>',//'- '
	'>', '>', '>', '>', '<', '>', '>',//'*'
	'>', '>', '>', '>', '<', '>', '>',//'/'
	'<', '<', '<', '<', '<', '=', ' ',//'('
	'>', '>', '>', '>', ' ', '>', '>',//')'
	'<', '<', '<', '<', '<', ' ', '=',//'#'
	};//���֮������ȹ�ϵ
	int i = 0, j = 0;
	while (ch[i] != x)i++;
	while (ch[j] != y)j++;
	if (i > 6 || j > 6)return 0;
	return OP_class[i][j];
}

int In(SElemType c)
{//�жϵ�ǰԪ���Ƿ�Ϊ�����
	SElemType ch[] = { '+', '-', '*', '/', '(', ')', '#' };
	int i=0;
	while (ch[i] != c) i++; 
	if (i > 6)return 0;
	return 1;
}

SElemType Operate(SElemType a, SElemType thera, SElemType b){
	//����������
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
	//�������ʽ��ֵ�������㷨����OPTR��OPND�ֱ�Ϊ�����ջ��������ջ
	SElemType a,b,c,thera;
	SqStack OPTR, OPND;//����ջ
	InitStack(OPTR);//��ʼ�������ջ
	InitStack(OPND);//��ʼ��������ջ
	Push(OPTR, '#');//��#ѹ��ջ��
	c = getchar();
	while (c != '#' || GetTop(OPTR) != '#'){
		if (!In(c)){ Push((OPND), c); c = getchar(); }//������������������ջ
		else
			switch (Precede(GetTop(OPTR),c)){
			case'<'://ջ��Ԫ�����ȼ���
				Push(OPTR, c); c = getchar();
				break;
			case '='://�����Ų�������һ�ַ�
				Pop(OPTR, c); c = getchar();
				break;
			case '>'://ջ��Ԫ�����ȼ���
				Pop(OPTR, thera);
				Pop(OPND, b); Pop(OPND, a);
				Push(OPND, Operate(a, thera, b));
				break;
			}//switch
	}//while
	return GetTop(OPND);
}//EvaluateExpression

void main(){
	printf("�������������ʽ\n");
	printf("%d\n", EvaluateExpression()-'0');
}