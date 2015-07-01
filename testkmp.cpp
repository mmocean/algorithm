/*************************************************************************
	> File Name: testkmp.cpp
	> Author: lihy
	> Mail: lihaiyangcsu@gmail.com 
	> Created Time: Tue 30 Jun 2015 10:00:03 AM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>


inline int getnext( const char *str, int size )
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
	int count = 0;
		
	while( '\0' != *src )
	{
		int next = (count > 0)?getnext( pattern, count ):0;
		count = next;
		const char* subfix = src-count;
		while( '\0' != *src && '\0' != *(pattern+next) && (*src == *(pattern+next)) )
		{
			++next;
			++count;
			++src;
		}
		if( '\0' == *(pattern+next) )
			return (subfix-head);
		if( 0 == next )
			++src;
	}
	return -1;	
}


int bf( const char* src, const char* pattern )
{
	if( NULL == src || NULL == pattern )
		return -1;

	const char* head = src;
	
	while( '\0' != *src )
	{
		const char* tmps = src;
		const char* tmpp = pattern;
		while( '\0' != *src && '\0' != *tmpp && (*src == *tmpp) )
		{
			++src;
			++tmpp;
		}
		if( '\0' == *tmpp )	
			return (tmps-head);
		src = ++tmps;	
	}

	return -1;
}


int main( int argc, char **argv )
{
	if( argc < 3 )
		exit(-1);

	const char* p = argv[1];
	const char* str = argv[2];

	printf( "strlen str: %d\n", strlen(str) );

	int ret = getnext( p, strlen(p) );
	printf( "ret %d\n", ret );

	//ret = kmp( str, p );
	ret = bf( str, p );
	printf( "subfix %d\n", ret );

	return 0;
}

