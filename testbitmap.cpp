/*************************************************************************
	> File Name: testbitmap.cpp
	> Author: lihy
	> Mail: lihaiyangcsu@gmail.com 
	> Created Time: 2015-07-05 19:16:03
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>


void bitmap( int array[], int key )
{
	array[key/32] |= (1<<(key%32));	
}


//signed int: 0x80000000
//& ==: priority
void traversal( int array[], int size )
{
	for( int i = size; i>=0; i-- )
	{
		if( 0 != *(array+i) )
		{
			for( int j = 31; j>=0; j-- )
			{
				if( 1 == ((*(array+i)>>j)&0x01) )
					printf( "%d ", i*32+j );
			}
		}
	}
}


int main()
{
	//2048*32 = 65536 [0-65535]
	int array[2048];
	memset( array, 0, sizeof(array) );
	
	bitmap( array, 1 );
	bitmap( array, 31 );
	bitmap( array, 32 );
	bitmap( array, 65535 );
	
	traversal( array, sizeof(array)/sizeof(int)-1 );
	printf( "\n" );

	return 0;
}

