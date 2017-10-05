#include <stdio.h>
#include <stdlib.h>

//#include <>��ʽ�����ñ�׼���ͷ�ļ����������ӱ�׼��Ŀ¼��ʼ����
//#include ""��ʽ�����÷Ǳ�׼���ͷ�ļ������������û��Ĺ���Ŀ¼��ʼ����

#define list_init_size 100
#define newsize 10
//���Ա�洢�ռ��ʼ������

typedef int Status;//���庯������
typedef int ElemType;//����Ԫ������

typedef struct{
	ElemType *elem;//�洢�ռ��ַ
	int length;//��ǰ���Ա���
	int listsize;//��ǰ����Ĵ洢����
// (��sizeof(ElemType)Ϊ��λ)
}Sqlist;

//��ʼ�����Ա�(����һ���µ����Ա�)��
Status chushihua(Sqlist &L){
	L.elem=(ElemType *)malloc(list_init_size*sizeof(ElemType));
	if(!L.elem)
		exit(-2);
	L.length=0;
	L.listsize=list_init_size;
	return 1;
}

//�ж����Ա��Ƿ�Ϊ��
Status ListEmpty(Sqlist &L)
{ 
	if(L.length==0)
		return 1;
	else
		return 0;
}

//�����Ա�����Ϊ�ձ�
Status ClearList(Sqlist &L)
{
    L.length=0;
    return 1;
}
//�������Ա�
Status visit(ElemType e)
{
    printf("%d ",e);
    return 1;
}

Status ListTraverse(Sqlist &L)
{
    int i;
    for(i=0;i < L.length;i++)
        visit(L.elem[i]);
    printf("\n");
    return 1;
}

//�����Ա��еĵ�j��λ�ò���Ԫ��
Status init_Sq(Sqlist &L,int j,ElemType e)
{
	int *newbase,*q,*p;
	//�����Ա�ĵ�j��λ��֮ǰ�����µ�Ԫ��e
	// (1<=i<=ListLength_Sq(L)+1)
	if(j<1||j>L.length+1)
		return 0;
	if(L.length>=L.listsize){//��ǰ�洢�ռ����������ӿռ�
		newbase=(ElemType *)realloc(L.elem,(L.listsize+newsize)*sizeof(ElemType));
	if(!newbase)
		exit(-2);//�洢�ռ����ʧ��
	L.elem=newbase;//�µĻ�ַ
	L.listsize+=newsize;//���Ӵ洢����
	}
	q=&(L.elem[j-1]);//qΪ�����ַ
	for(p=&(L.elem[L.length-1]);p>=q;p--)
		*(p+1)=*p;//����λ�ü�֮���Ԫ�������ƶ�
	*q=e;
	L.length++;
	return 1;
}//a(Sqlist &L,int i,ElemType e),���Ա����


//���Ա�ɾ��   ɾ����i��Ԫ��
Status delete_Sq(Sqlist &L,int i,ElemType &e){
	//�����Ա�L��ɾ����i��Ԫ�أ�����e������ֵ
	//(1<=i<=ListLength_Sq(L))
	int *p,*q;
	if(i<1||i>L.length)
		return 0;
	p=&(L.elem[i-1]);
	e=*p;
	q=L.elem+L.length-1;
	for(++p;p<=q;++p)
		*(p-1)=*p;
	--L.length;
	return 1;
}//delete_Sq


Status MergeList(Sqlist La,Sqlist Lb,Sqlist &Lc)
{
       //��֪���Ա�La��Lb�е�����Ԫ���Ƿǵݼ�����
       //�鲢La��Lb�õ��µ����Ա�Lc��Lc������Ԫ��Ҳ�Ƿǵݼ�����
       int *pa,*pb,*pa_last,*pb_last,*pc;
       pa=La.elem;
       pb=Lb.elem;
       Lc.listsize=Lc.length=La.length+Lb.length;
       pc=Lc.elem=(ElemType *)malloc(Lc.listsize*sizeof(ElemType));
       if(!Lc.elem)
              exit(-2);  //�ڴ����ʧ��
       pa_last=La.elem+La.length-1;
       pb_last=Lb.elem+Lb.length-1;
       while(pa<=pa_last&&pb<=pb_last)  //�鲢
       {
              if(*pa<=*pb)
                     *pc++=*pa++;
              else
                     *pc++=*pb++;
       }
       while(pa<=pa_last)  //����A��ʣ���Ԫ��
       {
              *pc++=*pa++;
       }
       while(pb<=pb_last)  //����A��ʣ���Ԫ��
       {
              *pc++=*pb++;
       }
	   return 1;
}

void main()
{
	Sqlist L;
	chushihua(L);
//����1--n������
	int i,n;
	printf("�����������Ա�Ԫ�صĸ���\n");
	scanf("%d",&n);
	if(n>L.listsize)
		printf("error");
	for(i=0;i<n;i++)
		L.elem[i]=i+1;
	L.length=n;
	for(i=0;i<n;i++)
		printf("%d ",L.elem[i]);
	printf("\n\n");

//����Ԫ��
	int j,e1;
	printf("��������λ�ã��Լ������Ԫ�ص�ֵ\n");
	scanf("%d%d",&j,&e1);
	init_Sq(L,j,e1);
	for(j=0;j<n+1;j++)
		printf("%d ",L.elem[j]);
	printf("\n\n");


//ɾ����i��Ԫ�ز������ֵ
	int i1,e2;
	printf("����Ҫɾ��Ԫ�ص�λ��\n");
	scanf("%d",&i1);
	if(i1>n)
		printf("����,�����λ�ñ����Ա��ȳ�!\n\n");
	else
	{
		delete_Sq(L,i1,e2);
		for(j=0;j<n;j++)
			printf("%d ",L.elem[j]);
		printf("\n");
		printf("ɾ����Ԫ�ص�ֵΪ:");
		printf("%d\n",e2);
	}
	

//���Ա�La��Lb�ϲ�
	Sqlist La,Lb,Lc;
	chushihua(La);chushihua(Lb);chushihua(Lc);

	printf("�����������Ա�La��Ԫ�صĸ���\n");
	scanf("%d",&n);
	if(n>La.listsize)
		printf("error");
	for(i=0;i<n;i++)
		La.elem[i]=i+1;
	La.length=n;
	for(i=0;i<n;i++)
		printf("%d ",La.elem[i]);
	printf("\n");
	printf("\n�����������Ա�Lb��Ԫ�صĸ���\n");
	scanf("%d",&n);
	if(n>Lb.listsize)
		printf("error");
	for(i=0;i<n;i++)
		Lb.elem[i]=i+1;
	Lb.length=n;
	for(i=0;i<n;i++)
		printf("%d ",Lb.elem[i]);
	printf("\n");
//�鲢
	MergeList(La,Lb,Lc);
	printf("\n���Ա�La,Lb����֮��\n");
	for(i=0;i<La.length+Lb.length;i++)
		printf("%d ",Lc.elem[i]);
}