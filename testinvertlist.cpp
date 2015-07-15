/*************************************************************************
	> File Name: testinvertlist.cpp
	> Author: lihy
	> Mail: lihaiyangcsu@gmail.com 
	> Created Time: Sun 28 Jun 2015 09:55:49 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include"definitionlist.h"


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
			head = pre->next;
		} else {
			pre = head;
			head = head->next;
		}
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


//判读链表是否有环
int cyclejudgement( const struct NODE* head, struct NODE** node )
{
	*node = NULL;
	if( NULL != head && head == head->next )
	{
		*node = (struct NODE*)head;
		return 0;
	}

	const struct NODE* pre = head;
	const struct NODE* rear = head;
	
	while( NULL != pre && NULL != pre->next )
	{
		pre = pre->next->next;
		rear = rear->next;
		printf( "pre %d rear %d\n", pre->val, rear->val );	
		if( pre == rear )
		{
			pre = head;
			while( pre != rear )
			{
				pre = pre->next;
				rear = rear->next;
			}
			*node = (struct NODE*) pre;
			return 0;
		}
	}

	return -1;
}


//返回链表倒数第K个节点
const NODE* lastKnode( struct NODE* head , int k )
{
	if( k <= 0 ) 
	{
		return NULL;
	} else { //k >= 1
		const struct NODE* rear = head;
		while( NULL != head && (k--) > 0 )	
		{
			head = head->next;
		}
		if( k > 0 )
		{
			return NULL;
		}
		while( NULL != head )
		{
			head = head->next;
			rear = rear->next;	
		}
		return rear;
	}
	return NULL;
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

	int array2[] = { 9,7,5,3,1 };
	
	struct NODE* list2 = createlist( array2, sizeof(array2)/sizeof(int) );
	traversallist( list2 );

	list2 = insertionsortlist( list2 );
	traversallist( list2 );

	struct NODE* newlist = mergelist( list1, list2 );
	traversallist( newlist );

	for( int k = -1; k<11; k++ )
	{
		const struct NODE* tmp = lastKnode( newlist, k );
		if( NULL != tmp )
			printf( "val:%d K:%d\n", tmp->val, k );
		else 
			printf( "NULL k:%d\n", k );
	}


	struct NODE* last = (struct NODE*)lastKnode( newlist, 1 );
	if( NULL != last )
	{
		printf( "last val %d\n", last->val );	
		
		struct NODE* tmp = (struct NODE*)lastKnode( newlist, 3 );
		printf( "tmp val %d\n", tmp->val );	

		last->next = tmp;
		
		struct NODE* node = NULL;
		if( 0 == cyclejudgement( newlist, &node ) )
		{
			printf( "node val %d\n", node->val );	
		}

		last->next = NULL;
	}

	freelist( newlist );

	return 0;
}


