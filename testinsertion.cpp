/*************************************************************************
	> File Name: testinsertion.cpp
	> Author: lihy
	> Mail: lihaiyangcsu@gmail.com 
	> Created Time: Sat 27 Jun 2015 10:38:20 PM CST
 ************************************************************************/

#include<stdio.h>

int insertion( int arrary[], int size )
{
	for( int i = 0; i<size; i++ )
	{
		int tmp = arrary[i];
		for( int j = 0; j<i; j++ )
		{
			if( tmp < arrary[j] )
			{
				int k = i;
				//right shift
				while( k > j )
				{
					arrary[k] = arrary[k-1];
					--k;
				}
				//insert
				arrary[j] = tmp;
				break;
			}
		}	
	}

	return 0;
}


int main()
{
	int array[] = { 12,3,34,56,7,8,9,100 };
	(void)insertion( array, sizeof(array)/sizeof(int) );
	for( int i = 0; i<sizeof(array)/sizeof(int); i++ )
	{
		printf( "%d ", array[i] );
	}
	printf( "\n" );

	return 0;
}

