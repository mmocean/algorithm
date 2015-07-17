/*************************************************************************
	> File Name: definitionqueue.h
	> Author: lihy
	> Mail: lihaiyangcsu@gmail.com 
	> Created Time: 2015-07-17 10:23:49
 ************************************************************************/

#ifndef _DEFINITION_QUEUE_H
#define _DEFINITION_QUEUE_H

#include"definitionlist.h"

//queue definition
struct Queue
{
	NODE *front;
	NODE *rear;
};

int enqueue( struct Queue *q, int val );

int dequeue( struct Queue *q, int *val );

int isempty( struct Queue *q );

#endif

