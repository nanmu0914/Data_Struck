#include<stdio.h>
#include<stdlib.h>
#define maxSize 10
//顺序存储表示：1.存储A1-A5节点的数据信息 2.存储其指向父节点的数组下标
typedef struct{
    int data;
    int pIdx;
}TNode;
TNode tree1[maxSize];
//简化形式(双亲存储关系)
// int tree[maxSize];
// tree[0]=-1;
// tree[1]=0;

//链式存储
//链表的节点类型(分支) 存储数组中指向其孩子节点的下标
typedef struct Branch{
    int cIdx;//孩子节点的数组下标
    Branch *next;
}Branch; 
//树节点
typedef struct{
    int data;//节点的数据信息
    Branch *first;//指向所有孩子节点的首个地址信息
}TNode;
/*
二叉树的约束条件：每个节点追索两颗子树，子树有左右次序之分
*/
//二叉链表存储结构   可以表示树的孩子兄弟存储结构
typedef struct BTNode{
    int data;
    struct BTNode * lChild;
    struct BTNode * rChild;
}BTNode;
//A1->lChild=A2;

//树与二叉树的互相转换
//将其的兄弟节点进行连接 作为根节点的右边孩子节点

//遍历
/*
二叉树的遍历：
1.层次遍历（广度优先遍历）
2.深度优先遍历
先序遍历：根左右  中序遍历：左根右  后序遍历：左右根
树的遍历：
1.层次遍历（广度优先遍历）
2.深度优先遍历
先序遍历：根然后访问子树   后序遍历：先访问所有的子树然后访问根
树转化为二叉树后  原本的树与转换后的二叉树先序遍历相同  原树后序遍历与二叉树中序遍历相同
*/
//二叉树遍历代码结构框架(递归实现)
void visit(BTNode *p){

}
void r(BTNode *p){
    if(p!=NULL){
        //(1)先序遍历
        visit(p);
        r(p->lChild);
        //(2)中序遍历
        r(p->rChild);
        //(3)后序遍历
    }
}
//二叉树遍历（非递归实现方法）
//先序遍历  如若栈不空则入栈
void preorderNorecursion(BTNode *bt){
    if(bt!=NULL){//判断传入的根结点是否为空
        BTNode *Stack[maxSize];//建立一个辅助栈 保存节点的地址
        int top=-1;
        BTNode *p =NULL;//遍历指针
        Stack[++top]=bt;
        while(top!=-1){//判断栈是否为空
            //出栈一个元素对其访问
            p=Stack[top--];
            visit(p);
           //判断其左右孩子是否存在 
            if(p->rChild!=NULL)
                Stack[++top]=p->rChild;
            if(p->lChild!=NULL)
                Stack[++top]=p->lChild;
        }
    }
}
//后序遍历非递归  构建两个辅助栈
//将逆后序遍历入辅助栈然后就可得到后序遍历 
//逆后序遍历为：根右左
void postorDerNonrecursion(BTNode *bt){
    if(bt!=NULL){
        BTNode *Stack1[maxSize];int top1 =-1;
        BTNode *Stack2[maxSize];int top2=-1;
        BTNode *p;
        Stack1[++top1]=bt;
        while(top1!=-1){
            p=Stack1[--top1];
            Stack2[++top2]=p;
            if(p->lChild!=NULL)
                Stack1[++top1]=p->lChild;
            if(p->rChild!=NULL)
                Stack1[++top1]=p->rChild;
        }
        while(top2!=-1){//将辅助栈中的元素出栈
            p=Stack2[--top2];
            visit(p);
        }
    }
}
//中序遍历
/*从根结点开始沿着左海志指针一直往左走，直到左孩子指针为空的结点
将途经的孩子全部入栈，判断当前的左孩子是否为空，为空则出栈，再判
断其右孩子是否为空，为空则继续出栈  再取其右孩子
*/
void inorderNonrecursion(BTNode *bt){
    if(bt!=NULL){
        BTNode *Stack[maxSize];int top =-1;
        BTNode *p=NULL;
        p=bt;
        //p！=NULL 表示当当前的右孩子结点不空时且栈为空时有可能会导致主循环结束 
        while(top!=-1||p!=NULL){//如果栈不空或p不空
            while(p!=NULL){
                //将途经的所有结点入栈
                Stack[++top]=p;
                p=p->lChild;
            }
            if(top!=-1){
                p=Stack[top--];
                visit(p);
                p=p->rChild;
            }
        }
    }
}
//二叉树的层次遍历  运用队列遍历
void level(BTNode *bt){
    if(bt!=NULL){
        int front,rear;
        BTNode *que[maxSize];
        front=rear=0;
        BTNode *p;
        //将根结点入队
        rear=(rear+1)%maxSize;
        que[rear]=bt;
        while(front!=rear){
            front=(front+1)%maxSize;
            p=que[front];
            visit(p);
            //判断p的左孩子是否为空  不为空则将p的左孩子入队
            if(p->lChild!=NULL){
                rear=(rear+1)%maxSize;
                que[rear]=p->lChild;
            }
            if(p->rChild!=NULL){
                rear=(rear+1)%maxSize;
                que[rear]=p->rChild;
            }
        }
    }
}


