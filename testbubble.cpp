/*************************************************************************
	> File Name: testbubble.cpp
	> Author: lihy
	> Mail: lihaiyangcsu@gmail.com 
	> Created Time: Sat 27 Jun 2015 09:39:24 PM CST
 ************************************************************************/

#include<stdio.h>

/*
 * bubble sort
 * after one inner loop, max is array[n] in [0...n], then continue to loop until n -> 0.
 * when array[j-1] == array[j], doesn't swap.
 */

int bubble( int array[], int size )
{
	int count = 0;
	for( int i = 0; i<size; i++ )
	{
		for( int j = 1; j<size-i; j++ )
		{
			if( *(array+j-1) > *(array+j) )
			{
				int tmp = *(array+j-1);
				*(array+j-1) = *(array+j);
				*(array+j) = tmp;
			}
			++count;
		}
	}
	return count;
}


int bubbleimprovement( int array[], int size )
{
	int count = 0;
	for( int i = 0; i<size; i++ )
	{
		int flag = 0;
		for( int j = 1; j<size-i; j++ )
		{
			if( *(array+j-1) > *(array+j) )
			{
				int tmp = *(array+j-1);
				*(array+j-1) = *(array+j);
				*(array+j) = tmp;
				flag = 1;
			}
			++count;
		}
		//already ordered
		if( 0 == flag )
			break;
	}
	return count;
}


int main()
{
	//int array[] = { 12,3,34,56,7,8,9,100 };
	int array[] = { 1,2,3,4,5,6,7,8 };
	
	int count = bubble( array, sizeof(array)/sizeof(int) );
	//int count = bubbleimprovement( array, sizeof(array)/sizeof(int) );
	printf( "count %d \n", count );
	
	for( int i = 0; i<sizeof(array)/sizeof(int); i++ )
	{
		printf( "%d ", *(array+i) );
	}
	printf( "\n" );

	return 0;
}

