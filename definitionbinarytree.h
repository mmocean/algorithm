/*************************************************************************
	> File Name: definitionbinarytree.h
	> Author: lihy
	> Mail: lihaiyangcsu@gmail.com 
	> Created Time: 2015-07-07 14:54:38
 ************************************************************************/

#ifndef _DEFINITION_BINARYTREE_H
#define _DEFINITION_BINARYTREE_H

//tree definition
struct TREE{
	int val;
	struct TREE *lchild, *rchild;
};

int initbinarytree( struct TREE **root, int array[], int size );

int clearbinarytree( struct TREE **root );

#endif

