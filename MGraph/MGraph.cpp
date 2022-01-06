#include<stdio.h>
#include <algorithm> 
using namespace std;
#define maxSize 10
/*图的顺序存储结构
有向图：行表示起点  列表示终点
*/
//带权图   二维数组中对角线上的点为其顶点
/*
顶点为数值：
float MGraph[5][5];
for(int i=0;i<5;++i)
    for(int j=0;j<5;j++)
        MGraph[i][j]=MAX;
顶点为其余的字符：
char vertex[5]={'A',''B,'C','D','E'}
*/
//链式存储结构
typedef struct ArcNode{//边节点
    int adjv;//边所指的顶点
    struct ArcNode *next;//指向下一个边节点的指针
}ArcNode;
typedef struct{//图的顶点的结构体设计
    int data;
    ArcNode *first;
}VNode;
typedef struct{//图的结构体设计 
    VNode adjList[maxSize];
    int n,e;
}AGraph;

//图的深度优先遍历  DFS0
void Visit(int v){}
int visit[];
void DFS(int v,AGraph *G){
    visit[v]=1;
    Visit(v);
    ArcNode *q = G->adjList[v].first;//取A1相关的第一条边
    while(q!=NULL){
        if(visit[q->adjv]==0)//q所指向的另一端的顶点是否已被访问
            DFS(q->adjv,G);
        q=q->next;
    }
}
//广度优先遍历  队列
void BFS(AGraph *G,int v,int visit[maxSize]){
    ArcNode *p;//边
    int que[maxSize],front=0,rear=0;//定义一个队列
    int j;
    Visit(v);
    visit[v]=1;//给已访问的图的顶点赋值为1
    rear=(rear+1)%maxSize;
    que[rear]=v;//入队
    while(front!=rear){
        front=(front+1)%maxSize;
        j=que[front];//出队
        p=G->adjList[j].first;//p指向当前顶点的一条边
        while(p!=NULL){
            if(visit[p->adjv]==0){
                //与边相连有顶点存在且该顶点没有访问过
                Visit(p->adjv);
                visit[p->adjv]=1;
                rear=(rear+1)%maxSize;
                que[rear]=p->adjv;
            }
            p=p->next;
        }
    }
}

//最小生成树  选取权值最小的树
//基于顶点的操作
int INF=0;//表示无穷大 ∞
void Prim(int n,float MGraph[][10],int v0,float &sum){
    /*参数：
    1.顶点的个数
    2.带权图  二维数组表示的图
    3.构造生成树的起始顶点
    4.最小代价
    */
    int lowCost[n],vSet[n];
    //lowCost[]当前生成树到图中其余顶点边的最小权值
    //vSet[]当数组中的某位置上的值被设置为1时  表示该顶点已经被并入树中
    int v,k,min;//v表示当前刚并入的顶点
    //初始化
    for(int i =0;i<n;i++){
        lowCost[i]=MGraph[v0][i];//初始时 表示为0到其余顶点的权值
        vSet[i]=0;
    }
    v=v0;
    vSet[v]=1;
    sum=0;
//生成树
    for(int i=0;i<n-1;++i){//n-1表示带的节点  因为0号节点已被处理
        min=INF;//min表示当前顶点到图中剩余顶点的最小边
       //获取最小边
        for(int j=0;j<n;j++)
            if(vSet[j]==0 && lowCost[j]<min){
                min=lowCost[j];
                k=j;
            }
        vSet[k]=1;
        v=k;
        sum += min;
        //更新lowCost[]的值  添加顶点边的值会发生改变
        for(int j=0;j<n;++j)
            if(vSet[j]==0 && MGraph[v][j]<lowCost[j])
                lowCost[j]=MGraph[v][j];
    }
}