// //链式存储
// //链表的节点类型(分支) 存储数组中指向其孩子节点的下标
// typedef struct Branch{
//     int cIdx;//孩子节点的数组下标
//     Branch *next;
// }Branch; 
// //树节点
// typedef struct{
//     int data;//节点的数据信息
//     Branch *first;//指向所有孩子节点的首个地址信息
// }TNode;
//取树的根节点
// TNode tree[6];
// Branch *q=tree[0]->first;
// tree[q->cIdx];
//树的先序遍历

void visit1(TNode *p){

}
void preOrder(TNode *p,TNode tree[]){//tree[]存储其孩子节点的索引
    if(p!=NULL){
        visit1(p);
        Branch *q;
        q=p->first;
        //遍历
        while(q!=NULL){//扫描链表里的数据
            preOrder(&tree[q->cIdx],tree);
            q=q->next;
        }
    }
}
//树的层次结构遍历
void levelT(TNode*tn,TNode tree[]){
    int rear,front;
    TNode *ques[maxSize];
    front=rear=0;
    TNode *p;
    if(tn!=NULL){//入队
        rear=(rear+1)%maxSize;
        ques[rear]=tn;
        while(front!=rear){//出队一个元素
            front=(front+1)%maxSize;
            p=ques[front];
            visit1(p);
            Branch*q=p->first;
            //q来扫描链表数据
            while(q!=NULL){
                rear=(rear+1)%maxSize;
                ques[rear]=&tree[q->cIdx];//子节点入队
                q=q->next;
            }
        }
    }
}

//考点：线索二叉树
//中序线索二叉树   连接规则：如果有左空指针，则左空指针指向其前驱 反之为后继
typedef struct TBTNode{
    int data;
    int lTag;//当其为0时  指向左孩子 当其为1时 指向前驱
    int rTag;
    TBTNode *lChild;
    TBTNode *rChild;
}TBTNode;

void inThread(TBTNode*p,TBTNode *&pre){//pre为其前驱结点
    if(p!=NULL){
        inThread(p->lChild,pre);
        if(p->lChild==NULL){
            p->lChild=pre;
            p->lTag=1;
        }
        if(pre->rChild==NULL && pre!=NULL){
            pre->rChild=p;
            pre->rTag=1;
        }
        pre=p;
        inThread(p->rChild,pre);
    }
}
//先序线索化
//找其开始结点  然后再找其后继节点
void preThread(TBTNode *p,TBTNode *&pre){
    if(p!=NULL){
        if(p->lChild==NULL){//做个线索
            p->lChild=pre;
            p->lTag=1;
        }
        if(p->rChild==NULL && p!=NULL){//pre线索化
            pre->rChild=p;
            pre->rTag=1;
        }
        pre=p;
        //防止p一直在打转
        if(p->lTag==0)
            preThread(p->lChild,pre);
        if(p->rTag==0)
            preThread(p->rChild,pre);
    }
}

