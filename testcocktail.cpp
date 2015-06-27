/*************************************************************************
	> File Name: testcocktail.cpp
	> Author: lihy
	> Mail: lihaiyangcsu@gmail.com 
	> Created Time: Sat 27 Jun 2015 04:41:17 PM CST
 ************************************************************************/

#include<stdio.h>

int cocktail( int array[], int size )
{
	for( int i = 0; i<size-i; i++ )
	{
		int tmp = 0;
		if( array[i] < array[size-i-1] )
		{
			tmp = array[i];
			array[i] = array[size-i-1];
			array[size-i-1] = tmp;
		}
		for( int j = i+1; j<size-i; j++ )
		{
			if( array[j] > array[i] )
			{
				tmp = array[j];
				array[j] = array[i];
				array[i] = tmp;
			} else if( array[j] < array[size-i-1] ) {
				tmp = array[j];
				array[j] = array[size-i-1];
				array[size-i-1] = tmp;
			}
		}
	}
	return 0;
}


int main()
{
	int array[] = { 12,3,34,56,7,8,9,100 };
	(void)cocktail( array, sizeof(array)/sizeof(int) );
	for( int i = 0; i<sizeof(array)/sizeof(int); i++ )
	{
		printf( "%d ", array[i] );
	}
	printf( "\n" );

	return 0;
}

