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
		while( low < high && key <= *(array+high) )
			--high;	
		*(array+low) = *(array+high);
	
		while( low < high && key >= *(array+low) )
			++low;
		*(array+high) = *(array+low);	
	}
	*(array+low) = key;

	return low;
}


int quicksort( int array[], int low, int high )
{
	if( low < high )
	{
		int index = partiton( array, low, high );
		quicksort( array, low, index-1 );
		quicksort( array, index+1, high );
	}
	return 0;
}


int main()
{
	int array[] = { 12,3,34,56,12,8,9,100 };
	int ret = quicksort( array, 0, sizeof(array)/sizeof(int)-1 );
	for( int i = 0; i<sizeof(array)/sizeof(int); i++ )
	{
		printf( "%d ", *(array+i) );
	}
	printf( "\n" );

	return 0;
}

