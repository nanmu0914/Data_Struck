#include<stdio.h>
#include<stdlib.h>
//查找
//顺序查找    挨个的扫描查找    ASL（平均查找长度）
typedef struct LNode{
    int data;
    LNode * next;
}LNode;

int Search(int arr[],int n,int key){
    int i;
    for(i=0;i<n;++i)
        if(arr[i]==key)
            return i;
    
    return -1;
}

LNode * Search(LNode * head,int key){
    LNode * p=head->next;
    while(p!=NULL){
        if(p->data == key)
            return p;
        p=p->next;
    }
    return NULL;
}
//折半查找（被查序列必须有序）   判定其的平均查找长度则需构建折半查找判定树
int BSearch(int arr[],int low,int high,int key){
    while(low<=high){
        int mid=(high+low)/2;
        if(arr[mid]==key)
            return mid;
        else if(arr[mid]>key)
        high=mid-1;
        else
            low=mid+1;
    }
return -1;
}

//排序二叉树（查找）
//如果存在左子树 则左子树的值都小于其根节点的值 反之  右子树都大于
typedef struct BTNode
{
    int data;
    struct BTNode * lchild;
    struct BTNode * rchild;
}BTNode;

BTNode * BSTSearch(BTNode *p,int key){
    while(p!=NULL){
        if(p->data == key)
            return p;
        else if(key<p->data)
            p=p->lchild;
        else
            p=p->rchild;
    }
    return NULL;
}
//二叉排序树查找递归实现
BTNode * BSTSearchDG(BTNode * p,int key){
    if(p==NULL)//递归出口
        return NULL;
    else{
        if(key==p->data)
            return p;//结束当前层的函数
        else if(key<p->data)
            return BSTSearchDG(p->lchild,key);//先执行递归函数再return
        else
            return BSTSearchDG(p->rchild,key);
    }
}
//二叉排序树插入关键字   p可能会找的空指针  因此要对p采用引用形  将p的值插入空指针后
int BSTInsert(BTNode *&p,int key){
    if(p==NULL){
        p=(BTNode*)malloc(sizeof(BTNode));
        p->rchild=p->lchild=NULL;
        p->data=key;
        return 1;
    }
    else{
        if(p->data==key)
            return 0;//插入的元素已经存在
        else if(p->data>key)
            return BSTInsert(p->lchild,key);
        else
            return BSTInsert(p->rchild,key);
    }
}

/*二叉排序树删除双分支节点：1.来到该节点的左孩子节点，然后一直往右走，来到一个没有右孩子的节点
2.也可来到该节点的右孩子节点，然后一直往左走，来到一个没有左孩子的节点*/

//平衡二叉树（二叉排序树）  各个节点的平衡因子的绝对值不大于1  平衡因子=左子树的高度-右子树的高度

/*B树：插入关键字  当插入节点后阶数大于所给阶数 则要进行节点拆分
节点拆分：将当前的（阶数/2）位置上的关键字提出单独作为一个节点
B+树一个关键字对应一个分支   B树一个关键字的空位子对应一个分支

*/
//散列表  根据关键字的值来计算关键字在表中的地址 
//哈希函数的构造：1.直接地址 2.数字分析   3.平方取中  4.除留取余
//哈希表的冲突处理：1.开放地址法（线性探测）（平方探测） 2.链地址法（）

//汉诺塔问题    
/*
    1.表示需要移动的圆盘 
    2.a,b,c表示柱子的编号   
    */
void hanoi(int n,char a,char b,char c){
    if(n==1){
        printf("%c->%c",a,c);
    }
    else{
        hanoi(n-1,a,c,b);
        printf("%c->%c",a,c);
        hanoi(n-1,b,a,c);
    }
}