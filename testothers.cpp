/*************************************************************************
	> File Name: testothers.cpp 
	> Author: lihy
	> Mail: lihaiyangcsu@gmail.com 
	> Created Time: Wed 01 Jul 2015 09:38:54 AM CST
 ************************************************************************/

#include<stdio.h>
#include<string.h>


/*
 *1分2分5分的硬币，组成1角，共有多少种组合。
 * */
int coin( int sum )
{
	int count = 0;
	for( int i = 0; i<=sum/1; i++ )
	{
		for( int j = 0; j<=sum/2; j++ )
		{
			for( int k = 0; k<=sum/5; k++ )
			{
				if( sum == i*1+j*2+k*5 )
				{
					++count;
					printf( "1,2,5: %d %d %d\n", i, j, k );	
				}
			}	
		}
	}
	return count;
}


/*
 *char *str = "AbcABca";写出一个函数，查找出每个字符的个数，区分大小写，要求时间复杂度是n（提示用ASCⅡ码）
 * */
int statisticchar( const char* str )
{
	int result[128];
	memset( result, 0 , sizeof(result) );
	while( '\0' != *str )
	{
		*(result+*str) += 1;	
		++str;
	}
	for( int i = 0; i<sizeof(result)/sizeof(int); i++ )
	{
		if( 0 != *(result+i) )
			printf( "%c %d\n", i, *(result+i) );
	}
	return 0;
}


//求集合的交集
//a and b are sorted collections
int intersection( const int collection_a[], int size_a, const int collection_b[], int size_b )
{
	int i = 0, j = 0;
	while( i < size_a && j < size_b )
	{
		if( *(collection_a+i) < *(collection_b+j) ) {
			++i;
		} else if( *(collection_a+i) > *(collection_b+j) ) {
			++j;
		} else {
			printf( "%d ", *(collection_a+i) );
			int tmp = *(collection_a+i);
			//we should skip repeatable value if exists
			++i;
			while( i < size_a && tmp == *(collection_a+i) )
				++i;
			++j;
			while( j < size_b && tmp == *(collection_b+j) )
				++j;
		}
	}

	return 0;
}


int main()
{
	int ret = coin(11);
	printf( "ret %d\n", ret );

	const char* str = "ABCabcABC";
	printf( "str: %s\n", str );
	(void)statisticchar( str );

	int a[] = { 2,37,39,46,46,57,63,93 };
	int b[] = { 2,39,43,46,46,57,69,98,99 };
	intersection( a, sizeof(a)/sizeof(int), b, sizeof(b)/sizeof(int) );

	return 0;
}

