#include<math.h>//����ȡ����ֵ����
#include<stdio.h>
//˳��ջ�ı�ʾ
#define maxSize 10
#define MIN 0
int stack[maxSize];
int top = -1;
//���㣺ջ��ʵ�ֱ��ʽ��ת��
/*
1.��׺תΪǰ׺  ���ȼ����ȫ����ջ
2.��׺תΪ��׺  ���ȼ����ڵ��ڵ�ȫ����ջ
*/
int getPriority(char ch) {

}
//s2Ϊ���ջ  s1Ϊ����ջ   ��׺תΪ��׺
void infixToPostFix(char infix[], char s2[], int& top2) {
	char s1[maxSize];
	int top1 = -1;
	int i = 0;
	while (infix[i] != '/0') {
		if ('0' <= infix[i] && infix[i] <= '9') {//�жϵ�ǰ���ַ��Ƿ�Ϊ���ʽ
			s2[++top2] = infix[i];//����ǰ�ı��ʽ����ջ
			++i;
		}
		else if(infix[i]=='('){//�����"("����ȫ���븨��ջ
			s1[++top1] = infix[i];//
			++i;
		}
		//�ж�����������ȼ�  ��ǰ����������ȼ����ڸ���ջ��ջ�������ȼ��������ջ
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
		else if (infix[i] == ')') {//���Ϊ��"("��ȫ��������ջ
			while (s1[top1] != ')')
				s2[++top2] = s1[top1--];
			top1--;
			i++;
		}
	}
	while (s1[top] != -1) {//������ջ��ʣ���Ԫ��ȫ����ջ
		s2[++top2] = s1[top1--];
	}
}
//��׺���ʽתΪ��׺���ʽ
void infixToEnd(char infix[],int len,char s2[],int &top2){
	char s1[maxSize];
	int top1 = -1;
	int i = len-1;//�Ӻ���ǰ��ɨ��
	while (infix[i] != '/0') {
		if ('0' <= infix[i] && infix[i] <= '9') {//�жϵ�ǰ���ַ��Ƿ�Ϊ���ʽ
			s2[++top2] = infix[i];//����ǰ�ı��ʽ����ջ
			--i;
		}
		else if(infix[i]==')'){//�����"��"����ȫ���븨��ջ
			s1[++top1] = infix[i];//
			--i;
		}
		//�ж�����������ȼ�  ��ǰ����������ȼ����ڵ��ڸ���ջ��ջ�������ȼ��������ջ
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
		else if (infix[i] == '(') {//���Ϊ��"("��ȫ��������ջ
			while (s1[top1] != ')')
				s2[++top2] = s1[top1--];
			top1--;
			i--;
		}
	}
	while (s1[top] != -1) {//������ջ��ʣ���Ԫ��ȫ����ջ
		s2[++top2] = s1[top1--];
	}
}

/*���㣺��ջ��ʵ�ֱ��ʽ�ļ���
1.��׺��ʾ�ļ���*/
int getPriority(char op){
	if(op=='+' || op=='-')
		return 0;
	else
		return 1;
}
//�ӱ��ʽ����ֵ
int calSub(float opand1,char op,float opand2,float &result){
	if(op=='+')result=opand1+opand2;
	if(op=='-')result=opand1-opand2;
	if(op=='*')result=opand1*opand2;
	if(op=='/'){//����ĸΪ0ʱ  ��ʽ������
		//�ж�float���͵���ֵ�Ƿ�Ϊ0
		if(fabs(opand2) < MIN)//fabs()�Դ����float�����������ֵ 
			return 0;
		else
			result=opand1/opand2;
	}
	return 1;
}

