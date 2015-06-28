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


int main()
{
	int array[] = { 12,3,34,56,7,8,9,100 };
	
	struct NODE* head = createlist( array, sizeof(array)/sizeof(int) );
	traversallist( head );

	head = invertlist( head );
	traversallist( head );

	freelist( head );

	return 0;
}


