/*************************************************************************
	> File Name: testkmp.cpp
	> Author: lihy
	> Mail: lihaiyangcsu@gmail.com 
	> Created Time: Tue 30 Jun 2015 10:00:03 AM CST
 ************************************************************************/

#include<stdio.h>
#include<string.h>


int getnext( const char *str, int size )
{
	for( int i = 1; i<size; i++ )
	{
		int j = i;
		while( j<size && ( *(str+j-i) == *(str+j) ) )
			++j;
		if( size == j )
			return (size-i);	
	}
	return 0;
}


int kmp( const char* src, const char* pattern )
{
	if( NULL == src || NULL == pattern )
		return -1;
	
	const char* head = src;
	int len = strlen(pattern);
	
	int count = 0;
	while( '\0' != *src )
	{
		int next = (count > 0)?getnext( pattern, count ):0;
		count = count - next;
		while( '\0' != *src && '\0' != *(pattern+next) && (*src == *(pattern+next)) )
		{
			++next;
			++count;
			++src;
		}
		if( len == next )
			return (src-head-len);
		if( 0 == next )
			++src;
	}
	return -1;	
}


int main()
{
	const char* str = "ababdababc";
	const char* p = "bd";

	printf( "str: %s\n", str );
	printf( "p:   %s\n", p );

	int ret = getnext( p, strlen(p) );
	printf( "ret %d\n", ret );

	ret = kmp( str, p );
	printf( "subfix %d\n", ret );

	return 0;
}

