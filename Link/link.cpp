#include <stdio.h>

typedef struct node{
	int data;
	struct node *link;
}NODE,*LinkList;

/*²éÕÒ*/
LinkList Find_List(LinkList L, int k){
	LinkList p,int i;
	i = 1;
	p=L->link;
	while(P && i < k){
		p = p->link;
		i++;
	}
	if(p && i == k)
		return p;
	return NULL;
}//Find_List

/*²åÈë*/
int Insert_List(LinkList L, int k, int NewElem){
	LinkList p,s;
	if(k == 1)
		p = L;
	else
		p = Find_List(L, k-1);
	if(!p)
		return -1;
	s = (NODE *)malloc(sizeof(NODE));
	if(!s)
		return -1;
	s->data = newElem;
	s->link = p->link;
	p->link = s;
	return 0;
}//Insert_List

/*É¾³ý*/
int Delete_Link(LinkList L, int k){
	LinkList p,q;
	if(k == 1)
		p = L;
	else
		p = Find_List(L, k-1);
	if(!p || !p->link)
		return -1;
	q = p->link;
	p->link = q->link;
	free(q);
	return 0;
}//Delete_Link