int calStackTopTow(float s1[],int &top1,char s2[],int &top2){
	float opnd1,opnd2,result;
	char op;
	int flag;//��־λ
	opnd2=s1[top1--];
	opnd1=s1[top1--];
	op=s2[top2--];
	flag=calSub(opnd1,op,opnd2,result);
	s1[top1++]=result;//������Ľ��д��s1ջ��
	return flag;
}
//�����׺���ʽ
float calInFix(char exp[]){
	float s1[maxSize];int top1=-1;//װ�������Ļ���ʽ��
	char s2[maxSize];int top2 =-1;//װ�������
	int i=0;//�Ա��ʽ��0��ʼ����ɨ��
	while(exp[i]!='/0'){//�ж��ַ����Ƿ�Ϊ0
	//1.�Բ�����������ջ�Ĵ���
		if(exp[i]>='0' && exp[i]<='9'){
			s1[++top1]=exp[i]-'0';//���ַ�����ת��Ϊ��ֵȻ����ջ
			i++;
		}
		//2.�������ŵĴ���
		else if(exp[i]=='('){
			s2[++top2]='(';//���������������ջ
			i++;
		}
		//3.����������д���
		//ֱ����ջ����
		else if(exp[i]=='+' ||exp[i]=='-' ||
				exp[i]=='*' ||exp[i]=='/'){
				if(top2=-1 || s2[top2]=='('||
				getPriority(exp[i])>getPriority(s2[top2])){
				//��s2��Ϊ�ջ�s2ջ��ǰԪ��Ϊ"("��ǰ����������ȼ�����ջ��Ԫ�ص����ȼ�
					s2[top2++]=exp[i];
					++i;
			}
					else{
							int flag= calStackTopTow(s1,top1,s2,top2);
							if(flag==0)
								return 0;
				}			
		}
		//4.��")"����
		else if(exp[i]==')'){
			while(s2[top2++]!='('){
				int flag = calStackTopTow(s1,top1,s2,top2);
				if(flag==0)
					return 0;
			}
			--top2;//����Ҫ������  �ʽ�ջ��ָ�����һλ
			++i;
		}
	}
	//�ж�ջ���Ƿ���Ԫ��ʣ��
	while(top2!=-1)
	{
		int flag=calStackTopTow(s1,top1,s2,top2);
		if(flag==0)
			return 0;
	}
	return s1[top1];
}
//��ջ����׺���ʽ
/*
�㷨˼�룺�ȶԺ�׺�ַ�������ɨ��
*/
float calPostFix(char exp[]){
	float s[maxSize];int top=-1;
	for(int i=0;exp[i]!='\0';i++){//ɨ�������ĺ�׺���ʽ
		//���ɨ�赽���Ǳ��ʽ ����ջ  ������������ջ�������ʽ��������
		if('0'<=exp[i] && exp[i]<='9'){
			s[top++]=exp[i]-'0';//���ַ�������ת��Ϊ��ֵ������ Ȼ�����ջ��
		}
		else{
			//��ջ��ȡ������Ԫ�ؽ��м���
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
//��ջʵ��ǰ׺���ʽ�ļ���
float claPreFix(char exp[],int len){
	float s[maxSize];int top=-1;
	for(int i=len-1;i>=0;--i){
		if('0'<=exp[i] && exp[i] <='9'){
			s[top--]=exp[i]-'0';//ת��Ϊ��ֵ����
		}
		//�Ӻ���ǰɨ��
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
//���㣻˫�˶���  ���˶��ɽ��в����ɾ������
 //���˲���������
 
 //���㣺ջ����չ������ջ��
 int stack[maxSize];
 //int top1=-1,top2=maxSize;<==>
 int top[2]={-1,maxSize};
 //top2ָ�����һ��Ԫ�صĺ�һ��λ��
 //��top[0]=-1,top[1]=maxSizeʱ ����ջΪ��ջ
 /*
 ��ջ:
  s1:stack[++top[0]]=x;[]
  s2:stack[--top[1]]=x;
  top[0]+1==top[1];ջ��
 */

//���㣺����ƥ��
//������ƥ�亯��
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
		//��ǰ��Ԫ��Ϊ����������ջ
		if(exp[i]=='(' || exp[i]=='[' || exp[i]=='{')
			s[++top]=exp[i];
		if(exp[i]==')' || exp[i]==']' || exp[i]=='}'){
			if(top==-1)//ջ�������Ų�ƥ��
				return 0;
			//��ջ�г�ջһ��Ԫ�ؽ���ƥ��
			char left=s[--top];
			if(isMatched(left,exp[i])==0)
				return 0;	
		}
	}
	if(top>-1)//ȫ���ַ�ɨ�����  ���ջ�ǿ� �����Ų�ƥ��
		return 0;
	return 1;
}
 
 //��ջ����⺯����δ֪����ֵ
 int calF(int m){
	 int cum=1;//��¼�۳˵��м���
	 int s[maxSize],top=-1;
	 while(m!=0){
		 //��ÿ�εõ�������ѹ��ջ��
		 s[++top]=m;
		 m/=3;
	 }
	 while(top!=-1)
		 cum *=s[--top];
	 return cum;
 }