/*************************************************************************
	> File Name: testselection.cpp
	> Author: lihy
	> Mail: lihaiyangcsu@gmail.com 
	> Created Time: Sat 27 Jun 2015 08:38:49 PM CST
 ************************************************************************/

#include<stdio.h>

int selection( int array[], int size )
{
	for( int i = 0; i<size; i++ )
	{
		int index = i;
		for( int j = i+1; j<size; j++ )
		{
			if( *(array+index) < *(array+j) )
			{
				index = j;	
			}
		}
		if( i != index )
		{
			int tmp = *(array+i);
			*(array+i) = *(array+index);
			*(array+index) = tmp;
		}
	}
	return 0;
}


int duplexselection( int array[], int size )
{
	for( int i = 0; i<size-i; i++ )
	{
		int minindex = i;
		int maxindex = size-i-1;

		if( *(array+minindex) > *(array+maxindex) )
		{
			int tmp = *(array+minindex);
			*(array+minindex) = *(array+maxindex);
			*(array+maxindex) = tmp;
		}

		for( int j = i+1; j<size-i; j++ )
		{
			if( *(array+j) < *(array+minindex) )
			{
				minindex = j;
			} else if ( *(array+j) > *(array+maxindex) ) {
				maxindex = j;
			}
		}
		
		if( i != minindex )
		{
			int tmp = *(array+minindex);
			*(array+minindex) = *(array+i);
			*(array+i) = tmp;	
		}
		if( size-i-1 != maxindex )
		{
			int tmp = *(array+maxindex);
			*(array+maxindex) = *(array+size-i-1);
			*(array+size-i-1) = tmp;	
		}
	}
	return 0;
}


int main()
{	
	int array[] = { 2,3,34,56,7,8,9,100 };
	//(void)selection( array, sizeof(array)/sizeof(int) );
	(void)duplexselection( array, sizeof(array)/sizeof(int) );
	for( int i = 0; i<sizeof(array)/sizeof(int); i++ )
	{
		printf( "%d ", *(array+i) );
	}
	printf( "\n" );

	return 0;
}

