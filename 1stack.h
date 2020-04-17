#include<iostream>
#include<stdlib.h>
using namespace std;
class stack 
{
	public:
	typedef struct node
	{
		char data;
		struct node *next;
		
	}node;
	 node *top,*p;
	
	
		stack()
		{
			top=NULL;
		}
		int empty()
		{
			if(top==NULL)
				return 1;
			return 0;
		}
		void push(char);
		char pop();
		void display();
};
void stack::push(char info)
{
	node *nn;
	nn=new node();
	nn->data=info;
	nn->next=NULL;

	if(top==NULL)
	{
		top=nn;
		
	}
	else
	{
		nn->next=top;
		top=nn;
		
	}
	
	
}

char stack::pop()
{
	node *p;
	char p1;
	if(top==NULL)
	{
		cout<<"\nStack is empty.\n";
		
	}
	else
	{
		
		p=top;
		top=top->next;
		//cout<<"\n"<<p->data<<" is poped.\n";
		p1=p->data;
		free(p);
		return p1;
		
		
	}
}
void stack::display()
{
	int info;
	int flag;
	if(top==NULL)
	{
		cout<<"|#|";
	}
	else
	{
		p=top;
		cout<<"|";
		if(flag==0)
		{
		while(p!=NULL)
		{
			cout<<p->data<<"|";
			p=p->next;
		}
		}
		else
		{
		while(p!=NULL)
		{
			info=p->data;
			cout<<info<<" ";
			p=p->next;
		}
		}	
		cout<<"#|";
	}
	
}


