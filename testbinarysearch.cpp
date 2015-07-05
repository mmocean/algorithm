/*************************************************************************
	> File Name: testbinarysearch.cpp
	> Author: lihy
	> Mail: lihaiyangcsu@gmail.com 
	> Created Time: 2015-07-05 18:47:05
 ************************************************************************/

#include<stdio.h>

//recursive
int binarysearch( int array[], int low, int high, int key )
{
	if( low <= high )
	{
		int middle = (low+high)/2;
		if( key < array[middle] )
		{
			return binarysearch( array, low, middle-1, key );
		} else if( key > array[middle] ) {
			return binarysearch( array, middle+1, high, key );	
		} else {
			return middle;
		}	
	}
	return -1;
}


//non-recursive
int binarysearch( int array[], int size, int key )
{
	int low = 0;
	int high = size-1;
	while( low <= high )
	{
		int middle = (low+high)/2;
		if( key < array[middle] )
			--high;
		else if( key > array[middle] )
			++low;
		else 
			return middle;	
	}
	return -1;
}


int main()
{
	int array[] = { 1,2,3,4,5,6,7 };
	int ret = binarysearch( array, 0, sizeof(array)/sizeof(int)-1, 8 );
	printf( "ret %d\n", ret );
	ret = binarysearch( array, sizeof(array)/sizeof(int), 3 );
	printf( "ret %d\n", ret );

	return 0;
}

