#ifndef _MYLIST_H
#define _MYLIST_H
typedef struct node{
	void *data;
	struct node *next;
	struct node *prev;
}Node;

typedef struct list{
	Node *first;
	Node *last;
	int count;
}List;
/**
 *@brief create a list 
 *
 *@param 
 * 
 *@return List*
 */
List * CreateList();
/**
 @brief free a list
 *
 *@param h
 *
 *@return 
 */
void ListFree(List *h);
/**
 *@brief list length
 *
 *@param h
 *
 *@return list length
 */
int ListLength(List *h);
/**
 *@brief judge a list is empty
 *
 *@param h
 * 
 *@return 1:is empty
          0:is not empty
 */
int ListIsEmpty(List *h);
/**
 *@brief remove a list's tail
 *
 *@param h
 * 
 *@return tail's data
 */
void *ListRemoveTail(List *h);
/**
 *@brief remove a list's head 
 *
 *@param 
 * 
 *@return head's data
 */
void *ListRemoveHead(List *h);
/**
 *@brief remove a list's node by index 
 *
 *@param h
 *@param index
 * 
 *@return the index node of data
 */
void *ListRemove(List *h,int index);
/**
 *@brief insert a node at tail
 *
 *@param h
 *@param data
 *
 *@return 0: insert sussesful
         -1:insert failed
 */      
int ListInsertTail(List *h,void *data);
/**
 *@brief insert a node at head
 *
 *@param h
 *@param data
 *
 *@return 0:insert sussesful
        -1:insert failed
 */
int ListInsertHead(List *h,void *data);
/**
 *@brief insert a node at index
 *
 *@param h
 *@param index
 *
 *@return 0:insert sussesful
        -1:insert failed
	 1:index is not legal
 */
int ListInsert(List *h,int dex,void * data);
/**
 *@brief find a node by data and findfuction
 *
 *@param h
 *@param data
 *@param (*findfuction)
 *
 *@return node
 */
Node * ListFind(List *h,void* data,int(*findfuction)(void *,void *));
/**
 *@brief get a next node
 *
 *@param a
 *
 *@return node
 */
Node *GetNextNode(Node *a);
/**
 *@brief get a prev node
 *
 *@param a
 *
 *@return node
 */
Node *GetPrevNode(Node *a);
/**
 *@brief find a node by index
 *
 *@param h
 *@param index
 *
 *@return nnode
 */
Node *GetNode(List *h,int index);
/**
 *@brief swap node
 *
 *@param a
 *@param b
 *
 *@return 
 */
void Swap(Node *a,Node *b);
/**
 *@brief get a separator by cmp serve quicksort
 *
 *@param begin
 *@param end
 *@param (*cmp)
 *
 *@return node
 */
Node *GetSeparator(Node *begin,Node *end,int(*cmp)(void *,void*));
/**
 *@brief serve listsort
 *
 *@param begin
 *@param end
 *@param (*cmp)
 *
 *@return node
 */
void QuickSort(Node *begin,Node *end,int(*cmp)(void *,void *));
/**
 *@brief quicksort a list by cmp
 *
 *@param h
 *@param (*cmp)
 *
 *@return 
 */
void ListSort(List *h,int(*cmp)(void *,void *));
/**
 *@brief output a list
 *
 *@param h
 *@param (*pt)
 *
 *@return 
 */
void ListOutput(List *h,void(*pt)(void *));
/**
 *@brief invert output list
 *
 *@param h
 *@param (*pt)
 *
 *@return
 */
void ListInvertOutput(List *h,void(*pt)(void*));
/**
 *@brief reverse a list
 *
 *@param h
 *
 *@return 
 */
void ListReverse(List *h);

Node *GetNodetwo(List *h,int cur,int i);

Node *ListFindtwo(List *h,void *data,int(*findfunction)(void *,void *));

List *ListMerge(List *h1,List *h2);

#endif

