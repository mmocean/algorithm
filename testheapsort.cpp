/*************************************************************************
	> File Name: testheapsort.cpp
	> Author: lihy
	> Mail: lihaiyangcsu@gmail.com 
	> Created Time: 2015-07-15 17:13:09
 ************************************************************************/

#include<stdio.h>

//min-heap
int heapadjust( int a[], int size, int n )
{
	int min = *(a+n);
	int next = 0;
	//lchild
	int lchild = (1+(n<<1));
	if( lchild <= size && *(a+lchild) < min )
	{
		min = *(a+lchild);
		next = lchild;
	}
	int rchild = (2+(n<<1));
	if( rchild <= size && *(a+rchild) < min )
	{
		min = *(a+rchild);
		next = rchild;
	}
	if( *(a+n) != min )
	{
		*(a+next) = *(a+n);
		*(a+n) = min;
		heapadjust( a, size, next );
	}

	return 0;
}


int heapsort( int array[], int size )
{
	//build-min-heap
	for( int i = (size-1)>>1; i >= 0; i-- )
	{
		(void)heapadjust( array, size-1, i );
	}
	
	for( int i = size-1; i > 0; i-- )
	{
		int tmp = *(array+i);
		*(array+i) = *array;
		*array = tmp;
		(void)heapadjust( array, i-1, 0 );	
	}	
	return 0;
}


int topK( int array[], int size, int k )
{
	for( int i = (k-1)>>1; i >= 0; i-- )
	{
		(void)heapadjust( array, k-1, i );
	}

	for( int i = k; i < size; i++ )
	{
		if( *(array+i) > *array )
		{
			*array = *(array+i);
			(void)heapadjust( array, k-1, 0 );	
		}
	}

	for( int i = 0; i < k; i++ )
	{
		printf( "%d ", *(array+i) );
	}
	printf( "\n" );
}


int main()
{
	int array[] = { 49,38,65,97,76,13,27,49,12,3,63,636,72,872,929,37,3 };
//	(void)heapsort( array, sizeof(array)/sizeof(int) );
	for( int i = 0; i<sizeof(array)/sizeof(int); i++ )
	{
		printf( "%d ", *(array+i) );
	}
	printf( "\n" );

	(void)topK( array, sizeof(array)/sizeof(int), 3 );

	return 0;
}

