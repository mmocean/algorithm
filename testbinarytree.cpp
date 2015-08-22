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

int visit( const struct TREE *root )
{
	printf( "%d ", root->val );
	#ifdef BALANCED_BINARY_TREE
//	printf( ".%d ", root->height );
	#endif

	return 0;
}


int preordertraversal( const struct TREE *root, int (*visit)(const struct TREE *) )
{
	if( NULL == root )
	{
		return -1;
	}
	printf("(");
	visit( root );
	preordertraversal( root->lchild, visit );
	preordertraversal( root->rchild, visit );
	printf(")");
	
	return 0;
}
 

int inordertraversal( const struct TREE *root, int (*visit)(const struct TREE *) )
{
	if( NULL == root )
	{
		return -1;
	}
	inordertraversal( root->lchild, visit );
	visit( root );
	inordertraversal( root->rchild, visit );
	
	return 0;
}


int postordertraversal( const struct TREE *root, int (*visit)(const struct TREE *) )
{
	if( NULL == root )
	{
		return -1;
	}
	postordertraversal( root->lchild, visit );
	postordertraversal( root->rchild, visit );
	visit( root );
	
	return 0;
}


//non-recursive
int nonpreordertraversal( const struct TREE *root, int (*visit)(const struct TREE *) )
{
	struct NODE* stack = NULL;
	while( NULL != root )
	{
		visit( root );
	
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
int noninordertraversal( const struct TREE *root, int (*visit)(const struct TREE *) )
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
		visit( root );
		root = root->rchild;	
	}

	return 0;
}


//non-recursive
int nonpostordertraversal( const struct TREE *root, int (*visit)(const struct TREE *) )
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
			visit( root );
			root = NULL;
		} else {
			if( 0 != push( &sc, (int)NULL ) )
				return -1;	
		}
	}


	return 0;
}


//levleltraversal
int levleltraversal( const struct TREE *root, int (*visit)(const struct TREE *) )
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
			visit( root );
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


int insertbinarysearchtree( struct TREE **root, int key )
{
	if( NULL == *root )
	{
		struct TREE* tmp = (struct TREE*)malloc(sizeof(struct TREE));
		if( NULL == tmp )
			exit(-1);
		tmp->val = key;
		tmp->lchild = NULL;
		tmp->rchild = NULL;
		*root = tmp;
	}else if( (*root)->val > key ){
		return insertbinarysearchtree( &(*root)->lchild, key );	
	}else if( (*root)->val < key ){
		return insertbinarysearchtree( &(*root)->rchild, key );	
	}
	return 0;
}


struct TREE * initbinarysearchtree( int array[], int size )
{
	struct TREE *root = NULL;
	for( int i = 0; i<size; i++ )
	{
		/*
		//one way to construct BST
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
		*/

		//another way to construct BST
		insertbinarysearchtree( &root, *(array+i) );	
	}
	return root;
}


#define MAX( a, b )\
({\
	typeof(a) _a = (a);\
	typeof(b) _b = (b);\
	void( &_a == &_b );\
	( _a >= _b )?_a:_b;\
 })


inline int height( const struct TREE *root )
{
	return (NULL==root)?(-1):(root->height);
}

/* LL
 *
 * insert C to B->lchild
 *
 *     A(2)
 *    / 
 *   B(1)   -->  B(1)
 *  /           / \	
 * C(0)     (0)C   A(0)
 *
 * */
void singlerotationwithleft( struct TREE **root )
{
	//rotation
	struct TREE *tl = (*root)->lchild;
	(*root)->lchild = (*root)->lchild->rchild;
	tl->rchild = *root;
	*root = tl;
	
	//re-calc height
	(*root)->rchild->height = MAX( height( (*root)->rchild->lchild ), height( (*root)->rchild->rchild ) ) + 1;
}


/* RR
 *
 * insert C to B->rchild
 *
 *     A(2)
 *      \ 
 *       B(1)   -->  B(1)
 *        \         / \	
 *         C(0) (0)A   C(0)
 *
 * */
void singlerotationwithright( struct TREE **root )
{
	//rotation
	struct TREE *tr = (*root)->rchild;
	(*root)->rchild = (*root)->rchild->lchild;
	tr->lchild = *root;
	*root = tr;
	
	//re-calc height
	(*root)->lchild->height = MAX( height( (*root)->lchild->lchild ), height( (*root)->lchild->rchild ) ) + 1;
}

/* LR
 *
 * insert C to B->rchild
 *
 *     A(2)
 *    / 
 *   B(1)   -->   C(1)
 *    \          / \	
 *     C(0)  (0)B   A(0)
 *
 * */
void doublerotationwithleft( struct TREE **root )
{
	//rotation
	singlerotationwithright( &(*root)->lchild );
	//re-calc height
	(*root)->lchild->height = MAX( height( (*root)->lchild->lchild ), height( (*root)->lchild->rchild ) ) + 1;
	
	singlerotationwithleft( root );	
}


/* RL
 *
 * insert C to B->lchild
 *
 *     A(2)
 *      \ 
 *       B(1)   -->   C(1)
 *      /            / \	
 *     C(0)      (0)A   B(0)
 *
 * */
void doublerotationwithright( struct TREE **root )
{
	//rotation
	singlerotationwithleft( &(*root)->rchild );	
	//re-calc height
	(*root)->rchild->height = MAX( height( (*root)->rchild->lchild ), height( (*root)->rchild->rchild ) ) + 1;
	
	singlerotationwithright( root );
}



int insertbalancedbinarytree( struct TREE **root, int key )
{
	if( NULL == *root )
	{
		struct TREE* tmp = (struct TREE*)malloc(sizeof(struct TREE));
		if( NULL == tmp )
			exit(-1);
		tmp->val = key;
		tmp->lchild = tmp->rchild = NULL;
		*root = tmp;
	}else if( (*root)->val > key ){
		insertbalancedbinarytree( &(*root)->lchild, key );	
		if( height( (*root)->lchild ) - height( (*root)->rchild ) == 2 )
		{
			if( (*root)->lchild->val > key )
			{
				singlerotationwithleft( root );
			} else {
				doublerotationwithleft( root );
			}
		}
	}else if( (*root)->val < key ){
		insertbalancedbinarytree( &(*root)->rchild, key );	
		if( height( (*root)->rchild ) - height( (*root)->lchild ) == 2 )
		{
			if( (*root)->rchild->val < key )
			{
				singlerotationwithright( root );
			} else {
				doublerotationwithright( root );
			}
		}
	}

	(*root)->height = MAX( height( (*root)->lchild ), height( (*root)->rchild ) ) + 1;

	return 0;
}


struct TREE * initbalancedbinarytree( int array[], int size )
{
	struct TREE *root = NULL;
	for( int i = 0; i<size; i++ )
	{
		insertbalancedbinarytree( &root, *(array+i) );	
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

	printf( "initbalancedbinarytree\n" );
	int array1[] = { 13,24,37,90,53 };
	struct TREE *bbt = initbalancedbinarytree( array1, sizeof(array1)/sizeof(int) );
	printf( "\n\n" );

	printf( "preordertraversal\n" );
	preordertraversal( bbt, visit );	
	printf( "\n\n" );

	printf( "inordertraversal\n" );
	inordertraversal( bbt, visit );
	printf( "\n\n" );
	
	printf( "clearbinarytree\n" );
	clearbinarytree( &bbt );
	printf( "\n\n" );

	return 0;
}

