/*
  TITLE: Implement stack  as  an  abstract  data  type  using  linked  list  and  use  this  ADT  for  conversion  of  
	infix expression to postfix, prefix and evaluation of postfix and prefix expression.
*/

#include<iostream>
#include<stdlib.h>
#include<string.h>
#include "1stack.h"
using namespace std;
class PostfixPrefix
{
	public:
	
	 char info[30],postfix[30],reverse[30],prefix[30];
	int s;
		PostfixPrefix()
		{
			s=0;
		}
		void input();
		void infix_to_postfix(char[]);
		void infix_to_prefix(char[]);
		void postfixToPrefix();
		int priority(char);
		void display();
		void evaluation();
		int evaluate(char ,int ,int );
		void eva_postfix(char []);
		void eva_prefix(char []);
};
void PostfixPrefix::input()
{
	int flag=0;
	cout<<"\nEnter the infix expression:\n";
	cin>>info;
	int ch=0;
	while(ch!=3)
	{
		cout<<"\nEnter \n 1 To convert in postfix expression \n 2 To convert in prefix expression \n 3 Exit\n";
		cin>>ch;
		switch(ch)
		{
			case 1:
				infix_to_postfix(info);
				break;
			case 2:
				s=0;
				infix_to_prefix(info);
				postfixToPrefix();
				break;				
		}
	}
	
}
void PostfixPrefix::infix_to_prefix(char info[30])
{
	int i,j;
	char rev[30];
	for(i=0;info[i]!='\0';i++);	//to move to last char
	i--;
	for(j=0;i>=0;j++)	//to reverse string
	{
		rev[j]=info[i];
		i--;
	}
	rev[j]='\0';
	cout<<"\nInfix Expression is :"<<info<<"\n";
	cout<<"\nReverse of infix expression is:"<<rev;
	for(i=0;i<strlen(rev);i++)	//replacing brackets
	{
		if(rev[i]=='(')
		rev[i]=')';
		else if(rev[i]==')')
		rev[i]='(';
	}
	cout<<"\nAfter changing opening and closing brackets:"<<rev;
	infix_to_postfix(rev);
}

void PostfixPrefix::infix_to_postfix(char reverse[30])
{
	int i,len;
	stack st;
	char symbol,r;
	
	len=strlen(reverse);
	cout<<"\nStep \t Infix Expression \t\t Stack \t\t\t Postfix Expression \n";
	for(i=0;i<len;i++)	//aceepting single character
	{
		symbol=reverse[i];
		switch(symbol)
		{
			case '(':
				st.push(symbol);
				break;
			case ')':
				while((r=st.pop())!='(' && st.top!=NULL)
				{
					postfix[s]=r;
					s++;
				}
				//postfix[s]='\0';
				break;
			case '+':
			case '-':
			case '/':
			case '%':
			case '*':
			case '^':
				while(st.top!=NULL && priority(st.top->data)>=priority(symbol))	
				{
					postfix[s]=st.pop();	//if precedence of operator is higher or equal than current
								//pop element
					s++;
				}
				st.push(symbol);
				break;
				
			default:
				postfix[s]=symbol;	//for character
				s++;
				break;
		};
			
		
		cout<<"\n"<<i+1<<"\t"<<symbol<<"\t\t\t\t";
		st.display();
		postfix[s]='\0';
		cout<<"\t\t\t\t"<<postfix<<"\n";
		
	}
	if(info[len]!=')')	//for remaining element
	{
		while(st.top!=NULL)
		{
			char r=st.pop();
			postfix[s]=r;
			s++;
		}
		
	}
	cout<<"\n"<<i+1<<"\t-"<<"\t\t\t\t";
		st.display();
		cout<<"\t\t\t\t"<<postfix<<"\n";
	cout<<"\nPostfix expression is:"<<postfix<<"\n";
	//postfixToPrefix();
}
void PostfixPrefix::postfixToPrefix()
{
	int i,j;
	for(i=0;postfix[i]!='\0';i++);
	i--;
	for(j=0;i>=0;j++)
	{
		prefix[j]=postfix[i];
		i--;
	}
	prefix[j]='\0';
	cout<<"\nPrefix expression is :"<<prefix<<"\n";
	
}
int PostfixPrefix::priority(char symbol)
{
	switch(symbol)
	{
		case '(':
			return 0;
		case '+':
		case '-':
			return 1;
		case '*':
		case '/':
		case '%':
			return 2;
		case '^':
			return 3;
		/*default:
			return 0;*/
	}
}