//先序线索化遍历
//如果p不是线索则p边访问边往左走 如果p是线索则先访问p然后p往右走
void preOrder(TBTNode *tbt){
    if(tbt!=NULL){
        TBTNode *p=tbt;
        while(p!=NULL){
            while(p->lTag==0){
                //visit2(p);
                p=p->lChild;
            }
            //visit2(p);
            p=p->rChild;
        }
    }
}
//后序线索化
void postThread(TBTNode *p,TBTNode *&pre){
    if(p!=NULL){
        postThread(p->lChild,pre);
        postThread(p->rChild,pre);
        if(p->lChild==NULL){
            p->lChild=pre;
            p->lTag=1;
        }
        if(p->rChild==NULL && pre!=NULL){
            pre->rChild=p;
            pre->rTag=1;
        }
        pre=p;
    }
}
//寻找节点的后继：a.若是根节点则其后继为空   b.若为双亲的右孩子（左孩子）且其双亲没有
//右子树，则其后继即为双亲节点   c.若节点是其双亲的左孩子，且其双亲有右子树，则其后继
//为双亲右子树上按后序遍历列出的第一个节点

//哈夫曼树
//根据遍历序列确定二叉树 先序和中序
BTNode *CreateBT(char pre[],char in[],int L1,int R1,int L2,int R2){
    /*1.两个字符型数组参数存储两个遍历序列
    2.两个控制范围的变量来划分数组 pre为L1和R1  in为L2和R2 */
    if(L1>R1)//递归出口  长度为0的序列
        return NULL;
    //构建一个树的根节点
    BTNode *s=(BTNode *)malloc(sizeof(BTNode));//根节点申请一个存储空间
    s->lChild=s->rChild=NULL;
    s->data=pre[L1];

    int i;//寻找根节点将其分为两段
    for(i=L2;i<=R2;++i)
        if(in[i]==pre[L1])
            break;

    s->lChild=CreateBT(pre,in,L1+1,L1+i-L2,L2,i-1);
    s->rChild=CreateBT(pre,in,L1+i-L2+1,R1,i+1,R2);
    return s;
}
//中序和后序
BTNode *CreateBT2(char post[],char in[],int L1,int R1,int L2,int R2){
    if(L1>R1)
        return NULL;
    BTNode *s=(BTNode *)malloc(sizeof(BTNode));
    s->lChild=s->rChild=NULL;
    s->data=post[R1];

    int i;
    for(i=L2;i<=R2;i++)
        if(in[i]==post[R1])
            break;
    s->lChild=CreateBT2(post,in,L1+1,L1+i-L2,L2,i-1);
    s->rChild=CreateBT2(post,in,L1+i-L2+1,R1,i+1,R2);
    return s;
}
//层次遍历序列和中序遍历序列来确定二叉树
//确定待查找数组的下标
int search(char arr[],char key,int L,int R){//1.待查找数组 2.待查关键字 3.待查范围
    int index;
    for(index=L;index <= R;++index){
        if(arr[index]==key)
            return index;
    return -1;
    }
}
//获取子序列
void getSublevel(char sublevel[],char level[],char in[],int n,int L,int R){
    int k=0;//辅助向结果数组中求得的元素
    for(int i=0;i<n;i++){
        if(search(in,level[i],L,R))
            sublevel[k++]=level[i];
    }
}
//核心代码
BTNode *CreatBT3(char level[],char in[],int n,int L,int R){
    if(L>R)
        return NULL;
    BTNode *s =(BTNode *)malloc(sizeof(BTNode));
    s->lChild=s->rChild=NULL;
    s->data = level[0];

    int i=search(in,level[0],L,R);//查找根节点在中序遍历中的位置
    //在level[]中构建两个长度和in[]中两个子序列长度相等的序列
    int LN=i-L;char LLevel[LN];
    int RN=R-i;char Rlevel[RN];
    //将levev[]中分散的两个子序列通过存储在不同的两个数组中  使其变得连续起来
    getSublevel(LLevel,level,in,LN,L,i-1);
    getSublevel(Rlevel,level,in,RN,i+1,R);

    s->lChild=CreatBT3(LLevel,in,LN,L,i-1);
    s->rChild=CreatBT3(Rlevel,in,RN,i+1,R);

    return s;
}