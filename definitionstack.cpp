/*************************************************************************
	> File Name: definitionstack.cpp
	> Author: lihy
	> Mail: lihaiyangcsu@gmail.com 
	> Created Time: 2015-07-07 10:01:29
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include"definitionstack.h"

int push( struct NODE** head, int val )
{
	struct NODE* tmp = (struct NODE*)malloc(sizeof(struct NODE));
	if( NULL == tmp )
	{
		return -1;
	}
	tmp->val = val;
	tmp->next = (NULL==*head)?NULL:(*head);
	*head = tmp;

	return 0;
}


int pop( struct NODE** head, int *val )
{
	if( NULL == *head )
		return -1;
	struct NODE* tmp = (*head)->next;	
	*val = (*head)->val;
	free( (void*)*head );
	*head = tmp;

	return 0;
}


int gettop( struct NODE** head, int *val )
{
	if( NULL == *head )
		return -1;
	*val = (*head)->val;
	
	return 0;
}


int isempty( struct NODE** head )
{
	if( NULL != *head )
		return -1;
	return 0;
}

