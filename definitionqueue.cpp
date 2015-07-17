/*************************************************************************
	> File Name: definitionqueue.cpp
	> Author: lihy
	> Mail: lihaiyangcsu@gmail.com 
	> Created Time: 2015-07-17 10:28:32
 ************************************************************************/

#include"definitionqueue.h"
#include<stdio.h>
#include<stdlib.h>

int enqueue( struct Queue *q, int val )
{
	if( NULL == q )
		return -1;

	struct NODE* tmp = (struct NODE*)malloc( sizeof(struct NODE) );
	if( NULL == tmp )
		return -1;

	tmp->next = NULL;
	tmp->val = val;

	if( NULL == q->rear )
	{	
		q->front = q->rear = tmp;	
	} else {
		q->rear->next = tmp;
		q->rear = tmp;
	}

	return 0;
}


int dequeue( struct Queue *q, int *val )
{
	if( NULL == q || NULL == q->front )
		return -1;	

	if( q->front == q->rear )
	{
		*val = q->front->val;
		free( (void*)q->front );
		q->front = q->rear = NULL;
	} else {
		*val = q->front->val;
		struct NODE* tmp = q->front->next;
		free( (void*)q->front );
		q->front = tmp;	
	}

	return 0;
}


int isempty( struct Queue *q )
{
	if( NULL == q )
		return -1;
	if( NULL == q->front && NULL == q->rear )
		return 0;
	return -1;
}


