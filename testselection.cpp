/*************************************************************************
	> File Name: testselection.cpp
	> Author: lihy
	> Mail: lihaiyangcsu@gmail.com 
	> Created Time: Sat 27 Jun 2015 08:38:49 PM CST
 ************************************************************************/

#include<stdio.h>

int selection_wrong( int array[], int size )
{
	for( int i = 0; i<size; i++ )
	{
		for( int j = i+1; j<size; j++ )
		{
			if( array[i] < array[j] )
			{
				int tmp = array[i];
				array[i] = array[j];
				array[j] = tmp;
			}
		}
	}
	return 0;
}


int selection( int array[], int size )
{
	for( int i = 0; i<size; i++ )
	{
		int index = i;
		for( int j = i+1; j<size; j++ )
		{
			if( array[index] < array[j] )
			{
				index = j;	
			}
		}
		if( i != index )
		{
			int tmp = array[i];
			array[i] = array[index];
			array[index] = tmp;
		}
	}
	return 0;
}


int main()
{	
	int array[] = { 2,3,34,56,7,8,9,100 };
	(void)selection( array, sizeof(array)/sizeof(int) );
	for( int i = 0; i<sizeof(array)/sizeof(int); i++ )
	{
		printf( "%d ", array[i] );
	}
	printf( "\n" );

	return 0;
}

