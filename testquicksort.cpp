/*************************************************************************
	> File Name: testquicksort.cpp
	> Author: lihy
	> Mail: lihaiyangcsu@gmail.com 
	> Created Time: 2015-07-05 21:42:11
 ************************************************************************/

#include<stdio.h>

int partiton( int array[], int low, int high )
{
	int key = *(array+low);
	while( low < high )
	{
		while( low < high && key < *(array+high) )
			--high;	
		int tmp = *(array+high);
		*(array+high) = key;
		*(array+low) = tmp;
	
		while( (low+1) < high && key > *(array+low+1) )
			++low;
		tmp = *(array+high);
		*(array+high) = *(array+low+1);
		*(array+low+1) = tmp;
		
		++low;
		--high;
	}
	return low;
}


int merge( int array[], int low, int high )
{
	if( low < high )
	{
		int index = partiton( array, low, high );
		merge( array, low, index-1 );
		merge( array, index+1, high );
	}
	return 0;
}


int main()
{
	int array[] = { 12,3,34,56,12,8,9,100 };
	int ret = merge( array, 0, sizeof(array)/sizeof(int)-1 );
	for( int i = 0; i<sizeof(array)/sizeof(int); i++ )
	{
		printf( "%d ", array[i] );
	}
	printf( "\n" );

	return 0;
}

