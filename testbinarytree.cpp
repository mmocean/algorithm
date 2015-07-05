/*************************************************************************
	> File Name: testbinarytree.cpp
	> Author: lihy
	> Mail: lihaiyangcsu@gmail.com 
	> Created Time: 2015-07-04 15:56:27
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>

//tree definition
struct TREE{
	int val;
	struct TREE *lchild, *rchild;
};


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


int visit( int val )
{
	printf( "%d ", val );
	return 0;
}


int  preordertraversal( const struct TREE *root, int (*visit)(int) )
{
	if( NULL == root )
	{
		return -1;
	}
	printf("(");
	visit( root->val );
	preordertraversal( root->lchild, visit );
	preordertraversal( root->rchild, visit );
	printf(")");
	
	return 0;
}
 

int  inordertraversal( const struct TREE *root, int (*visit)(int) )
{
	if( NULL == root )
	{
		return -1;
	}
	inordertraversal( root->lchild, visit );
	visit( root->val );
	inordertraversal( root->rchild, visit );
	
	return 0;
}


int postordertraversal( const struct TREE *root, int (*visit)(int) )
{
	if( NULL == root )
	{
		return -1;
	}
	postordertraversal( root->lchild, visit );
	postordertraversal( root->rchild, visit );
	visit( root->val );
	
	return 0;
}


int invertbinarytree( struct TREE *root )
{
	if( NULL == root || (NULL == root->lchild && NULL == root->rchild) )
	{
		return -1;
	}
	struct TREE *tmp = root->lchild;
	root->lchild = root->rchild;
	root->rchild = tmp;
	invertbinarytree( root->lchild );
	invertbinarytree( root->rchild );
	return 0;
}


int main()
{
	int array[] = { 1,2,3,-1,-1,4,5,-1,7,-1,-1,6,-1,-1,-1 };
	
	struct TREE *root = NULL;

	initbinarytree( &root, array, sizeof(array)/sizeof(int) );

	preordertraversal( root, visit );	
	printf( "\n" );

	inordertraversal( root, visit );
	printf( "\n" );
	
	postordertraversal( root, visit );
	printf( "\n" );

	invertbinarytree( root );

	preordertraversal( root, visit );	
	printf( "\n" );

	clearbinarytree( &root );
	
	return 0;
}

