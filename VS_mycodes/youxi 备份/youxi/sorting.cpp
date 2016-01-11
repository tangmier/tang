#include"stdafx.h"

struct List{
	int score;
	List*next;
};

void insert(List*&head,int num){
	List*s,*p,*q;
	s=new List;
	s->data=num;
	s->next=NULL;
	if(head==NUll){
	    head=s;
		return;
	}
	if(head->data>s->data){
	    s->next=head;
		head=s;
		return;
	}
	for(q=head,p=head->next;p;q=p,p=p->next){
	    if(p->data>s->data)
		{
			s->next=p;
			q->next=s;
			return;
		}
		q->next=s;
		return;
	}
}