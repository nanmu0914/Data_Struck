//设计一个算法删除重复节点
#include<stdio.h>
#include<stdlib.h>
//链表的结构体定义
typedef struct LNode {
	int data;
	struct LNode* next;
}LNode;

//核心函数
void del(LNode* L) {
	LNode* p = L->next, * q;//含有头结点的链表
	while (p->next != NULL) {//遍历链表
		if (p->data == p->next->data) {//如果数据相等则执行删除操作
			q = p->next;
			p->next = q->next;
			free(q);
		}
		else
			p = p->next;
	}
}

//建表
void CreateList(LNode* &head, int arr[], int n) {
	head = (LNode*)malloc(sizeof(LNode));
	head->next = NULL;
	LNode* r = head;
	for (int i = 0;i < n;++i) {
		LNode* p = (LNode*)malloc(sizeof(LNode));
		p->data = arr[i];
		p->next = NULL;
		r->next = p;
		r = p;
	}
}
void PrintList(LNode* L) {
	LNode* p;
	p = L->next;
	while (p->next != NULL) {
		printf("%d\t", p->data);
		p = p->next;
	}
	printf("\n");
}
int main() {
	int a[] = { 1,2,2,2,3,3,3,3,4,4,4,4,6,7,7,7 };
	LNode* A;
	CreateList(A, a, 17);
	del(A);
	PrintList(A);
	return 0;
}

//将A链表中的偶数节点移除到B链表中
void split(LNode* A, LNode*& B) {
	LNode* p, * q, * r;
	B = (LNode*)malloc(sizeof(LNode));
	B->next = NULL;
	p = A;r = B;
	while (p->next != NULL) {
		if (p->next->data % 2 == 0) {
			q = p->next;
			p->next = q->next;
			q->next = NULL;
			r->next = q;
			r = q;
		}
		else
			p = p->next;
	}
}

//头插法建表（链表）
void createListTR(LNode*& head) {
	head = (LNode*)malloc(sizeof(LNode));
	head->next = NULL;
	LNode* p = NULL, * r = head;
	int n;
	for (int i = 0;i < n;++i) {
		p = (LNode*)malloc(sizeof(LNode));
		p->next = NULL;
		scanf("%d", &(p->data));
		//p->next = r->next;
		r->next = p;
		r = p;
	}
}

//头插法建表（链表）
void createListTH(LNode*& head) {
	head = (LNode*)malloc(sizeof(LNode));
	head->next = NULL;
	LNode* p = NULL;
	int n;
	for (int i = 0;i < n;i++) {
		p = (LNode*)malloc(sizeof(LNode));
		p->next = NULL;
		scanf("%d", &(p->data));
		//p->next = head->next;
		head->next = p;
	}
}

//键盘输入n个字母建立一个单链表，并且重复的数据建立只建立一个节点
//头插法
void createLinkNoSameElem(LNode* head) {
	head = (LNode*)malloc(sizeof(LNode));
	head->next = NULL;
	LNode* p;
	int n;
	char ch;
	scanf("%d", &n);
	for (int i = 0;i < n;i++) {
		scanf("%c", &ch);
		p = head -> next;
		while (p != NULL) {
			if (p->data == ch)
				break;
			p = p->next;
		}//遍历现有链表
			if (p == NULL) {
				p = (LNode*)malloc(sizeof(LNode));
				p->data = ch;
				head->next = p;
		}
	}
}

//考点：逆置
//顺序表的逆置
//将一长度为n的数组前端k个元素逆序后移动到数组中，原数据不变
void reverse(int a[], int left, int right, int k) {
	int temp;
	for (int i = left, j = right;i < left + k && i < j; i++, j--) {
		temp = a[i];
		a[i] = a[j];
		a[j] = temp;
	}
}

//链表的逆置
/*
while (p->next != q) {
	t = p->next;
	p->next=t->next;
	t->next=q->next;
	q->next=t;
}
*/

