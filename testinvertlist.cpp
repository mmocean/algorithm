/*************************************************************************
	> File Name: testinvertlist.cpp
	> Author: lihy
	> Mail: lihaiyangcsu@gmail.com 
	> Created Time: Sun 28 Jun 2015 09:55:49 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>

//list definition
struct NODE {
	int val;
	struct NODE* next;
};


void freelist( const struct NODE* head )
{
	while( NULL != head )
	{
		struct NODE* tmp = head->next;
		free( (void*)head );
		head = tmp;
	}
}


void traversallist( const struct NODE* head )
{
	while( NULL != head )
	{
		printf( "%d ", head->val );
		head = head->next;
	}
	printf( "\n" );
}


NODE* createlist( int array[], int size )
{
	struct NODE* head = NULL;
	for( int i = 0; i<size; i++ )
	{
		struct NODE* tmp = (struct NODE*)malloc(sizeof(struct NODE));
		if( NULL == tmp )
		{
			freelist( head );
			return NULL;
		}
		tmp->val = array[i];
		tmp->next = NULL;

		if( NULL == head )
		{
			head = tmp;
		} else {
			struct NODE* tail = head;
			while( NULL != tail->next )
			{
				tail = tail->next;
			}
			tail->next = tmp;
		}
	}
	return head;
}


NODE* invertlist( struct NODE* head )
{
	struct NODE* newlist = NULL;
	while( NULL != head )
	{
		struct NODE* tmp = head->next;
		head->next = newlist;
		newlist = head;
		head = tmp;
	}
	return newlist;
}


NODE* insertionsortlist( struct NODE* head )
{
	struct NODE* newlist = head;
	struct NODE* pre = NULL;
	while( NULL != head )
	{
		struct NODE* tmp = newlist;
		struct NODE* subspre = NULL;
		while( NULL != tmp && tmp != head && head->val > tmp->val )
		{
			subspre = tmp;
			tmp = tmp->next;
		}
		if( tmp != head )
		{
			pre->next = head->next;
			if( NULL == subspre )
			{
				head->next = newlist;
				newlist = head;
			} else {
				head->next = tmp;
				subspre->next = head;
			}
		}
		pre = head;
		head = head->next;
	}
	return newlist;
}


NODE* mergelist( struct NODE* list1, struct NODE* list2 )
{
	struct NODE* newlist = NULL;
	struct NODE* rear = NULL;
	while( NULL != list1 && NULL != list2 )
	{
		struct NODE* tmp = NULL;
		if( list1->val < list2->val )
		{
			tmp = list1;
			list1 = list1->next;
		} else {
			tmp = list2;
			list2 = list2->next;
		}

		if( NULL == newlist )
		{
			newlist = tmp;
			rear = tmp;
		} else {
			rear->next = tmp;
			rear = rear->next;
		}
	}
	if( NULL != rear )
		rear->next = (NULL==list1)?list2:list1;
	
	return newlist;
}


int main()
{
	int array[] = { 2,6,4,10,8 };
	
	struct NODE* list1 = createlist( array, sizeof(array)/sizeof(int) );
	traversallist( list1 );

//	head = invertlist( list1 );
//	traversallist( list1 );

	list1 = insertionsortlist( list1 );
	traversallist( list1 );

	int array2[] = { 7,5,1 };
	
	struct NODE* list2 = createlist( array2, sizeof(array2)/sizeof(int) );
	traversallist( list2 );

	list2 = insertionsortlist( list2 );
	traversallist( list2 );

	struct NODE* newlist = mergelist( list1, list2 );
	traversallist( newlist );

	freelist( newlist );

	return 0;
}


