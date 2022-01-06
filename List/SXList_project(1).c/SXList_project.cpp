//���һ���㷨ɾ���ظ��ڵ�
#include<stdio.h>
#include<stdlib.h>
//����Ľṹ�嶨��
typedef struct LNode {
	int data;
	struct LNode* next;
}LNode;

//���ĺ���
void del(LNode* L) {
	LNode* p = L->next, * q;//����ͷ��������
	while (p->next != NULL) {//��������
		if (p->data == p->next->data) {//������������ִ��ɾ������
			q = p->next;
			p->next = q->next;
			free(q);
		}
		else
			p = p->next;
	}
}

//����
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

//��A�����е�ż���ڵ��Ƴ���B������
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

//ͷ�巨��������
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

//ͷ�巨��������
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

//��������n����ĸ����һ�������������ظ������ݽ���ֻ����һ���ڵ�
//ͷ�巨
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
		}//������������
			if (p == NULL) {
				p = (LNode*)malloc(sizeof(LNode));
				p->data = ch;
				head->next = p;
		}
	}
}

//���㣺����
//˳��������
//��һ����Ϊn������ǰ��k��Ԫ��������ƶ��������У�ԭ���ݲ���
void reverse(int a[], int left, int right, int k) {
	int temp;
	for (int i = left, j = right;i < left + k && i < j; i++, j--) {
		temp = a[i];
		a[i] = a[j];
		a[j] = temp;
	}
}

//���������
/*
while (p->next != q) {
	t = p->next;
	p->next=t->next;
	t->next=q->next;
	q->next=t;
}
*/

/*
���⣺
�轫n(n>1)��������ŵ�һά����R�С������һ����ʱ��Ϳռ������涼�����ܸ�Ч���㷨����R�б��������ѭ������p(0<p<n)��λ�ã�����R�е�Ԫ��(Xo��X1��...Xn-1)�������ƶ����Ϊ:(Xp��Xp+1,...Xn-1,Xo,X1,...Xp-1)��
Ҫ��:
(1)�����㷨�Ļ������˼�롣
(2)�������˼�룬����C��C++��JAVA���������㷨���ؼ�֮������ע�͡�
(3)˵����������㷨��ʱ�临�ӶȺͿռ临�Ӷȡ�		ʱ�临�Ӷȣ�O(n),�ռ临�Ӷȣ�O(1)
*/
//(1)�Ƚ�ǰXo,X1,...Xp-1���ã��ٽ�Xp��Xp+1,...Xn-1���ã�����ٽ�����������
//(2)����
void reverse(int a[], int left, int right, int k) {
	int temp;
	for (int i = left, j = right;i < left + k && i < j; i++, j--) {
		temp = a[i];
		a[i] = a[j];
		a[j] = temp;
	}
}
void moveP(int a[], int n, int p) {
	reverse(a, 0, p - 1, p);//ǰ������
	reverse(a, p, n - 1, n - p);//�������
	reverse(a, 0, n - 1, n);//ȫ������
}

//���㣺ȡ��ֵ
//˳���
/*
int max = a[0];
int maxIdx = 0;  ��¼���ֵ����Сֵ
for(int i=0;i<n;i++){
	if(max<a[i]){
		max=a[i];
		maxIdx=i;
	}
}

����
LNode* p, * q;
int max = head->next->data;
q = p = head->next; p���� q��¼
while(p!=NULL){
	if(max<p->data){
		max=p->data;
		q=p
	}
	p=p->next;
}
*/
/*
һ˫����ǿգ���headָ��ָ�������ṹΪ{ llink��data,rlink }�������һ�������������dataֵ
�����Ǹ����(���ֵ���ֻ��һ��)�ƶ���������ǰ�ߵ��㷨��Ҫ�󲻵������½��ռ䡣
*/
typedef struct DLNode {
	int data;
	struct DLNode* llink;
	struct DLNode* rlink;
}DLNode;
void maxFirst(DLNode* head) {
	DLNode* p = head->rlink, *q = p;
	int max = p->data;
	//����ֵ
	while (p != NULL) {
		if (max < p->data) {
			max = p->data;
			q = p;
		}
		p = p->rlink;
	}
	//��ɾ����
	DLNode* l = q->llink, * r = q->rlink;
	l->rlink = r;
	if(r!=NULL)
		r->llink=l;
	//����
	q->llink = head;
	q->rlink = head->llink;
	head->rlink = q;
	q->rlink->llink = q;
}


