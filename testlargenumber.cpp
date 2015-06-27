/*************************************************************************
	> File Name: testlargenumber.cpp
	> Author: lihy
	> Mail: lihaiyangcsu@gmail.com 
	> Created Time: Sat 27 Jun 2015 09:32:55 AM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int increment( char *str, int len )
{
	if( NULL == str )
		return -1;
	if( len > 0 )
	{
		*(str+len-1) += 1;
		while( len > 0 && *(str+len-1) > '9' )
		{
			*(str+len-1) = '0';
			if( --len > 0 )
				*(str+len-1) += 1;
			else 
				return 0;
		}
	}
}

//0 equal; 1:greater; 2:less -1:error
int judge( const char *s1, const char* s2 )
{
	int len1 = strlen(s1);
	int len2 = strlen(s2);
	if( len1 < len2 )
	{
		return 2;
	} else if( len1 > len2 ) {
		return 1;
	} else {
		for( int i = 0; i<len1; i++ )
		{
			if( *(s1+i) > *(s2+i) )
				return 1;
			else if( *(s1+i) < *(s2+i) )
				return 2;
		}
		return 0;
	} 
}

int display( char *str )
{
	int len = strlen(str);
	char *tmp = (char*)malloc(len+1);
	if( NULL == tmp )
		return -1;
	memset( tmp, '0', (len) );
	*(tmp+len) = 0;

	while( 2 == judge( tmp, str ) )
	{
		increment( tmp, len );
		const char* p = tmp;
		for( int i = 0; i<len; i++ )
		{
			if( *p > '0' && *p <= '9' )
			{
				printf( "%s|", p );
				break;
			}
			++p;
		}
	}
	printf("\n");
	free( tmp );
	return 0;
}

int main()
{
	char p[] = "98";
	char c[] = "123";
	(void)increment( p, strlen(p) );
	printf( "p %s\n", p );
	
	int res = judge( p, c );
	printf( "res %d\n", res );

	(void)display( p );
	
	return 0;
}

