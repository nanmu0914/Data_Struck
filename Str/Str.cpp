#include<stdio.h>
#include<stdlib.h>
#define maxSize 10
//串的存储结构
/*定长存储结构：
typedef struct{
    char str[maxSize+1];
    int length;
}Str;*/
//数组的长度为maxSize+1  因为串会多出一个'\0'的结束标记

//变长存储结构
typedef struct{
    char *ch;
    int length;
}Str;
//给串分配一个存储空间
//S.ch =(char *)malloc((L+1)*sizeof(char));(L+1)为规模   ch指向存储空间的首地址

//串的基本操作
//1.赋值操作
//将一个串中的字符搬运到另外一个串中的过程<=>将一个数组中的元素赋值到另外一个数组中的过程
int strAssign(Str &str,char *ch){
    //参数1:串的结构体类型 
    //参数2：指向已申请好的连续存储空间的首地址（等效于定义一个数组参数）
    if(str.ch)//判断将要赋值的串是否已有存储空间  如有则释放
        free(str.ch);
    int len=0;
    char *c=ch;//c指向一片连续空间的首地址
    //确定赋值目标串的长度
    while(*c){//指针c所指元素的值不为0开始循环
        ++len;//记录串长
        ++c;
    }
    //赋值的数组中是个空串（空串赋值）
    if(len==0){
        str.ch=NULL;
        str.length=0;
        return 1;
    }
    else{
        str.ch = (char *)malloc(sizeof(char)*(len+1));//分配存储空间
        //如果空间已满  空间申请失败
        if(str.ch==NULL)
            return 0;
        else{
            //将c指向赋值串的第一个字符
            c=ch;
            for(int i=0;i<=len;++i,++c)//i扫描所有的位置 c扫描所有的字符
            //将c所扫描到的搬运到i所扫描到的上面来
                str.ch[i]=*c;
            str.length=len;
            return 1;
        }
    }
}
//2.取串的长度  str.length;
//3.串比较
int strCompare(Str s1,Str s2){
    for(int i=0;i<s1.length && i<s2.length;i++)
        if(s1.ch[i]!=s2.ch[i])
            return s1.ch[i]-s2.ch[i];
    return s1.length-s2.length;
}

//4.串连接
int concat(Str &str,Str str1,Str str2){//参数1 结果串 参数2,3 连接的串
    if(str.ch){//判断结果串是否为空  不空则释放
        free(str.ch);
        str.ch=NULL;
    }
    str.ch=(char*)malloc(sizeof(char)*(str1.length+str2.length+1));
    if(!str.ch)//申请存储空间失败
        return 0;
    //将str1复制到str的前端
    int i=0;
    while(i<str1.length){
        str.ch[i]=str1.ch[i];
        ++i;
    }
    //将str2复制到str中str1的后边
    int j=0;
    while(j<=str2.length){
        str.ch[++j]=str2.ch[j];
        ++j;
    }
    str.length=str1.length+str2.length;
    return 1;
}

//5.求子串
int getSubString(Str &substr,Str str,int pos,int len){//pos为子串的开始 ken为子串的长度
    //判断那些条件是不合法的
    if(pos<0||pos>=str.length||len<0||len>str.length-pos)
        return 0;
    if(substr.ch){//判断当前用来装子串的数组是否为空  若不空则清除串
        free(substr.ch);
        substr.ch=NULL;
    }
    if(len==0){//所求的子串的长度为0
        substr.ch=NULL;
        substr.length=0;
        return 1;
    }
    else{
        substr.ch=(char *)malloc(sizeof(char)*(len+1));
        int i=pos;//记录原本串中子串的开始位置
        int j=0;
        while(i<pos+len){
            substr.ch[j]=str.ch[i];
            ++i;++j;
        }
        substr.ch[j]='\0';//将结束的标记赋给子串
        substr.length=len;
        return 1;
    }
}

//6.清空串
int clearString(Str &str){
    if(str.ch){
        free(str.ch);
        str.ch=NULL;
    }
    str.length=0;
    return 1;
}
/*考点：KMP算法
核心：直接移动模式串 使原本的前缀直接移动到后缀
公共前缀的长度小于子串的长度
*/
//Next数据的求解
void getNext(Str substr,int next[]){
    int j=1,t=0;//从1位置开始保存数据
    next[1]=0;
    while(j<substr.length){
        if(t==0||substr.ch[j]== substr.ch[t]){
            next[j+1]=t+1;
            ++t;++j;
        }
        else
            t=next[t];
    }
}

int KMP(Str str,Str substr,int next[]){
    int i=1,j=1; 
    while(i<=str.length && j<=substr.length){
        if(j==0||str.ch[i]==substr.ch[j]){
//if(j=0){i++;j++;}
            ++i;++j;
        }
        else{
            j=next[j];//不回溯
        }
    }
    if(j>substr.length)//如果超出位置  则匹配成功 返回模式串在主串中的起始位置
        return i-substr.length;
    else
        return 0;
}