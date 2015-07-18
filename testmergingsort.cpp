/*************************************************************************
	> File Name: mergingsort.cpp
	> Author: lihy
	> Mail: lihaiyangcsu@gmail.com 
	> Created Time: 2015-07-14 22:01:46
 ************************************************************************/

#include<stdio.h>

int merge( int a[], int tmp[], int low, int middle, int high )
{
	//copy to tmp
	for( int n = low; n<=high; n++ )
		*(tmp+n) = *(a+n);

	//merge
	int k = low, i = low, j = middle+1;
	for( ; i <= middle && j <= high ; )
	{
		if( *(tmp+i) < *(tmp+j) )
			*(a+k++) = *(tmp+i++);
		else
			*(a+k++) = *(tmp+j++);
	}
	while( i <= middle )
		*(a+k++) = *(tmp+i++);
	while( j <= high )
		*(a+k++) = *(tmp+j++);
		
	return 0;
}


int mergingsort( int a[], int tmp[], int low, int high )
{
	if( low < high )
	{
		int middle = (low+high)/2;
		//recursive
		mergingsort( a, tmp, low, middle );
		mergingsort( a, tmp, middle+1, high );
		merge( a, tmp, low, middle, high );			
	}

	return 0;
}


int main()
{
	int array[] = { 4,13,28,74,6,8,74 };
	int tmp[sizeof(array)/sizeof(int)];
	(void)mergingsort( array, tmp, 0, sizeof(array)/sizeof(int)-1 );
	for( int i = 0; i<sizeof(array)/sizeof(int); i++ )
	{
		printf( "%d ", *(array+i) );
	}
	printf( "\n" );

	return 0;
}

