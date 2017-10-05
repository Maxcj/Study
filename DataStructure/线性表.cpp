#include <stdio.h>
#include <stdlib.h>

//#include <>格式，引用标准库的头文件，编译器从标准库目录开始搜索
//#include ""格式，引用非标准库的头文件，编译器从用户的工作目录开始搜索

#define list_init_size 100
#define newsize 10
//线性表存储空间初始分配量

typedef int Status;//定义函数类型
typedef int ElemType;//定义元素类型

typedef struct{
	ElemType *elem;//存储空间基址
	int length;//当前线性表长度
	int listsize;//当前分配的存储容量
// (以sizeof(ElemType)为单位)
}Sqlist;

//初始化线性表(构造一个新的线性表)：
Status chushihua(Sqlist &L){
	L.elem=(ElemType *)malloc(list_init_size*sizeof(ElemType));
	if(!L.elem)
		exit(-2);
	L.length=0;
	L.listsize=list_init_size;
	return 1;
}

//判断线性表是否为空
Status ListEmpty(Sqlist &L)
{ 
	if(L.length==0)
		return 1;
	else
		return 0;
}

//将线性表重置为空表
Status ClearList(Sqlist &L)
{
    L.length=0;
    return 1;
}
//遍历线性表
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

//在线性表中的第j个位置插入元素
Status init_Sq(Sqlist &L,int j,ElemType e)
{
	int *newbase,*q,*p;
	//在线性表的第j个位置之前插入新的元素e
	// (1<=i<=ListLength_Sq(L)+1)
	if(j<1||j>L.length+1)
		return 0;
	if(L.length>=L.listsize){//当前存储空间已满，增加空间
		newbase=(ElemType *)realloc(L.elem,(L.listsize+newsize)*sizeof(ElemType));
	if(!newbase)
		exit(-2);//存储空间分配失败
	L.elem=newbase;//新的基址
	L.listsize+=newsize;//增加存储容量
	}
	q=&(L.elem[j-1]);//q为插入地址
	for(p=&(L.elem[L.length-1]);p>=q;p--)
		*(p+1)=*p;//插入位置及之后的元素向右移动
	*q=e;
	L.length++;
	return 1;
}//a(Sqlist &L,int i,ElemType e),线性表插入


//线性表删除   删除第i个元素
Status delete_Sq(Sqlist &L,int i,ElemType &e){
	//在线性表L中删除第i个元素，并用e返回其值
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
       //已知线性表La和Lb中的数据元素是非递减排列
       //归并La和Lb得到新的线性表Lc，Lc的数据元素也是非递减排列
       int *pa,*pb,*pa_last,*pb_last,*pc;
       pa=La.elem;
       pb=Lb.elem;
       Lc.listsize=Lc.length=La.length+Lb.length;
       pc=Lc.elem=(ElemType *)malloc(Lc.listsize*sizeof(ElemType));
       if(!Lc.elem)
              exit(-2);  //内存分配失败
       pa_last=La.elem+La.length-1;
       pb_last=Lb.elem+Lb.length-1;
       while(pa<=pa_last&&pb<=pb_last)  //归并
       {
              if(*pa<=*pb)
                     *pc++=*pa++;
              else
                     *pc++=*pb++;
       }
       while(pa<=pa_last)  //插入A中剩余的元素
       {
              *pc++=*pa++;
       }
       while(pb<=pb_last)  //插入A中剩余的元素
       {
              *pc++=*pb++;
       }
	   return 1;
}

void main()
{
	Sqlist L;
	chushihua(L);
//输入1--n的数据
	int i,n;
	printf("输入所需线性表元素的个数\n");
	scanf("%d",&n);
	if(n>L.listsize)
		printf("error");
	for(i=0;i<n;i++)
		L.elem[i]=i+1;
	L.length=n;
	for(i=0;i<n;i++)
		printf("%d ",L.elem[i]);
	printf("\n\n");

//插入元素
	int j,e1;
	printf("输入插入的位置，以及插入的元素的值\n");
	scanf("%d%d",&j,&e1);
	init_Sq(L,j,e1);
	for(j=0;j<n+1;j++)
		printf("%d ",L.elem[j]);
	printf("\n\n");


//删除第i个元素并输出其值
	int i1,e2;
	printf("输入要删除元素的位置\n");
	scanf("%d",&i1);
	if(i1>n)
		printf("错误,输入的位置比线性表长度长!\n\n");
	else
	{
		delete_Sq(L,i1,e2);
		for(j=0;j<n;j++)
			printf("%d ",L.elem[j]);
		printf("\n");
		printf("删除的元素的值为:");
		printf("%d\n",e2);
	}
	

//线性表La，Lb合并
	Sqlist La,Lb,Lc;
	chushihua(La);chushihua(Lb);chushihua(Lc);

	printf("输入所需线性表La的元素的个数\n");
	scanf("%d",&n);
	if(n>La.listsize)
		printf("error");
	for(i=0;i<n;i++)
		La.elem[i]=i+1;
	La.length=n;
	for(i=0;i<n;i++)
		printf("%d ",La.elem[i]);
	printf("\n");
	printf("\n输入所需线性表Lb的元素的个数\n");
	scanf("%d",&n);
	if(n>Lb.listsize)
		printf("error");
	for(i=0;i<n;i++)
		Lb.elem[i]=i+1;
	Lb.length=n;
	for(i=0;i<n;i++)
		printf("%d ",Lb.elem[i]);
	printf("\n");
//归并
	MergeList(La,Lb,Lc);
	printf("\n线性表La,Lb排序之后：\n");
	for(i=0;i<La.length+Lb.length;i++)
		printf("%d ",Lc.elem[i]);
}