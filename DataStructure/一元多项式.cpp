#include<stdio.h>
#include<stdlib.h>

//定义函数返回值
#define  TURE          1
#define  ERROR         0
#define  OK            1
#define  FALSE         0
#define  OVERFLOW      -2 

//定义函数类型
typedef int Status;
typedef int ElemType;

typedef struct  LNode{//项的表示
	float coef;//系数
	int expn;//系数
	struct LNode  *next;//指向下一项
}LNode, *Polynomial;

void paixu(Polynomial &P){
	Polynomial p, q;
	int t1;
	float t2;
	p = P;
	for (p = P->next; p != NULL; p = p->next)//排序
	{
		for (q = p->next; q != NULL; q = q->next)
		{
			if (p->expn>q->expn){//当后项指数大于前项指数时，进行调整
				t1 = p->expn;
				p->expn = q->expn;
				q->expn = t1;
				t2 = p->coef;
				p->coef = q->coef;
				q->coef = t2;
			}
		}
	}
}


Status CreatPolyn(Polynomial &P, int m, void(*compare)(Polynomial &P)){
	//输入m项的系数和指数，建立表示一元多项式的有序链表P
	Polynomial p, last;
    int i;
	P = (Polynomial)malloc(sizeof(LNode));
	P->next = NULL;//建立一个带头节点的单链表
	last = P;
	for (i = 0; i < m; i++){
		p = (Polynomial)malloc(sizeof(LNode));
		printf("输入第%.0f项系数：",i+1.0);
		scanf("%f",&p->coef);
		printf("输入第%d项指数：",i+1);
		scanf("%d", &p->expn);                     //输入元素
		p->next = last->next; last->next = p; last = p; //插入
	}		
	compare(P);
	return OK;
};

Status PrintPolyn(Polynomial P){
	//打印一元多项式
	Polynomial p;
	p = P->next;
	printf("输出链表：");
	while (p)
	{
		if (p->coef>0 && p->expn != 0)
		printf("+%.0f*X^%d ", p->coef,p->expn);
		if (p->coef<0 && p->expn != 0)
			printf("%.0f*X^%d ", p->coef, p->expn);
		if (p->expn == 0)printf("%.0f ", p->coef);
		p = p->next;
	}
	printf("\n");
	return OK;
};

Status compare(int a,int b){
	//判断指数是否相等
	if (a == b)return 1;
	return 0;
};

Status LinkDelete_L(Polynomial &P,Status(*compare)(int,int)){
	//归并指数重复项
	Polynomial p, q;
	p = P;
	while (p ->next!= NULL){
		if(p->next != NULL&&!(compare(p->expn, p->next->expn))){ p = p->next; }//寻找第i个节点，并令p指向其前驱
		else {
			q = p->next; p->next = q->next;
			p->coef += q->coef; free(q);
		}//删除并释放
	}	
	return OK;
}

Status AddPolyn(Polynomial &Pa, Polynomial &Pb, Polynomial &Pc){
	//多项式加法Pc=Pa+Pb;
	Polynomial pa, pb,pc;
	pa = Pa->next; pb = Pb->next;
	Pc = pc = Pa;
	while (pa&&pb){//用Pa的头节点作为Lc的头节点
		if (pa->expn <= pb->expn){
			pc->next = pa; pc = pa; pa = pa->next;
		}
		else{ pc->next = pb; pc = pb; pb = pb->next; }
	}
	pc->next = pa ? pa : pb;//插入剩余段
	free(Pb);//释放头节点
	return OK;
};

Status SubtractPolyn(Polynomial &Pa, Polynomial &Pb, Polynomial &Pc){
	//多项式减法Pc=Pa+Pb;
	Polynomial pa, pb, pc,p;
	pa = Pa->next; pb = Pb->next;
	Pc = pc = Pa;
	p = Pb;
	for (p = Pb->next; p != NULL; p = p->next)//排序
	{
		p->coef = -1 * p->coef;
	}
	while (pa&&pb){//用Pa的头节点作为Lc的头节点
		if (pa->expn <= pb->expn){
			pc->next = pa; pc = pa; pa = pa->next;
		}
		else{ pc->next = pb; pc = pb; pb = pb->next; }
	}
	pc->next = pa ? pa : pb;//插入剩余段
	free(Pb);//释放头节点
	return OK;
};

Status MultipiyPolyn(Polynomial &Pa, Polynomial &Pb, Polynomial &Pc, void(*compare)(Polynomial &Pc)){
	//多项式乘法Pc = Pa * Pb;
	Polynomial pa, pb, pc, last;
	Pc = (Polynomial)malloc(sizeof(LNode));
	Pc->next = NULL;
	last = Pc;
	for (pa = Pa->next; pa != NULL; pa = pa->next)//相乘
	{
		for (pb = Pb->next; pb!= NULL; pb = pb->next)
		{
			pc= (Polynomial)malloc(sizeof(LNode));
			pc->coef = pa->coef * pb->coef;
			pc->expn = pa->expn * pb->expn;
			pc = last->next; last->next = pc; last = pc;
		}	
                compare(Pc);
	}	
	return OK;
};

void main()
{
	Polynomial Pa,Pb,Pc;
	int m;
	printf("输入链表A长度：");
	scanf("%d",&m);
	CreatPolyn(Pa, m,paixu);
	PrintPolyn(Pa);
	printf("输入链表B长度：");
	scanf("%d", &m);
	CreatPolyn(Pb, m,paixu);
	PrintPolyn(Pb);
	MultipiyPolyn(Pa,Pb,Pc,paixu);
	LinkDelete_L(Pc,compare);
	PrintPolyn(Pc);
}