void PostfixPrefix::evaluation()
{
	int ch=0,len,cnt,cnt1;
	do
	{
		cout<<"\n1.Postfix evaluation \n2.Prefix evaluation \n3.Exit";
		cin>>ch;
		switch(ch)
		{
			case 1:
			cout<<"\nEnter postfix expression: ";
			cin>>postfix;
			len=strlen(postfix);
			cnt=cnt1=0;
			if(isalnum(postfix[0]) && isalnum(postfix[1]) && !isalnum(postfix[len-1]) )
			{
				for(int i=0;i<len;i++)
				{
					if( isalnum(postfix[i]) )
						cnt++;
					else
						cnt1++;
				}
				if( cnt>cnt1)	
					cout<<postfix;
				else
				{
					cout<<"\n Invalid expression..\n";
					break;
				}
			}
			else
			{
				cout<<"\n Invalid expression..\n";
				break;
			}	
			eva_postfix(postfix);
			break;
			
			case 2:
			cout<<"\nEnter prefix expression: ";
			cin>>prefix;
			len=strlen(prefix);
			cnt=cnt1=0;
			if(!isalnum(prefix[0]) && isalnum(prefix[len-1]) && isalnum(prefix[len-2]) )
			{
				for(int i=0;i<len;i++)
				{
					if( isalnum(prefix[i]) )
						cnt++;
					else
						cnt1++;
				}
				if( cnt>cnt1)	
					cout<<prefix;
				else
				{
					cout<<"\n Invalid expression..\n";
					break;
				}
			}
			else
			{
				cout<<"\n Invalid expression..\n";
				break;;
			}	
			
			
			eva_prefix(prefix);
			break;	
		}
	}while(ch!=3);
}

int PostfixPrefix::evaluate(char x,int op1,int op2)
{
	if(x=='+') return(op1+op2);
	if(x=='-') return(op1-op2);
	if(x=='*') return(op1*op2);
	if(x=='/') return(op1/op2);
	if(x=='^') return(op1^op2);
	if(x=='%') 
	return(op1%op2);
}



void PostfixPrefix:: eva_postfix(char postfix[])
{
	stack st;
	char x;
	int op1,op2,val,flag=0;
	
	for(int i=0;postfix[i]!='\0';i++)
	{      
		x=postfix[i];
		if(isalnum(x))
		{
			cout<<"\nEnter value of character "<<x<<" : ";
			cin>>val;
			st.push(val);
			
			

		}
		else
		{
			op2=st.pop();
			op1=st.pop();
			val=evaluate(x,op1,op2);
			st.push(val);
			
			
		}
		flag=1;
		cout<<"\n"<<i+1<<"\t"<<postfix[i]<<"\t\t\t\t";
		st.display();
					
	}
	
	val=st.pop();
	cout<<"\nValue is :"<<val;
}

void PostfixPrefix:: eva_prefix(char prefix[])
{
	stack st;
	char x;
	int op1,op2,val,flag=0;
	for(int i=strlen(prefix)-1;i>=0;i--)
	{
		x=prefix[i];
		if(isalnum(x))
		{
			cout<<"\nEnter value of character "<<x<<" : ";
			cin>>val;
			st.push(val);
		}
		else
		{
			op1=st.pop();
			op2=st.pop();
			val=evaluate(x,op1,op2);
			st.push(val);
		}
		flag=1;
		cout<<"\n"<<i+1<<"\t"<<prefix[i]<<"\t\t\t\t";
		st.display();
	}
	val=st.pop();
	cout<<"\nValue is :"<<val;
}

