#include <stdio.h> 
#include <stdlib.h> 
#define MAX_VEX_NUM 50 //顶点数目最大为50
#define UN_REACH 1000  //若两点之间不直接连通,则权值为1000

typedef char VertexType;
 
typedef struct 
{ 
    VertexType vexs[MAX_VEX_NUM];			//顶点表
    int arcs[MAX_VEX_NUM][MAX_VEX_NUM];		//邻接矩阵，可看作边
    int vexnum, arcnum;						//图中当前的顶点数和边数
}MGraph;
  
/* 	根据名称得到指定顶点在顶点集合中的下标
	vex  顶点 
	return 如果找到，则返回下标，否则，返回0 */
 
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
  
/*创建邻接矩阵 */
 
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
        printf("请输入第%d个顶点:", i); 
        scanf("%c", &MG->vexs[i]); 
        getchar(); 
    } 
  
//初始化邻接矩阵 
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
  
//输入边的信息，建立邻接矩阵 
    for (k = 1; k <= MG->arcnum; k++) { 
        printf("请输入第%d条边的起点、终点、权值:", k); 
        scanf("%c %c %d",&c1, &c2,&weight); 
        v1 = getIndexOfVexs(c1, MG); 
        v2 = getIndexOfVexs(c2, MG);  
        MG->arcs[v1][v2] = MG->arcs[v2][v1] = weight;  
        getchar(); 
    } 
}
 

/*打印邻接矩阵和顶点信息 */
 
void print_MG(MGraph MG) { 
    int i, j; 
	printf("\n输出图的邻接矩阵为:\n");
    for (i = 1; i <= MG.vexnum; i++) { 
        j = 1; 
        for (; j < MG.vexnum; j++) { 
            printf("%4d   ", MG.arcs[i][j]); 
        } 
        printf("%d \n", MG.arcs[i][j]); 
    } 
} 
  
  
// 定义边结构体 
typedef struct
{ 
    int start; 
    int end; 
    int cost; 
}Edge; 
  
  
/*Prim算法求最小生成树 */

void Prim_MG(MGraph MG,char vs)
{ 
    Edge edge[MAX_VEX_NUM]; 
    int i,j,k,v,min; 
    int s = getIndexOfVexs(vs,&MG); 
    //初始化边 
    for(i = 1;i <= MG.vexnum;i++)
	{ 
        if(s != i)
		{ 
            edge[i].start = s; 
            edge[i].end = i; 
            edge[i].cost = MG.arcs[s][i]; 
          
        }//if
    }//for

//首先将s加入生成树集合中 
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
        edge[v].cost = 0; // 加入新节点 
  
//输出生成树中的边 
        printf("<%c,%c> 权值为:%d \n",MG.vexs[edge[v].start],MG.vexs[edge[v].end],MG.arcs[edge[v].start][edge[v].end]); 
  
//重新调整数组 
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
	printf("请输入顶点数目:");
    scanf("%d", &vexnum); 
	if(vexnum<=1)
	{
		printf("Error!\n");
		printf("\n运行结束!(*^__^*)\n");
		exit(0);
	}
    printf("请输入边的数目:");
    scanf("%d", &arcnum);
	if(vexnum>arcnum+1)
		printf("ERROR!\n");
	else
	{
		create_MG(&MG,vexnum,arcnum);
		print_MG(MG); 
		printf("\n\n请输入起点位置:"); 
		scanf("%c",&startVex); 
		printf("\n所求最小生成树为:\n"); 
		Prim_MG(MG,startVex); 
	}
	printf("\n运行结束!(*^__^*)\n");
    return 1; 
}

