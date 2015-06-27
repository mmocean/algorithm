/*************************************************************************
	> File Name: testbubble.cpp
	> Author: lihy
	> Mail: lihaiyangcsu@gmail.com 
	> Created Time: Sat 27 Jun 2015 09:39:24 PM CST
 ************************************************************************/

#include<stdio.h>

int bubble( int arrary[], int size )
{
	for( int i = 0; i<size; i++ )
	{
		for( int j = 1; j<size-i; j++ )
		{
			if( arrary[j-1] > arrary[j] )
			{
				int tmp = arrary[j-1];
				arrary[j-1] = arrary[j];
				arrary[j] = tmp;
			}
		}
	}
	return 0;
}


int main()
{
	int array[] = { 12,3,34,56,7,8,9,100 };
	(void)bubble( array, sizeof(array)/sizeof(int) );
	for( int i = 0; i<sizeof(array)/sizeof(int); i++ )
	{
		printf( "%d ", array[i] );
	}
	printf( "\n" );

	return 0;
}

