/*************************************************************************
	> File Name: testbinarytree.cpp
	> Author: lihy
	> Mail: lihaiyangcsu@gmail.com 
	> Created Time: 2015-07-04 15:56:27
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include"definitionstack.h"
#include"definitionbinarytree.h"
#include"definitionqueue.h"

int visit( int val )
{
	printf( "%d ", val );
	return 0;
}


int preordertraversal( const struct TREE *root, int (*visit)(int) )
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
 

int inordertraversal( const struct TREE *root, int (*visit)(int) )
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


//non-recursive
int nonpreordertraversal( const struct TREE *root, int (*visit)(int) )
{
	struct NODE* stack = NULL;
	while( NULL != root )
	{
		visit( root->val );
	
		if( NULL != root->rchild && 0 != push( &stack, (int)root->rchild ) )
			return -1;

		if( NULL == root->lchild )
		{
			if( 0 != pop( &stack, (int*)&root ) )
				return -1;
		} else {
			root = root->lchild;
		}
	}

	return 0;
}


//non-recursive
int noninordertraversal( const struct TREE *root, int (*visit)(int) )
{
	struct NODE* stack = NULL;
	while( NULL != root || 0 != isempty( &stack ) )
	{
		while( NULL != root )		
		{
			if( 0 != push( &stack, (int)root ) )
				return -1;
			root = root->lchild;	
		}
		if( 0 != pop( &stack, (int*)&root ) )
			return -1;
		visit( root->val );
		root = root->rchild;	
	}

	return 0;
}


//non-recursive
int nonpostordertraversal( const struct TREE *root, int (*visit)(int) )
{
	struct NODE* sr = NULL;//root
	struct NODE* sc = NULL;//rchild
	
	while( NULL != root || 0 != isempty( &sc ) )
	{
		while( NULL != root )
		{
			if( 0 != push( &sr, (int)root ) )
				return -1;
			if( 0 != push( &sc, (int)root->rchild ) )
				return -1;
			root = root->lchild;	
		}
		if( 0 != pop( &sc, (int*)&root ) )
			return -1;
		if( NULL == root )
		{
			if( 0 != pop( &sr, (int*)&root ) )
				return -1;	
			visit( root->val );
			root = NULL;
		} else {
			if( 0 != push( &sc, (int)NULL ) )
				return -1;	
		}
	}


	return 0;
}


//levleltraversal
int levleltraversal( const struct TREE *root, int (*visit)(int) )
{
	if( NULL == root )
		return -1;

	struct Queue q;
	q.front = q.rear = NULL;
	
	if( 0 != enqueue( &q, (int)root ) )
		return -1;

	int leafcount = 0, nodecount = 0;

	while( 0 != isempty( &q ) )
	{
		if( 0 != dequeue( &q, (int*)&root ) )
			return -1;
		if( NULL != root )	
		{
			if( NULL != root->lchild || NULL !=root->rchild )
			{
				if( 0 != enqueue( &q, (int)root->lchild ) )
					return -1;
				if( 0 != enqueue( &q, (int)root->rchild ) )
					return -1;
			}
			visit( root->val );
			++nodecount;
		} else {
			++leafcount;
		}
		if( (leafcount+nodecount)%2 == 1 )
			printf( "\n" );	
	}
	
	printf( "leafcount(NULL) %d nodecount %d\n", leafcount, nodecount );	

	return 0;
}


int depthtree( const struct TREE *root )
{
	if( NULL == root )
	{
		return 0;
	}
	int ld = depthtree( root->lchild );
	int rd = depthtree( root->rchild );	
	
	return ( ld >= rd )?( ld+1 ):( rd+1 );
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


struct TREE * searchbinarysearchtree( struct TREE *root, int key )
{
	if( NULL != root )
	{
		if( key < root->val )
		{
			if( NULL != root->lchild )
				return searchbinarysearchtree( root->lchild, key );
		} else if (key > root->val) {
			if( NULL != root->rchild )
				return searchbinarysearchtree( root->rchild, key );
		}
	}
	return root;
}


struct TREE * initbinarysearchtree( int array[], int size )
{
	struct TREE *root = NULL;
	for( int i = 0; i<size; i++ )
	{
		struct TREE* tmp = (struct TREE*)malloc(sizeof(struct TREE));
		if( NULL == tmp )
			exit(-1);
		tmp->val = *(array+i);
		tmp->lchild = NULL;
		tmp->rchild = NULL;
		struct TREE * node = searchbinarysearchtree( root, *(array+i) );
		if( NULL == node )
		{
			root = tmp;	
		} else {
			if( *(array+i) == node->val )
			{
				free((void*)tmp);
			} else if( *(array+i) < node->val ) {
				node->lchild = tmp;
			} else {
				node->rchild = tmp;
			}
		}
	}
	return root;
}


int main()
{
	int array[] = { 1,2,3,-1,-1,4,5,-1,7,-1,-1,6,-1,-1,-1 };
	
	struct TREE *root = NULL;

	printf( "initbinarytree\n" );
	initbinarytree( &root, array, sizeof(array)/sizeof(int) );
	printf( "\n\n" );

	printf( "preordertraversal\n" );
	preordertraversal( root, visit );	
	printf( "\n\n" );

	printf( "inordertraversal\n" );
	inordertraversal( root, visit );
	printf( "\n\n" );
	
	printf( "postordertraversal\n" );
	postordertraversal( root, visit );
	printf( "\n\n" );

	printf( "invertbinarytree\n" );
//	invertbinarytree( root );
	printf( "\n\n" );

	printf( "preordertraversal\n" );
	preordertraversal( root, visit );	
	printf( "\n\n" );
	
	printf( "nonpreordertraversal\n" );
	nonpreordertraversal( root, visit );	
	printf( "\n\n" );
	
	printf( "noninordertraversal\n" );
	noninordertraversal( root, visit );	
	printf( "\n\n" );
	
	printf( "nonpostordertraversal\n" );
	nonpostordertraversal( root, visit );	
	printf( "\n\n" );

	printf( "levleltraversal\n" );
	levleltraversal( root, visit );
	printf( "\n\n" );

	printf( "depthtree\n" );
	int depth = depthtree( root );
	printf( "depth:%d\n\n", depth );
	
	printf( "clearbinarytree\n" );
	clearbinarytree( &root );
	printf( "\n\n" );

	printf( "initbinarysearchtree\n" );
	struct TREE *bst = initbinarysearchtree( array, sizeof(array)/sizeof(int) );
	printf( "\n\n" );

	printf( "inordertraversal\n" );
	inordertraversal( bst, visit );
	printf( "\n\n" );
	
	printf( "clearbinarytree\n" );
	clearbinarytree( &bst );
	printf( "\n\n" );

	return 0;
}

