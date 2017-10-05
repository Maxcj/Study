#include <stdio.h>  
#include <stdlib.h> 
#include<iostream>
using namespace std; 
 
#define OK      1  
#define ERROR   0   
#define InitSize 100  
#define Increment 10  
  
#define COLUMN 6    
#define ROW 6    
  
typedef int Status; 
  
typedef struct{  
   int *maze; 
    int *footprint; 
   int row;
   int column; 
}MazeType;  
 
typedef struct{
    int x;  
    int y;  
}PosType;  
 
typedef struct{  
   PosType seat;  
    int di;
}SElemType;  
  
typedef struct{ 
    SElemType *base;  
    SElemType *top;  
   int StackSize;  
}SqStack;  


Status InitMaze(MazeType &M){   
   int i,j;  
  
   int mz[ROW][COLUMN]={{1,0,1,1,1,1},{1,0,1,1,1,1},{1,0,0,0,0,1},{1,0,1,1,1,1},{1,0,0,0,0,0},{1,1,1,1,1,1}};

    M.maze=(int *)malloc(sizeof(int *)*ROW);  
    M.footprint=(int *)malloc(sizeof(int *)*ROW);
    if(!M.maze||!M.footprint){  
       return ERROR;  
 }  

   for(i=0;i<ROW;i++){  
      M.maze[i]=(int *)malloc(sizeof(int)*COLUMN);  
      M.footprint[i]=(int *)malloc(sizeof(int)*COLUMN);  
      if(!M.maze[i]||!M.footprint[i]){    
            return ERROR;  
        }  
    }  
    for(i=0;i<ROW;i++){  
        for(j=0;j<COLUMN;j++){  
           M.maze[i][j]=mz[i][j];  
           M.footprint[i][j]=0;  
        }  
  }  
   M.row=ROW; 
   M.column=COLUMN;  
    return OK;  
} 
 

Status PrintMaze(MazeType &M){    
    int i,j;  
    for(i=0;i<M.row;i++){  
       for(j=0;j<M.column;j++){  
      cout<<M.maze[i][j];  
        }  
    cout<<endl;  
    }  


	cout<<endl;
    return OK;  
}  
 
//打印迷宫
 
Status InitStack(SqStack &S){  
   S.base=(SElemType *)malloc(InitSize*sizeof(SElemType));  
   if(!S.base)  {return ERROR; }     
   S.top=S.base;  
    S.StackSize=InitSize;  
  return OK;  
}  
   
Status Push(SqStack &S,SElemType e){  
 if(S.top-S.base>=S.StackSize){
       S.base=(SElemType *)realloc(S.base,(S.StackSize+Increment)*sizeof(SElemType));  
       if(!S.base)  
       {    
return ERROR; 
      }  
      S.top=S.base+S.StackSize;
      S.StackSize+=Increment;  
   }  
   *S.top++=e;  
    return OK;  
}  
  
Status Pop(SqStack &S,SElemType e){  
    if(S.top==S.base){  
       return ERROR;  
    }  
    e=*(--S.top);  
   return OK;  
}  
 //栈的基本操作
 






 
Status Pass(MazeType &M,PosType pos){ //是否能通过
   if((M.row<pos.x)||(M.column<pos.y)){ return ERROR;}     
    if((0==M.footprint[pos.x][pos.y])&&(M.maze[pos.x][pos.y]==0))  
       return OK;  
  else  
       return ERROR;  
}  
 




Status FootPrint(MazeType &M,PosType pos){  //标记走过的通道快 为1
    if((pos.x>M.row)||(pos.y>M.column))  
       return ERROR;  
    M.footprint[pos.x][pos.y]=1;  
       return OK;  
} 




Status PrintFoot(MazeType &M,SqStack &S){   //打印路径
   int i,j;  
    SElemType *p;  
    for(i=0;i<M.row;i++){  
       for(j=0;j<M.column;j++){  
           M.footprint[i][j]=0;  
        }  
   }  
   p=S.base;  
   if(S.base==S.top)  
   {  
       return ERROR;  
   }  


  while(p!=S.top)  
   {  
      M.footprint[p->seat.x][p->seat.y]=1;  
     *p++;  
   }  


    for(i=0;i<M.row;i++){  
       for(j=0;j<M.column;j++){  
          cout<<M.footprint[i][j];  
       }  
	   cout<<endl;
    }  
  
   return OK;  
}  
  



SElemType NewSElem(PosType pos,int d){ //默认的新位置 
   SElemType e;   
   e.seat=pos;  
   e.di=d;  
    return e;  
}  

  

PosType NextPos(PosType pos,int di){   //新位置
    switch(di){  
   case 1:  
        pos.x++;  
       break;  
    case 2:  
      pos.y++;  
      break;  
 case 3 :
       pos.x--;  
        break;  
  case 4:  
        pos.y--;  
       break;  
   }  
   return pos;  
}  
 

 
Status MarkPrint(MazeType &M,PosType pos){ //被堵了 标记为1   
    if(pos.x>M.row||pos.y>M.column){  
       return ERROR;  
    }  
    M.footprint[pos.x][pos.y]=1;  
   return OK;  
}  





Status MazePath(SqStack &S,MazeType maze,PosType start,PosType end){   //打印路径
    SElemType e;  
    PosType curpos=start; 
    InitStack(S);
    do{  
        if(OK==Pass(maze,curpos)){  
            FootPrint(maze,curpos); 
           e=NewSElem(curpos,1);  
         Push(S,e);  
           if((curpos.x==end.x)&&(curpos.y==end.y)){
              PrintFoot(maze,S);  
              return OK;  
            }  
           curpos=NextPos(curpos,1);   
      } 
       else{
           if(!(S.base==S.top)){  
               Pop(S,e);  
               while(e.di==4&&!(S.base==S.top)){  
                   MarkPrint(maze,e.seat);  
                   Pop(S,e);  
                }  
               if(e.di<4){  
                   e.di++;  
                   Push(S,e);  
                   curpos=NextPos(e.seat,e.di);  
                }
            }  
        }   
    }while(!(S.base==S.top));  
    return ERROR;  
}  
 

int main()  
{  
   MazeType maze;  
   SqStack stack;  
   PosType start,end;  
   start.x=0;start.y=1;  
    end.x=4;end.y=5;  
   InitMaze(maze); 
   PrintMaze(maze); 
   
   if(OK==MazePath(stack,maze,start,end))
	   cout<<" 迷宫 可接"<<endl;
   else cout<<"迷宫不可解";
 
   return 0;  
} 