/*���㣺����
һ����Ϊ˳����еĵ�һ��Ԫ��������������
void partition(int arr[], int n) {
	int temp;//��Ż�������
	int i = 0, j = n - 1;
	temp = arr[i];
	while (i < j) {
		//ɨ��Ԫ��
		while (i < j && arr[j] >= temp)--j;
		//����Ԫ��
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
����������һ��ֵ��Ϊ�Ƚϵı�׼ ����Ϊ:X �Ƚϱ�׼Ϊ��Y
void partition(int arr[], int n,int comp){
	int temp;//��Ż�������
	int i = 0, j = n - 1;
	temp = arr[i];
	while (i < j) {
		//ɨ��Ԫ��
		while (i < j && arr[j] >= comp)--j;
		//����Ԫ��
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
������˳����е�����Ԫ�ؽ��л���
����Ԫ�ػ�λ�����еĵ�һ��Ԫ�ؼ��ɿ�ʼ����
void partition(int arr[], int n,int k) {
	int temp;//��Ż�������
	int i = 0, j = n - 1;
	//���л�λ����
	temp = arr[0];
	arr[0] = arr[k];
	arr[k] = temp;
	while (i < j) {
		//ɨ��Ԫ��
		while (i < j && arr[j] >= temp)--j;
		//����Ԫ��
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
//��һ�����Ա����ô�ͷ���ĵ�����L���洢�����һ���㷨�������á�Ҫ���ܽ����½�㣬ֻ��ͨ���������н��������������ɡ�
void reverse(LNode* L) {
	LNode* p = L->next, * q;//q���ڱ��p����һ�����
	L->next = NULL;
	while (p != NULL) {
		q = p->next;
		p->next = L->next;
		L->next = p;
		p = q;
	}
}
//���⣺��N����λ�����������int������A[0,..N-1]�У�NΪ�Ѷ���ĳ�����N<=9������A[]�ĳ���ΪN�����һ��int�ͱ���i��Ҫ��ֻ����������(A[0]~A[N-1]��i����N+1�����ͱ���)дһ���㷨���ҳ���N�������е���С�ߣ�����Ҫ�����ƻ�����A[]�е����ݡ�
//i�ĸ�λ�洢��ֵ  i�ĸ�λ��������
int N;
void findmin(int A[], int& i) {
	i = A[0];//A[0]����i�ĸ�λ��
	while (i / 10 <= N - 1) {//i/10ȡ����i�ĸ�λ
		if (i % 10 > A[i / 10])//i%10 ȡi��λ���ϵ�ֵ
		{
			i = i - i % 10;//��i�ĸ�λ����
			i = i + A[i / 10];
		}
		i = i + 10;
	}
	i = i % 10;//��i�ĸ�λ��ֵ��i
}
//���⣺дһ�������������ӡ�������е����ݣ�����ָ��Lָ���˵�����Ŀ�ʼ��㡣
//(1)����ջ�Ľṹ�����(2)�ݹ����,���÷��β���
void reprint(LNode* L) {//����reprint�����Ѿ����Խ�һ���������������
	if (L != NULL) {
		reprint(L->next);//�������ӡ��L�����������Ϣ
		printf("%d", L->data);
	}
}
//ʱ�临�Ӷ�ΪO(n),�ռ临�ӻ���O(n)

//���⣺���������������ɵļ���A��B���ж����������Ƿ����
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
	if (p != NULL || q != NULL)//���p��q�Ƿ�û��ɨ�����
		return 0;
	else
		return 1;
}

//���㣺�鲢
void mergearray(int a[], int m, int b[], int n, int c[]) {
	//m,n�ֱ��ʾ����ĳ���
	int i = 0, j = 0;
	int k = 0;
	while (i < m && j < n) {
		if (a[i] < b[j])
			c[k++] = a[i++];//c[k]=a[i];k++;i++
		else
			c[k++] = b[j++];
	}
	//a����ĳ��ȴ���b����  �� ����
	while (i < m)
		c[k++] = a[i++];
	while (j < n)
		c[k++] = b[j++];
}
//����Ĺ鲢
//��ͷ�������
void merge(LNode* A, LNode* B, LNode* C) {
	LNode* p = A->next;
	LNode* q = B->next;
	LNode* r;
	C = A;//��A��ͷ��㸳��C
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
//����鲢��ͷ�巨   �鲢���������ԭ�����˳���෴
void mergeR(LNode* A, LNode* B, LNode* C) {
	LNode* p = A->next;
	LNode* q = B->next;
	LNode* s;//��¼p��q
	C = A;//C����A��ͷ���
	C->next = NULL;
	free(B);//B��ʾ��ֻ����ͷ���  �൱��ͷ���ָ��
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