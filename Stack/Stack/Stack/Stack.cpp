#include<math.h>//调用取绝对值函数
#include<stdio.h>
//顺序栈的表示
#define maxSize 10
#define MIN 0
int stack[maxSize];
int top = -1;
//考点：栈来实现表达式的转换
/*
1.中缀转为前缀  优先级大的全部进栈
2.中缀转为后缀  优先级大于等于的全部进栈
*/
int getPriority(char ch) {

}
//s2为结果栈  s1为辅助栈   中缀转为后缀
void infixToPostFix(char infix[], char s2[], int& top2) {
	char s1[maxSize];
	int top1 = -1;
	int i = 0;
	while (infix[i] != '/0') {
		if ('0' <= infix[i] && infix[i] <= '9') {//判断当前的字符是否为表达式
			s2[++top2] = infix[i];//将当前的表达式入结果栈
			++i;
		}
		else if(infix[i]=='('){//如果是"("则将其全部入辅助栈
			s1[++top1] = infix[i];//
			++i;
		}
		//判断运算符的优先级  当前运算符的优先级大于辅助栈中栈顶的优先级则进辅助栈
		else if (infix[i] == '+' ||
			infix[i] == '-' ||
			infix[i] == '*' ||
			infix[i] == '/') {
			if (top1 = -1 || s1[top1] == '(' ||
				getPriority(infix[i]) > getPriority(s1[top1]))
			{
				s1[++top1] = infix[i];
				++i;
			}
			else
				s2[++top2] = s1[--top1];//
		}
		else if (infix[i] == ')') {//如果为非"("则全部出辅助栈
			while (s1[top1] != ')')
				s2[++top2] = s1[top1--];
			top1--;
			i++;
		}
	}
	while (s1[top] != -1) {//将辅助栈中剩余的元素全部出栈
		s2[++top2] = s1[top1--];
	}
}
//中缀表达式转为后缀表达式
void infixToEnd(char infix[],int len,char s2[],int &top2){
	char s1[maxSize];
	int top1 = -1;
	int i = len-1;//从后往前的扫描
	while (infix[i] != '/0') {
		if ('0' <= infix[i] && infix[i] <= '9') {//判断当前的字符是否为表达式
			s2[++top2] = infix[i];//将当前的表达式入结果栈
			--i;
		}
		else if(infix[i]==')'){//如果是"）"则将其全部入辅助栈
			s1[++top1] = infix[i];//
			--i;
		}
		//判断运算符的优先级  当前运算符的优先级大于等于辅助栈中栈顶的优先级则进辅助栈
		else if (infix[i] == '+' ||
			infix[i] == '-' ||
			infix[i] == '*' ||
			infix[i] == '/') {
			if (top1 = -1 || s1[top1] == ')' ||
				getPriority(infix[i]) >= getPriority(s1[top1]))
			{
				s1[++top1] = infix[i];
				--i;
			}
			else
				s2[++top2] = s1[--top1];//
		}
		else if (infix[i] == '(') {//如果为非"("则全部出辅助栈
			while (s1[top1] != ')')
				s2[++top2] = s1[top1--];
			top1--;
			i--;
		}
	}
	while (s1[top] != -1) {//将辅助栈中剩余的元素全部出栈
		s2[++top2] = s1[top1--];
	}
}

/*考点：用栈来实现表达式的计算
1.中缀表示的计算*/
int getPriority(char op){
	if(op=='+' || op=='-')
		return 0;
	else
		return 1;
}
//子表达式的求值
int calSub(float opand1,char op,float opand2,float &result){
	if(op=='+')result=opand1+opand2;
	if(op=='-')result=opand1-opand2;
	if(op=='*')result=opand1*opand2;
	if(op=='/'){//当分母为0时  等式不成立
		//判断float类型的数值是否为0
		if(fabs(opand2) < MIN)//fabs()对传入的float参数求其绝对值 
			return 0;
		else
			result=opand1/opand2;
	}
	return 1;
}

