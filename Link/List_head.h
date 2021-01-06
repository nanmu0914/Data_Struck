#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
//--------线性表的动态分配顺序存储结构-----
#define LIST_INIT_SIZE 100//存储空间的初始分配量
#define LISTINCREMENT	10//线性表的存储空间的分配量
#define TRUE 1
#define FLASE 0
#define OK	1
#define ERROR 0
#define LIFEASIBLE -1
#define OVERFLOW -2
typedef int ElemType;
typedef int Status;
/*
		分配的存储容量
*/
typedef struct {
	ElemType	*elem;	//存储空间的基址
	int		length;	//存储的长度
	int		listsize;	//当前的存储分配容量
}SqList;
//创造一个空的线性表

/*
Status Initlist_Sq(SqList L) {
	L.elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));//申请存储空间
	if (!L.elem) exit(OVERFLOW);
	L.length = 0;
	L.listsize = LIST_INIT_SIZE;
	return OK;
}
*/
Status InitList_Sq(SqList* L)
{
	(*L).elem = (ElemType*)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	if (!(*L).elem)
		exit(OVERFLOW);
	(*L).length = 0;
	(*L).listsize = LIST_INIT_SIZE;
	return OK;
}
//创建一个线性表
/*
void CreateList_Sq(SqList L) {
	L.elem = (ElemType*)malloc(LIST_INIT_SIZE * sizeof(ElemType));//申请存储空间
	if (!L.elem) exit(OVERFLOW);

}

*/
Status CreateList_Sq(SqList L) {
	L.elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));//申请存储空间
	if (L.elem) exit(OVERFLOW);
	//printf("请输入顺序表的长度:\n");
	//scanf_s("%d", &L.length);
	L.listsize = LIST_INIT_SIZE;
	int i;
	printf("请输入线性表的元素:\n");
	for (i = 0;i < L.length;i++) {
		scanf_s("%d",&L.elem[i]);
	}
	for (int i = 0;i < L.length;i++) {
		printf("%d ", L.elem[i]);
	}
	return OK;
}

//线性表的插入
/*
Status LinstInsert_Sq(SqList L,int i,ElemType e) {
	//1  判断i的值是否合法
	//n-i+1
	if (i<1 || i>L.length+1) return ERROR;
	//存储空间是否已满
	if (L.length >= L.listsize) {
		ElemType *newbase;
		newbase = (ElemType *)realloc(L.elem,
			(L.listsize + LISTINCREMENT) * sizeof(ElemType));
		if (!newbase)exit(OVERFLOW);
		L.elem = newbase;
		L.listsize += LISTINCREMENT;//当前的分配容量增加
	}
	int *q, *p;
	q = &(L.elem[i - 1]);
	for (p = &(L.elem[L.length - 1]);q <= p;--p) {
		*(p + 1) = *p;
		}
	*q = e;
	++L.length;
	return OK;
	}
*/
Status ListInsert_Sq(SqList* L, int i, ElemType e)
{
	if (i<1 || i>(*L).length + 1)
		return ERROR;  //i值不合法
	if ((*L).length >= (*L).listsize) {  //当前存储空间已满，增加分配
		ElemType* newbase;
		newbase = (ElemType*)realloc((*L).elem, ((*L).listsize + LISTINCREMENT) * sizeof(ElemType));
		if (!newbase)
			exit(OVERFLOW);
		(*L).elem = newbase;  //新基址
		(*L).listsize += LISTINCREMENT;  //增加存储容量
	}//if
	ElemType* q, * p;
	q = &((*L).elem[i - 1]); //q为插入位置
	for (p = &((*L).elem[(*L).length - 1]); p >= q; --p)
		*(p + 1) = *p;  //插入位置及之后的元素右移
	*q = e;  //插入e
	++(*L).length;  //表长增1
	return OK;
}
//线性表的删除
Status ListDelete_Sq(SqList L, int i, ElemType e) {
	if ((i<1 || i>L.length))return ERROR;//i的值是否合法}
	int *p, *q;
	p = &(L.elem[i - 1]);
	e = *p;
	q = L.elem + L.length - 1;//？
	for (++p;p <= q;++p) {
		*(p - 1) = *q;
	}
	--L.length;
		return OK;
}

int LocateElem_Sq(SqList L, ElemType e,Status(* compare)(ElemType ,ElemType)) {
	//compare比较函数
	//在顺序线性表L中查找第1个值与e满足compare()的元素的位序
	int i = 1;
	ElemType *p;
	p = L.elem;
	while (i <= L.length && !(* compare)(*p++, e))++i;//compare 如果=为1 否则为0
	if (i <= L.length) return i;
	else return 0;
}
//顺序表的合并
void MergeList_Sq(SqList LA,SqList LB,SqList *LC) {
	//LA LB已知  合并后为LC、
	ElemType* pa, * pb, * pc, *pa_last, *pb_last;
	//int pa_last, pb_last;
	pa = LA.elem;
	pb = LB.elem;
	(*LC).listsize = (*LC).length = LA.length + LB.length;
	pc = (ElemType*)malloc((*LC).listsize * sizeof(ElemType));
	(*LC).elem = pc;
	if (!(*LC).elem)exit(OVERFLOW);//存储分配失败
	pa_last = LA.elem + LA.length - 1;//LA最后一个元素
	pb_last = LB.elem + LB.length - 1;//LB最后一个元素
	while (pa <= pa_last && pb <= pb_last) {
		if (*pa <= *pb) *pc++ = *pa++;
		else *pc++ = *pb++;
	}
	while (pa <= pa_last)*pc++ = *pa++;
	while (pb <= pb_last) *pc++ = *pb++;
}

//遍历
void Print_Sq(SqList L) {
	for (int i = 0;i < L.length;i++) {
		printf("%d ",L.elem[i]);
	}
	printf("\n");
}

void displayTable(SqList L) {
	int i;
	for (i = 0; i < L.length; i++) {
 		printf("%d ", L.elem[i]);
	}
	printf("\n");
}

