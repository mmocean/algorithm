/*************************************************************************
	> File Name: testcycleshift.cpp
	> Author: lihy
	> Mail: lihaiyangcsu@gmail.com 
	> Created Time: Sat 27 Jun 2015 04:15:24 PM CST
 ************************************************************************/

#include<stdio.h>

int cycleshift( int x, int n )
{
	for( int i = 0; i<n; i++ )
	{
		int bit = x&0x01;
		x >>= 1;
		x |= (bit<<31);
	}
	return x;
}


int main()
{
	int ret = cycleshift( 4, 1 );
	printf( "ret %d \n", ret );
	return 0;
}

