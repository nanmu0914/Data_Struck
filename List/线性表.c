/*
分配存储容量的结构体
结构体
struct 结构体名称 结构体变量名
//线性表
1.存储空间的基址 指针(*)
2.存储的长度
3.当前存储分配的容量
typedef  //为类型定义一个新的类型
*/
#inclde<malloc.h>//申请内存的头文件库

#define OVERFLOW	-2
#define	OK	1	
#define ERROR -1

typedef struct{
	int *elem;
	int	listlong;
	int	listsize;
}Sqlist;

/*
创建一个空的线性表  sizeof 获取数据在内存中的存储空间,以字节为单位来计数
1.申请一个存储空间
2.给长度和大小都初始分配一个值
3.返回
*/
int CreateList(Sqlist L){
	L.elem = (int *)malloc(100 * sizeof(int));//int 为4个字节 malloc（存储空间的初始分配量 * 字节数）
	if(!L.elem) exit(OVERFLOW);
	L.listlong = 0;
	L.listsize = 100;
	return Ok;
}

/*
创建一个非空的线性表
1.申请地址空间
2.分配存储空间的大小
3.插入数据
4.打印插入的数据
*/
int CreateNotNullList(Sqlist L){
	L.elem = (int *)malloc(100 * sizeof(int));
	if (!L.elem) exit(OVERFLOW);
	L.listsize = 100;
	printf("请输入数据：\n");
	for(int i =0;i<L.listlong;i++){
		scanf("%d",&L.elem[i]);//依次往列表里面输入数据
	}
	return OK;
}

/*
某一个位置插入数据  n-i+1
(插入的表，插入的位置，插入的数据)
1.判断插入的位置是否合法
a.判断i是否比最小位置要小
b.判断i是否比最大的位置+1要大（超出列表的长度）
2.判断存储的空间是否已满 如果满了就在原存储空间的基础上
增加内存 
realloc(地址空间，（原本+增加的大小）*字节数)
3.更新地址空间和当前存储的容量
4.找出指定的位置 
a.从最后一个元素往前找
定义两个指针  第一个为要找的位置-1 第二个为最后的位置
b.for循环遍历  同时将列表里的每个值都往下移
5.赋值 长度++
*/
int Insert_List(Sqlist L,int i,int e){
	if(i < 1 || i > L.listlong+1) return ERROR;
	if( L.listlong >= L.listsize){
		int *newbase;
		newbase = (int *)realloc(L.elem,(L.listsize + 10) * sizeof(int));
	}
	L.elem = newbase;
	L.listsize = L.listsize + 10;
	int *p,*q;
	q = &(L.elem[i-1]);
	for(p=&(L.elem[L.listlong-1]);p>=q;--p){//如p与q相等条件去掉则会出现第i+1与第i+2的值相等
		  *(p+1)=*p
	}
	*p=e;
	++L.listlong;
	return OK;
}

//删除固定位置的值
int Delete_List(Sqlist L,int i,int e){
	if(i<1 || i>L.listlong+1)return ERROR;
	int *p,*q;
	q = &(L.elem[i]);
	for(p = &(L.elem(L.listlong-1));p >=q;--p){
		*(p-1)=*p;
	}
	e = L.elem[i];
	return OK;
}