/*
真题：
设将n(n>1)个整数存放到一维数组R中。试设计一个在时间和空间两方面都尽可能高效的算法。将R中保存的序列循环左移p(0<p<n)个位置，即将R中的元素(Xo，X1，...Xn-1)，经过移动后变为:(Xp，Xp+1,...Xn-1,Xo,X1,...Xp-1)。
要求:
(1)给出算法的基本设计思想。
(2)根据设计思想，采用C或C++或JAVA语言描述算法，关键之处给出注释。
(3)说明你所设计算法的时间复杂度和空间复杂度。		时间复杂度：O(n),空间复杂度：O(1)
*/
//(1)先将前Xo,X1,...Xp-1逆置，再将Xp，Xp+1,...Xn-1逆置，最后再将整个表逆置
//(2)解析
void reverse(int a[], int left, int right, int k) {
	int temp;
	for (int i = left, j = right;i < left + k && i < j; i++, j--) {
		temp = a[i];
		a[i] = a[j];
		a[j] = temp;
	}
}
void moveP(int a[], int n, int p) {
	reverse(a, 0, p - 1, p);//前段逆置
	reverse(a, p, n - 1, n - p);//后段逆置
	reverse(a, 0, n - 1, n);//全表逆置
}

//考点：取最值
//顺序表
/*
int max = a[0];
int maxIdx = 0;  记录最大值和最小值
for(int i=0;i<n;i++){
	if(max<a[i]){
		max=a[i];
		maxIdx=i;
	}
}

链表：
LNode* p, * q;
int max = head->next->data;
q = p = head->next; p遍历 q记录
while(p!=NULL){
	if(max<p->data){
		max=p->data;
		q=p
	}
	p=p->next;
}
*/
/*
一双链表非空，由head指针指出，结点结构为{ llink，data,rlink }，请设计一个将结点数据域data值
最大的那个结点(最大值结点只有一个)移动到链表最前边的算法，要求不得申请新结点空间。
*/
typedef struct DLNode {
	int data;
	struct DLNode* llink;
	struct DLNode* rlink;
}DLNode;
void maxFirst(DLNode* head) {
	DLNode* p = head->rlink, *q = p;
	int max = p->data;
	//找最值
	while (p != NULL) {
		if (max < p->data) {
			max = p->data;
			q = p;
		}
		p = p->rlink;
	}
	//“删除”
	DLNode* l = q->llink, * r = q->rlink;
	l->rlink = r;
	if(r!=NULL)
		r->llink=l;
	//插入
	q->llink = head;
	q->rlink = head->llink;
	head->rlink = q;
	q->rlink->llink = q;
}


