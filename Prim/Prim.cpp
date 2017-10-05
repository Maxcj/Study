#include <stdio.h> 
#include <stdlib.h> 
#define MAX_VEX_NUM 50 //������Ŀ���Ϊ50
#define UN_REACH 1000  //������֮�䲻ֱ����ͨ,��ȨֵΪ1000

typedef char VertexType;
 
typedef struct 
{ 
    VertexType vexs[MAX_VEX_NUM];			//�����
    int arcs[MAX_VEX_NUM][MAX_VEX_NUM];		//�ڽӾ��󣬿ɿ�����
    int vexnum, arcnum;						//ͼ�е�ǰ�Ķ������ͱ���
}MGraph;
  
/* 	�������Ƶõ�ָ�������ڶ��㼯���е��±�
	vex  ���� 
	return ����ҵ����򷵻��±꣬���򣬷���0 */
 
int getIndexOfVexs(char vex, MGraph *MG) 
{ 
    int i; 
    for (i=1;i<= MG->vexnum;i++) 
	{ 
        if (MG->vexs[i]==vex) 
		{ 
            return i; 
        } 
    } 
    return 0; 
} 
  
/*�����ڽӾ��� */
 
void create_MG(MGraph *MG,int a,int b) 
{ 
    int i, j, k,weight; 
    int v1, v2; 
    char c1, c2;
    MG->vexnum=a;
	MG->arcnum=b;
    getchar(); 
    for (i = 1; i <= MG->vexnum; i++) 
	{ 
        printf("�������%d������:", i); 
        scanf("%c", &MG->vexs[i]); 
        getchar(); 
    } 
  
//��ʼ���ڽӾ��� 
    for(i=1;i<=MG->vexnum;i++) 
	{ 
        for (j=1;j<=MG->vexnum;j++) 
		{ 
            if(i==j) 
                MG->arcs[i][j]=0; 
            else
                MG->arcs[i][j]=UN_REACH; 
        }//for
    }//for
  
//����ߵ���Ϣ�������ڽӾ��� 
    for (k = 1; k <= MG->arcnum; k++) { 
        printf("�������%d���ߵ���㡢�յ㡢Ȩֵ:", k); 
        scanf("%c %c %d",&c1, &c2,&weight); 
        v1 = getIndexOfVexs(c1, MG); 
        v2 = getIndexOfVexs(c2, MG);  
        MG->arcs[v1][v2] = MG->arcs[v2][v1] = weight;  
        getchar(); 
    } 
}
 

/*��ӡ�ڽӾ���Ͷ�����Ϣ */
 
void print_MG(MGraph MG) { 
    int i, j; 
	printf("\n���ͼ���ڽӾ���Ϊ:\n");
    for (i = 1; i <= MG.vexnum; i++) { 
        j = 1; 
        for (; j < MG.vexnum; j++) { 
            printf("%4d   ", MG.arcs[i][j]); 
        } 
        printf("%d \n", MG.arcs[i][j]); 
    } 
} 
  
  
// ����߽ṹ�� 
typedef struct
{ 
    int start; 
    int end; 
    int cost; 
}Edge; 
  
  
/*Prim�㷨����С������ */

void Prim_MG(MGraph MG,char vs)
{ 
    Edge edge[MAX_VEX_NUM]; 
    int i,j,k,v,min; 
    int s = getIndexOfVexs(vs,&MG); 
    //��ʼ���� 
    for(i = 1;i <= MG.vexnum;i++)
	{ 
        if(s != i)
		{ 
            edge[i].start = s; 
            edge[i].end = i; 
            edge[i].cost = MG.arcs[s][i]; 
          
        }//if
    }//for

//���Ƚ�s���������������� 
    edge[s].cost = 0; 
    for(i = 2;i <= MG.vexnum;i++)
	{ 
        min = 1000; 
        for(j = 1;j<= MG.vexnum;j++)
		{ 
            if(edge[j].cost != 0 && edge[j].cost < min )
			{ 
                min = edge[j].cost; 
                k = j; 
            }//if 
        }//for
        v = edge[k].end; 
        edge[v].cost = 0; // �����½ڵ� 
  
//����������еı� 
        printf("<%c,%c> ȨֵΪ:%d \n",MG.vexs[edge[v].start],MG.vexs[edge[v].end],MG.arcs[edge[v].start][edge[v].end]); 
  
//���µ������� 
        for(j = 1;j <= MG.vexnum;j++)
		{ 
            if(edge[j].cost != 0 && MG.arcs[v][j] != 0 && MG.arcs[v][j] < edge[j].cost)
			{ 
                edge[j].start = k; 
                edge[j].end = j; 
                edge[j].cost = MG.arcs[v][j]; 
            }//if 
        }//for
    }//for
  
} 


int main() 
{ 
    MGraph MG; 
    char startVex;
	int vexnum,arcnum;
	printf("�����붥����Ŀ:");
    scanf("%d", &vexnum); 
	if(vexnum<=1)
	{
		printf("Error!\n");
		printf("\n���н���!(*^__^*)\n");
		exit(0);
	}
    printf("������ߵ���Ŀ:");
    scanf("%d", &arcnum);
	if(vexnum>arcnum+1)
		printf("ERROR!\n");
	else
	{
		create_MG(&MG,vexnum,arcnum);
		print_MG(MG); 
		printf("\n\n���������λ��:"); 
		scanf("%c",&startVex); 
		printf("\n������С������Ϊ:\n"); 
		Prim_MG(MG,startVex); 
	}
	printf("\n���н���!(*^__^*)\n");
    return 1; 
}

