/*************************************************************************
	> File Name: definitionstack.h
	> Author: lihy
	> Mail: lihaiyangcsu@gmail.com 
	> Created Time: 2015-07-07 09:46:09
 ************************************************************************/

#ifndef _DEFINITION_SATCK_H
#define _DEFINITION_SATCK_H

#include"definitionlist.h"

int push( struct NODE** head, int val );

int pop( struct NODE** head, int *val );

int gettop( struct NODE** head, int *val );

int isempty( struct NODE** head );

#endif

