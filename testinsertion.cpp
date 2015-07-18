/*************************************************************************
	> File Name: testinsertion.cpp
	> Author: lihy
	> Mail: lihaiyangcsu@gmail.com 
	> Created Time: Sat 27 Jun 2015 10:38:20 PM CST
 ************************************************************************/

#include<stdio.h>

//non-stable
int nonstableinsertion( int array[], int size )
{
	for( int i = 0; i<size; i++ )
	{
		int key = *(array+i);
		for( int j = 0; j<i; j++ )
		{
			if( key < *(array+j) )
			{
				int k = i;
				//right shift
				//min k == j+1 
				while( k > j )
				{
					*(array+k) = *(array+k-1);
					--k;
				}
				//insert
				*(array+j) = key;
				break;
			}
		}	
	}

	return 0;
}


//stable
int stableinsertion( int array[], int size )
{
	for( int i = 1; i<size; i++ )
	{
		int key = *(array+i);
		int j = i-1;
		for( ; j>=0; j-- )
		{
			if( key < *(array+j) )
			{
				//right shift
				*(array+j+1) = *(array+j);
			} else {
				break;
			}
		}	
		if( j != i-1 )
			*(array+j+1) = key;
	}

	return 0;
}


int main()
{
	int array[] = { 12,3,34,56,7,8,9,100 };
//	(void)nonstableinsertion( array, sizeof(array)/sizeof(int) );
	(void)stableinsertion( array, sizeof(array)/sizeof(int) );
	for( int i = 0; i<sizeof(array)/sizeof(int); i++ )
	{
		printf( "%d ", *(array+i) );
	}
	printf( "\n" );

	return 0;
}

