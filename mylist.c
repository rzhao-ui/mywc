#include"mylist.h"
#include<stdio.h>
#include<stdlib.h>

List *CreateList()
{
	List *list = (List*)malloc(sizeof(List));
	if(list == NULL)
		return NULL;
	list->count = 0;
	list->first = NULL;
	list->last = NULL;
	return list;
}
void ListFree(List *h)
{
	Node *p;
	while(h->first != NULL)
	{
		p = h->first->next;
		free(h->first->data);
		free(h->first);
		h->first = p;
	}
	free(h);
}

int ListIsEmpty(List *h)
{
	return ((h->first == NULL) && (h->last == NULL));
}

int ListLength(List *h)
{
	return h->count;
}

void* ListRemoveTail(List *h)
{
	if(h->count == 1)
		return ListRemoveHead(h);
	Node *p = h->first;
	while(p->next != h->last)
	{
		p = p->next;
	}
	void *result = h->last->data;
	free(h->last);
	p->next = NULL;
	h->last = p;
	(h->count)--;
	return result;
}

void* ListRemoveHead(List *h)
{
	Node *p = h->first;
	h->first = p->next;
	void *result = p->data;
	free(p);
	(h->count)--;
	if(h->count == 0)
		h->last = NULL;
	return result;
}

void *ListRemove(List *h,int index)
{
	if(index == 0)
		return ListRemoveHead(h);
	if(index == h->count-1)
		return ListRemoveTail(h);
	Node *p = h->first;
	for(int i = 0;i < index-1;i++)
		p = p->next;
	Node *q = p->next;
	void *result = q->data;
	q->next->prev = p;
	p->next = q->next;
	free(q);
	(h->count)--;
	return result;
}

int ListInsertTail(List *h,void *data)
{
	Node *p;
	p = (Node *)malloc(sizeof(Node));
	if(p == NULL)
		return -1;
	p->data = data;
	p->next = NULL;
	if(h->count)
	{
		h->last->next = p;
		p->prev = h->last;
		h->last = p;
	}
	else
	{
		h->first = p;
		h->last = p;
	}
	(h->count)++;
	return 0;
}

int ListInsertHead(List *h,void *data)
{
	Node *p;
	p = (Node *)malloc(sizeof(Node));
	if(p == NULL)
		return -1;
	p->data = data;
	p->next = NULL;
	if(h->count)
	{
		p->next = h->first;
		h->first->prev = p;
		h->first = p;
	}
	else
	{
		h->first = p;
		h->last = p;
	}
	(h->count)++;
	return 0;
}

int ListInsert(List *h,int index,void *data)
{
	if(index == 0)
		ListInsertHead(h,data);
	else if(index == h->count)
		ListInsertTail(h,data);
	else if(index>0&&index<h->count)
	{
		Node *p = (Node *)malloc(sizeof(Node));
		if(p == NULL)
			return -1;
		p->data = data;
		Node *t = h->first;
		for(int i = 0;i < index-1;i++)
		{
			t = t->next;
		}
         	p->next = t->next;
        	p->prev = t;
	        t->next->prev = p;
        	t->next = p;
        	(h->count)++;
        }
	else
		return 1;

	return 0;
}

Node *ListFind(List *h,void *data,int(*findfunction)(void *,void *))
{
	Node *p = h->first;
	while(p != NULL)
	{
		if(findfunction(p->data,data)) 
			return p;
		p = p->next;
	}
	return NULL;
}

Node *GetNextNode(Node *a)
{
	if(a == NULL)
		return NULL;
	return a->next;
}

Node *GetPrevNode(Node *a)
{
	if(a == NULL)
		return NULL;
	return a->prev;
}

Node *GetNode(List *h,int index)
{
	if(index == 0)
		return h->first;
	else if(index == h->count-1)
		return h->last;
	else if(index > 0 && index < h->count-1)
	{
		Node *p = h->first;
		for(int i = 0;i<index;i++)
			p = p->next;
		return p;
	}
	else
		return NULL;
}

void Swap(Node *a,Node *b)
{
	void *data;
	data = a->data;
	a->data = b->data;
	b->data = data;
}

Node* GetSeparator(Node *begin,Node *end,int (*cmp)(void *,void*))
{
	Node *p = begin;
	Node *q = begin->next;
	void *data = p->data;
	while(q !=  end)
	{
		if(cmp(q->data,data))
		{
			p = p->next;
			Swap(p,q);
		}
		q = q->next;
	}
	Swap(begin,p);
	return p;
}

void QuickSort(Node *begin,Node *end,int(*cmp)(void *,void *))
{
        if(begin != end)
        {
		Node* separator = GetSeparator(begin,end,(*cmp));		
        QuickSort(begin,separator,(*cmp));
		QuickSort(separator->next,end,(*cmp));
	}
}

void ListSort(List *h,int(*cmp)(void *,void *))
{
	QuickSort(h->first,NULL,(*cmp));
}

void ListOutput(List *h,void(*pt)(void *))
{
	Node *p = h->first;
	while(p != NULL)
	{
		(*pt)(p->data);
		p = p->next;
	}
	
}

void ListInvertOutput(List *h,void(*pt)(void *))
{
	Node *p =h->last;
	while(p != NULL)
		{
			(*pt)(p->data);
			p=p->prev;
		}
}

void ListReverse(List *h)
{ 
	if(h == NULL)
		return ;
	Node *p = h->last;
	Node *temp = p->next;
	h->last = h->first;
	h->first = p;
	while(p)
		{
			temp = p->next;
			p->next = p->prev;
			p->prev = temp;
			p = p->next;
		}
}

Node *GetNodetwo(List *h,int cur,int i)
{
	Node *p = h->first;
	while(p)
		{
			if(i == (++cur))
				return p;
			p = p->next;
		}
	return NULL;
}

Node *ListFindtwo(List *h,void *data,int(*findfunction2)(void *,void *))
{
	Node *p ;
	int left = 0,right = h->count-1;
	while(left <= right)
		{
			int mid = (left + right) /2;
		//	printf("%d %d %d\n",left,mid,right);
			p = GetNode(h,mid);
			if(findfunction2(p->data,data)>0)
				right = mid - 1;
			else if(findfunction2(p->data,data)<0)
				left = mid + 1;
			else 
				return p;
		}
	return NULL;
}

List *ListMerge(List *h1,List *h2)
{
	h1->last->next = h2->first;
//	h2->first->prev = h1->:
    return h1;
}