/*考点：划分
一、以为顺序表中的第一个元素作枢轴来划分
void partition(int arr[], int n) {
	int temp;//存放划分枢轴
	int i = 0, j = n - 1;
	temp = arr[i];
	while (i < j) {
		//扫描元素
		while (i < j && arr[j] >= temp)--j;
		//搬运元素
		if (i < j) {
			arr[i] = arr[j];
			++i;
		}
		while (i < j && arr[i] < temp)++i;
		if (i < j) {
			arr[j] = arr[i];
			--j;
		}
	}
	arr[i] = temp;
}
二、以任意一个值作为比较的标准 枢轴为:X 比较标准为：Y
void partition(int arr[], int n,int comp){
	int temp;//存放划分枢轴
	int i = 0, j = n - 1;
	temp = arr[i];
	while (i < j) {
		//扫描元素
		while (i < j && arr[j] >= comp)--j;
		//搬运元素
		if (i < j) {
			arr[i] = arr[j];
			++i;
		}
		while (i < j && arr[i] < comp)++i;
		if (i < j) {
			arr[j] = arr[i];
			--j;
		}
	}
	arr[i] = temp;
}
三、以顺序表中的任意元素进行划分
将该元素换位到表中的第一个元素即可开始划分
void partition(int arr[], int n,int k) {
	int temp;//存放划分枢轴
	int i = 0, j = n - 1;
	//进行换位操作
	temp = arr[0];
	arr[0] = arr[k];
	arr[k] = temp;
	while (i < j) {
		//扫描元素
		while (i < j && arr[j] >= temp)--j;
		//搬运元素
		if (i < j) {
			arr[i] = arr[j];
			++i;
		}
		while (i < j && arr[i] < temp)++i;
		if (i < j) {
			arr[j] = arr[i];
			--j;
		}
	}
	arr[i] = temp;
}
*/
//有一个线性表，采用带头结点的单链表L来存储。设计一个算法将其逆置。要求不能建立新结点，只能通过表中已有结点的重新组合来完成。
void reverse(LNode* L) {
	LNode* p = L->next, * q;//q用于标记p的下一个结点
	L->next = NULL;
	while (p != NULL) {
		q = p->next;
		p->next = L->next;
		L->next = p;
		p = q;
	}
}
//例题：有N个个位正整数存放在int型数组A[0,..N-1]中，N为已定义的常量且N<=9，数组A[]的长度为N，另给一个int型变量i，要求只用上述变量(A[0]~A[N-1]与i，这N+1个整型变量)写一个算法，找出这N个整数中的最小者，并且要求不能破坏数组A[]中的数据。
//i的个位存储最值  i的高位遍历数据
int N;
void findmin(int A[], int& i) {
	i = A[0];//A[0]存于i的个位上
	while (i / 10 <= N - 1) {//i/10取的是i的高位
		if (i % 10 > A[i / 10])//i%10 取i个位数上的值
		{
			i = i - i % 10;//将i的个位清零
			i = i + A[i / 10];
		}
		i = i + 10;
	}
	i = i % 10;//将i的个位赋值给i
}
//例题：写一个函数、逆序打印单链表中的数据，假设指针L指向了单链表的开始结点。
//(1)可用栈的结构解决；(2)递归调用,运用分治策略
void reprint(LNode* L) {//假设reprint函数已经可以将一个链表逆序输出了
	if (L != NULL) {
		reprint(L->next);//先逆序打印出L结点后面结点的信息
		printf("%d", L->data);
	}
}
//时间复杂度为O(n),空间复杂化度O(n)

//例题：两个由有序链表构成的集合A和B，判定两个集合是否相等
int isEqual(LNode* A, LNode* B) {
	LNode* p = A->next;
	LNode* q = B->next;
	while (p != NULL && q != NULL) {
		if (p->data == q->data) {
			p = p->next;
			q = q->next;
		}
		else
			return 0;
	}
	if (p != NULL || q != NULL)//检测p和q是否没有扫描结束
		return 0;
	else
		return 1;
}

//考点：归并
void mergearray(int a[], int m, int b[], int n, int c[]) {
	//m,n分别表示数组的长度
	int i = 0, j = 0;
	int k = 0;
	while (i < m && j < n) {
		if (a[i] < b[j])
			c[k++] = a[i++];//c[k]=a[i];k++;i++
		else
			c[k++] = b[j++];
	}
	//a数组的长度大于b数组  或 ……
	while (i < m)
		c[k++] = a[i++];
	while (j < n)
		c[k++] = b[j++];
}
//链表的归并
//带头结点链表
void merge(LNode* A, LNode* B, LNode* C) {
	LNode* p = A->next;
	LNode* q = B->next;
	LNode* r;
	C = A;//将A的头结点赋给C
	C->next = NULL;
	free(B);
	r = C;
	while (p != NULL && q != NULL) {
		if (p->data <= q->data) {
			r->next = p;p = p->next;
			r = r->next;
		}
		else {
			r->next = q;q = q->next;
			r = r->next;
		}
	}
	if (p != NULL)r->next = p;
	if (q != NULL)r->next = q;
}
//链表归并的头插法   归并后的链表与原链表的顺序相反
void mergeR(LNode* A, LNode* B, LNode* C) {
	LNode* p = A->next;
	LNode* q = B->next;
	LNode* s;//记录p或q
	C = A;//C共用A的头结点
	C->next = NULL;
	free(B);//B表示的只有其头结点  相当于头结点指针
	while (p!=NULL && q!=NULL) {
		if (p->data <= q->data) {
			s = p;p = p->next;
			s->next = C->next;C->next = s;
		}
		else {
			s = q;q = q->next;
			s->next = C->next;C->next = s;
		}
	}
	while (p != NULL) { s = p;p = p->next;s->next = C->next;C->next = s; }
	while (q != NULL) { s = q;q = q->next;s->next = C->next;C->next = s; }
}