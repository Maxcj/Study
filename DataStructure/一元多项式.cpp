#include<stdio.h>
#include<stdlib.h>

//���庯������ֵ
#define  TURE          1
#define  ERROR         0
#define  OK            1
#define  FALSE         0
#define  OVERFLOW      -2 

//���庯������
typedef int Status;
typedef int ElemType;

typedef struct  LNode{//��ı�ʾ
	float coef;//ϵ��
	int expn;//ϵ��
	struct LNode  *next;//ָ����һ��
}LNode, *Polynomial;

void paixu(Polynomial &P){
	Polynomial p, q;
	int t1;
	float t2;
	p = P;
	for (p = P->next; p != NULL; p = p->next)//����
	{
		for (q = p->next; q != NULL; q = q->next)
		{
			if (p->expn>q->expn){//������ָ������ǰ��ָ��ʱ�����е���
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
	//����m���ϵ����ָ����������ʾһԪ����ʽ����������P
	Polynomial p, last;
    int i;
	P = (Polynomial)malloc(sizeof(LNode));
	P->next = NULL;//����һ����ͷ�ڵ�ĵ�����
	last = P;
	for (i = 0; i < m; i++){
		p = (Polynomial)malloc(sizeof(LNode));
		printf("�����%.0f��ϵ����",i+1.0);
		scanf("%f",&p->coef);
		printf("�����%d��ָ����",i+1);
		scanf("%d", &p->expn);                     //����Ԫ��
		p->next = last->next; last->next = p; last = p; //����
	}		
	compare(P);
	return OK;
};

Status PrintPolyn(Polynomial P){
	//��ӡһԪ����ʽ
	Polynomial p;
	p = P->next;
	printf("�������");
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
	//�ж�ָ���Ƿ����
	if (a == b)return 1;
	return 0;
};

Status LinkDelete_L(Polynomial &P,Status(*compare)(int,int)){
	//�鲢ָ���ظ���
	Polynomial p, q;
	p = P;
	while (p ->next!= NULL){
		if(p->next != NULL&&!(compare(p->expn, p->next->expn))){ p = p->next; }//Ѱ�ҵ�i���ڵ㣬����pָ����ǰ��
		else {
			q = p->next; p->next = q->next;
			p->coef += q->coef; free(q);
		}//ɾ�����ͷ�
	}	
	return OK;
}

Status AddPolyn(Polynomial &Pa, Polynomial &Pb, Polynomial &Pc){
	//����ʽ�ӷ�Pc=Pa+Pb;
	Polynomial pa, pb,pc;
	pa = Pa->next; pb = Pb->next;
	Pc = pc = Pa;
	while (pa&&pb){//��Pa��ͷ�ڵ���ΪLc��ͷ�ڵ�
		if (pa->expn <= pb->expn){
			pc->next = pa; pc = pa; pa = pa->next;
		}
		else{ pc->next = pb; pc = pb; pb = pb->next; }
	}
	pc->next = pa ? pa : pb;//����ʣ���
	free(Pb);//�ͷ�ͷ�ڵ�
	return OK;
};

Status SubtractPolyn(Polynomial &Pa, Polynomial &Pb, Polynomial &Pc){
	//����ʽ����Pc=Pa+Pb;
	Polynomial pa, pb, pc,p;
	pa = Pa->next; pb = Pb->next;
	Pc = pc = Pa;
	p = Pb;
	for (p = Pb->next; p != NULL; p = p->next)//����
	{
		p->coef = -1 * p->coef;
	}
	while (pa&&pb){//��Pa��ͷ�ڵ���ΪLc��ͷ�ڵ�
		if (pa->expn <= pb->expn){
			pc->next = pa; pc = pa; pa = pa->next;
		}
		else{ pc->next = pb; pc = pb; pb = pb->next; }
	}
	pc->next = pa ? pa : pb;//����ʣ���
	free(Pb);//�ͷ�ͷ�ڵ�
	return OK;
};

Status MultipiyPolyn(Polynomial &Pa, Polynomial &Pb, Polynomial &Pc, void(*compare)(Polynomial &Pc)){
	//����ʽ�˷�Pc = Pa * Pb;
	Polynomial pa, pb, pc, last;
	Pc = (Polynomial)malloc(sizeof(LNode));
	Pc->next = NULL;
	last = Pc;
	for (pa = Pa->next; pa != NULL; pa = pa->next)//���
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
	printf("��������A���ȣ�");
	scanf("%d",&m);
	CreatPolyn(Pa, m,paixu);
	PrintPolyn(Pa);
	printf("��������B���ȣ�");
	scanf("%d", &m);
	CreatPolyn(Pb, m,paixu);
	PrintPolyn(Pb);
	MultipiyPolyn(Pa,Pb,Pc,paixu);
	LinkDelete_L(Pc,compare);
	PrintPolyn(Pc);
}