int calStackTopTow(float s1[],int &top1,char s2[],int &top2){
	float opnd1,opnd2,result;
	char op;
	int flag;//标志位
	opnd2=s1[top1--];
	opnd1=s1[top1--];
	op=s2[top2--];
	flag=calSub(opnd1,op,opnd2,result);
	s1[top1++]=result;//将计算的结果写入s1栈中
	return flag;
}
//求解中缀表达式
float calInFix(char exp[]){
	float s1[maxSize];int top1=-1;//装操作数的或表达式的
	char s2[maxSize];int top2 =-1;//装运算符的
	int i=0;//对表达式从0开始依次扫描
	while(exp[i]!='/0'){//判断字符串是否为0
	//1.对操作数进行入栈的处理
		if(exp[i]>='0' && exp[i]<='9'){
			s1[++top1]=exp[i]-'0';//将字符数字转化为数值然后入栈
			i++;
		}
		//2.对左括号的处理
		else if(exp[i]=='('){
			s2[++top2]='(';//将左括号入运算符栈
			i++;
		}
		//3.对运算符进行处理
		//直接入栈处理
		else if(exp[i]=='+' ||exp[i]=='-' ||
				exp[i]=='*' ||exp[i]=='/'){
				if(top2=-1 || s2[top2]=='('||
				getPriority(exp[i])>getPriority(s2[top2])){
				//当s2张为空或s2栈当前元素为"("或当前运算符的优先级大于栈顶元素的优先级
					s2[top2++]=exp[i];
					++i;
			}
					else{
							int flag= calStackTopTow(s1,top1,s2,top2);
							if(flag==0)
								return 0;
				}			
		}
		//4.对")"处理
		else if(exp[i]==')'){
			while(s2[top2++]!='('){
				int flag = calStackTopTow(s1,top1,s2,top2);
				if(flag==0)
					return 0;
			}
			--top2;//不需要左括号  故将栈顶指针后移一位
			++i;
		}
	}
	//判断栈中是否还有元素剩余
	while(top2!=-1)
	{
		int flag=calStackTopTow(s1,top1,s2,top2);
		if(flag==0)
			return 0;
	}
	return s1[top1];
}
//用栈求解后缀表达式
/*
算法思想：先对后缀字符串进行扫描
*/
float calPostFix(char exp[]){
	float s[maxSize];int top=-1;
	for(int i=0;exp[i]!='\0';i++){//扫描所给的后缀表达式
		//如果扫描到的是表达式 则入栈  若是运算符则出栈两个表达式进行运算
		if('0'<=exp[i] && exp[i]<='9'){
			s[top++]=exp[i]-'0';//将字符型数据转化为数值型数据 然后存入栈中
		}
		else{
			//从栈中取出两个元素进行计算
			float opnd1,opnd2,result;char op;
			opnd2=s[top--];
			opnd1=s[top--];
			op=exp[i];
			int flag = calSub(opnd1,op,opnd2,result);
			if(flag==0){
				puts("ERROR!");
				return 0;
			}
			s[top++]=result;
		}
	}
	return s[top];
}
//用栈实现前缀表达式的计算
float claPreFix(char exp[],int len){
	float s[maxSize];int top=-1;
	for(int i=len-1;i>=0;--i){
		if('0'<=exp[i] && exp[i] <='9'){
			s[top--]=exp[i]-'0';//转换为数值数据
		}
		//从后往前扫描
		else{
			float opnd1,opnd2,result;char op;
			opnd1=s[top--];
			opnd2=s[top--];
			op=exp[i];
			int flag=calSub(opnd1,op,opnd2,result);
			if(flag==0){
				puts("ERROR!");
				return 0;
			}
			s[top++]=result;
		}
	}
	return s[top];
}
//考点；双端队列  两端都可进行插入和删除操作
 //两端操作会受限
 
 //考点：栈的扩展（共享栈）
 int stack[maxSize];
 //int top1=-1,top2=maxSize;<==>
 int top[2]={-1,maxSize};
 //top2指向最后一个元素的后一个位置
 //当top[0]=-1,top[1]=maxSize时 共享栈为空栈
 /*
 入栈:
  s1:stack[++top[0]]=x;[]
  s2:stack[--top[1]]=x;
  top[0]+1==top[1];栈满
 */

//考点：括号匹配
//子括号匹配函数
int isMatched(char left,char right){
	if(left=='(' && right==')')
		return 1;
	else if(left=='{'&&right=='}')
		return 1;
	else if(left=='['&&right==']')
		return 1;
	else
		return 0;
}

int isParenthesesBalanced(char exp[]){
	int s[maxSize];int top=-1;
	for(int i=0;exp[i]!='\0';i++){
		//当前的元素为左括号则入栈
		if(exp[i]=='(' || exp[i]=='[' || exp[i]=='{')
			s[++top]=exp[i];
		if(exp[i]==')' || exp[i]==']' || exp[i]=='}'){
			if(top==-1)//栈空则括号不匹配
				return 0;
			//从栈中出栈一个元素进行匹配
			char left=s[--top];
			if(isMatched(left,exp[i])==0)
				return 0;	
		}
	}
	if(top>-1)//全部字符扫描完后  如果栈非空 则括号不匹配
		return 0;
	return 1;
}
 
 //用栈来求解函数中未知数的值
 int calF(int m){
	 int cum=1;//记录累乘的中间结果
	 int s[maxSize],top=-1;
	 while(m!=0){
		 //将每次得到的因子压入栈中
		 s[++top]=m;
		 m/=3;
	 }
	 while(top!=-1)
		 cum *=s[--top];
	 return cum;
 }