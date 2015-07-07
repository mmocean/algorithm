/*************************************************************************
	> File Name: definitionlist.h
	> Author: lihy
	> Mail: lihaiyangcsu@gmail.com 
	> Created Time: 2015-07-07 14:47:07
 ************************************************************************/

#ifndef _DEFINITION_LIST_H
#define _DEFINITION_LIST_H

//list definition
struct NODE {
	int val;
	struct NODE* next;
};

NODE* createlist( int array[], int size );

void freelist( const struct NODE* head );

void traversallist( const struct NODE* head );

#endif

