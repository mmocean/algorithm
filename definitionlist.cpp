/*************************************************************************
	> File Name: definitionlist.cpp
	> Author: lihy
	> Mail: lihaiyangcsu@gmail.com 
	> Created Time: 2015-07-07 14:49:49
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include"definitionlist.h"

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
		tmp->val = *(array+i);
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

