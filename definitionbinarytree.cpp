/*************************************************************************
	> File Name: definitionbinarytree.cpp
	> Author: lihy
	> Mail: lihaiyangcsu@gmail.com 
	> Created Time: 2015-07-07 15:02:19
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include"definitionbinarytree.h"

int initbinarytree( struct TREE **root, int array[], int size )
{
	static int i = 0;
	if( i < size )
	{
		int val = *(array+(i++));
		if( -1 == val )
		{
			root = NULL;	
		} else {
			struct TREE* tmp = (struct TREE*)malloc(sizeof(struct TREE));
			if( NULL == tmp )
			{
				exit(-1);
			}
			tmp->val = val;
			tmp->lchild = NULL;
			tmp->rchild = NULL;
			*root = tmp;
			initbinarytree( &(*root)->lchild, array, size );
			initbinarytree( &(*root)->rchild, array, size );
		}
	}
	return 0;
}


int clearbinarytree( struct TREE **root )
{
	if( NULL == *root )
		return -1;
	clearbinarytree( &(*root)->lchild );
	clearbinarytree( &(*root)->rchild );
	free( (void*)*root );
	*root = NULL;//necessary

	return 0;
}


