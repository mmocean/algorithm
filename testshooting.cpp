/*************************************************************************
	> File Name: testshooting.cpp
	> Author: lihy
	> Mail: lihaiyangcsu@gmail.com 
	> Created Time: 2015-07-17 14:53:10
 ************************************************************************/

#include<stdio.h>


int shooting( int sum, int n, int array[], int size )
{
	if( sum < 0 || n <= 0 || 10*n < sum )
		return -1;

	for( int i = 10; i >= 0; i-- )
	{
		//output
		*(array+n-1) = i;
		if( sum == i && 1 == n )
		{
			for( int j = size-1; j >= 0; j-- )
			{
				printf( "%d ", *(array+j) );
			}
			printf( "\n" );
		}
		//continue
		shooting( sum-i, n-1, array, size );
	}

	return 0;
}


int main()
{
	int array[3];
	(void)shooting( 12, 3, array, sizeof(array)/sizeof(int) );
	printf( "\n" );

	return 0;
}