int main()
{
	PostfixPrefix pp;
	int c;
	do
	{
		cout<<"\nChoose from following \n1.Expression conversion \n2.Expression evaluation";
		cout<<"\n3.Exit \nEnter your choice :";
		cin>>c;
		if(c==1)
		   pp.input();
		if(c==2)
		   pp.evaluation();	
	}while(c!=3);
	return 0;
	
}

/*OUTPUT

	student@ubuntu:~/Desktop$ g++ 1stack.cpp
	student@ubuntu:~/Desktop$ ./a.out

	Choose from following 
	1.Expression conversion 
	2.Expression evaluation
	3.Exit 
	Enter your choice :1

	Enter the infix expression:
	(a+b*c)*d

	Enter 
	 1 To convert in postfix expression 
	 2 To convert in prefix expression 
	 3 Exit
	1

	Step 	 Infix Expression 		 Stack 			 Postfix Expression 

	1	(				|(|#|				

	2	a				|(|#|				a

	3	+				|+|(|#|				a

	4	b				|+|(|#|				ab

	5	*				|*|+|(|#|			ab

	6	c				|*|+|(|#|			abc

	7	)				|#|				abc*+

	8	*				|*|#|				abc*+

	9	d				|*|#|				abc*+d

	10	-				|#|				abc*+d*

	Postfix expression is:abc*+d*

	Enter 
	 1 To convert in postfix expression 
	 2 To convert in prefix expression 
	 3 Exit
	2

	Infix Expression is :(a+b*c)*d

	Reverse of infix expression is:d*)c*b+a(
	After changing opening and closing brackets:d*(c*b+a)
	Step 	 Infix Expression 		 Stack 			 Postfix Expression 

	1	d				|#|				d

	2	*				|*|#|				d

	3	(				|(|*|#|				d

	4	c				|(|*|#|				dc

	5	*				|*|(|*|#|				dc

	6	b				|*|(|*|#|				dcb

	7	+				|+|(|*|#|				dcb*

	8	a				|+|(|*|#|				dcb*a

	9	)				|*|#|				dcb*a+

	10	-				|#|				dcb*a+*

	Postfix expression is:dcb*a+*

	Prefix expression is :*+a*bcd

	Enter 
	 1 To convert in postfix expression 
	 2 To convert in prefix expression 
	 3 Exit
	3
	Choose from following 
	1.Expression conversion 
	2.Expression evaluation
	3.Exit 
	Enter your choice :2

	1.Postfix evaluation 
	2.Prefix evaluation 
	3.Exit1

	Enter postfix expression: abcd*-+
	abcd*-+
	Enter value of character a : 0

	1	a				|0 #|
	Enter value of character b : 1

	2	b				|1 0 #|
	Enter value of character c : 2

	3	c				|2 1 0 #|
	Enter value of character d : 3

	4	d				|3 2 1 0 #|
	5	*				|6 1 0 #|
	6	-				|-5 0 #|
	7	+				|-5 #|
	Value is :-5
	1.Postfix evaluation 
	2.Prefix evaluation 
	3.Exit2

	Enter prefix expression: +*ab/cd
	+*ab/cd
	Enter value of character d : 1

	1	d				|1 #|
	Enter value of character c : 2

	2	c				|2 1 #|
	3	/				|2 #|
	Enter value of character b : 3

	4	b				|3 2 #|
	Enter value of character a : 4

	5	a				|4 3 2 #|
	6	*				|12 2 #|
	7	+				|14 #|
	Value is :14
	1.Postfix evaluation 
	2.Prefix evaluation 
	3.Exit1

	Enter postfix expression: *ab+/

	 Invalid expression..

	1.Postfix evaluation 
	2.Prefix evaluation 
	3.Exit3

	Choose from following 
	1.Expression conversion 
	2.Expression evaluation
	3.Exit 
	Enter your choice :3

	*/