//Kruskal算法
//基于边的操作
//存储结构设计
typedef struct{
    int a,b;//边的两个顶点
    int w;//边的权重
}Road;
Road road[maxSize];
//在并查集中从某个顶点所在的树中找出根节点的方法
int getRoot(int p){
    int v[5]={0};
    while(p!=v[p])
        p=v[p];
    return p;
}
//克鲁斯卡尔算法
void Kruskal(Road road[],int n,int e,int &sum){
    /*
    Road[]边数组  n表示并查集的个数   e表示边的个数
    */
   int a,b,v[5];//v表示并查集
   sum=0;
   //并查集初始化
   for(int i=0;i<n;++i)
        v[i]=i;
    //将边数组按照权值进行排序   用于挑选未被并入的最短的边
    //sort(road,e);
    for(int i=0;i<e;++i){
        a=getRoot(road[i].a);
        b=getRoot(road[i].b);
        if(a!=b){
            v[a]=b;
            sum+=road[i].w;
        }
    }
}
//单元最短路径
//迪杰斯特拉算法
/*
dist[]当前的起点到其余各个顶点的最短路径的长度
path[]起点到其余个顶点的最短路径 -1表示没有前一个顶点
set[]标记已经被选入最短路径的顶点
核心操作：
若dist[v](v为当前要检测的顶点)比dist[Vpre](Vpre为上一步并入的顶点)+MGraph[Vpre][v]大则：
    更新dist[v]为dist[Vpre]+MGraph[Vpre][v]
    更新path[v]为Vpre
*/
void Dijkstra(int n,float MGraph[][10],int v0,int dist[],int path[]){
    /*参数：
    1.图的顶点个数
    2.边的信息
    3.求最短路径的起始顶点
    4.存储最短路径的长度
    5.存储最短路径
    */
   //初始化
   int set[maxSize];
   int min,v;
   for(int i=0;i<n;i++){
       dist[i]=MGraph[v0][i];
       set[i]=0;
       if(MGraph[v0][i]<INF)
        path[i]=v0;//将权值为非无穷的其余个顶点与v0相连接的顶点的前一个顶点标记为v0
       else
        path[i]=-1;
   }
   set[v0]=1;path[v0]=-1;
   //核心代码
   //双for循环用于遍历每个并入顶点到其余顶点的距离
   for(int i=0;i<n-1;++i){//对剩余的顶点进行处理
   //从当前的剩余顶点中选取一个距离起点最近的点 然后设置其set的值为1
       min=INF;
       for(int j=0;j<n;++j)
        if(set[j]==0&&dist[j]<min){
            v=j;
            min=dist[j];
        }
        set[v]=1;
    //对dist和path数组的更新
       for(int j=0;j<n;++j){
        if(set[j]==0 && dist[v]+MGraph[v][j]<dist[j]){//判断起点到其余顶点的大小和起点经过当前中间并入点到其余边的大小
           dist[j]=dist[v]+MGraph[v][j];
           path[j]=v;
       }
    }
   }
}
//弗洛伊德算法  任意两个顶点的最短路径
/*两个范围数值:A  存储任意两个顶点之间的  当前的最短路径
Path  任意两个顶点所在最短路径的中间点
对于每个顶点v，和任一顶点对（i,j） i!=j,v!=i,v!=j
如果A[i][j]>A[i][v]+A[v][j],则将A[i][j]更新为A[i][v]+A[v][j]的值
并且将Path[i][j]改为v
*/
 void printPath(int u,int v,int path[][maxSize]){//u v表示两个点的最短路径
    if(path[u][v]==-1);//如果为-1直接输出
        //printf;
    else{
        int mid=path[u][v];//u到v的中间点
        printPath(u,mid,path);
        printPath(mid,v,path);
    }  
 }

 void Floyd(int n,float MGraph[][10],int Path[][10]){
     int i,j,v;
     int A[n][n];
     //初始化
     for(i=0;i<n;++i)
        for(j=0;j<n;++j){
            A[i][j]=MGraph[i][j];
            Path[i][j]=-1;
        }
    for(v=0;v<n;++v)//选取所有的中间点
        for(i=0;i<n;++i)//选出所有的顶点对 根据v进行检测
            for(j=0;j<n;++j){
                if(A[i][j]>A[i][v]+A[v][j]){
                    A[i][j]=A[i][v]+A[v][j];
                    Path[i][j]=v;
                }
            }
 }
 //拓扑排序   AOV网
 /*
 1.从有向图中选择一个入度为0的顶点输出；
 2.删除1）中的顶点，并且删除从该顶点发出的全部边
 3.重复上述步骤，直到剩余的图中不存在入度为0的顶点
 */
 //图的邻接表结构设计
typedef struct ArcNode1{//边节点
    int adjv;//边所指的顶点
    struct ArcNode1 *next;//指向下一个边节点的指针
}ArcNode1;
 typedef struct{
     int data;
     int count;//当前此顶点的入度
    ArcNode1 *first;
 }VNode1;
typedef struct{//图的结构体设计 
    VNode1 adjList[maxSize];
    int n,e;
}AGraph1;

 int TopSort(AGraph1 *G){
     int i,j,n=0;//n表示当前已输出的拓扑序列的个数
     int Stack[maxSize],top=-1;//栈用于保存当前入度为0的顶点
     ArcNode1 *p;//用于遍历
    //扫描所有顶点  并把入度为0的入栈
    for(i=0;i<G->n;++i)
        if(G->adjList[i].count==0)//将所有入度为0的顶点入栈
            Stack[++top]=i;
      //删除图中的顶点
      while(top!=-1){//如果栈不空则将栈中元素出栈
          i=Stack[top--];
          ++n;
          printf("%d\t",i);
     //遍历出栈顶点的所有边 并删除该顶点的所有出度边
        p=G->adjList[i].first;//p指向与当前顶点相连接的第一个顶点
        while(p!=NULL){
            j=p->adjv;//j获取边
            --(G->adjList[j].count);
            if(G->adjList[j].count==0)
                Stack[++top]=j;
            p=p->next;
        }
      }  
      if(n==G->n)
        return 1;
    else
        return 0;
 }
 //拓扑逆序
 void NXTopSort(AGraph1 *G,int v){//v表示访问的起始点
     visit[v]=1;//visit访问标记
     ArcNode1 *q=G->adjList[v].first;
     while(q!=NULL){
         if(visit[q->adjv]==0)//判断q所指示边的顶点是否被访问过
            NXTopSort(G,q->adjv);
        q=q->next;
     }
     Visit(v);
 }
 //AOE网  关键路径：AOE中 从原点到汇点最大路径长度
 /*
 1.求解最早发生时间  活动最晚
 2.求解最晚发生时间=后继事件发生时间-持续时间    多个活动选取最早  最后一个事件的最晚发生时间=该事件的最早发生时间
 3.求解每个活动的最早发生时间  其时间等于发生该活动的事件最早发生时间
 4.活动的最迟发生时间=改事件的最晚发生时间-活动持续时间
 5.最早发生时间和最晚发生时间重合的部分为关键路径
 */