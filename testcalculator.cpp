/*************************************************************************
	> File Name: testcalculator.cpp
	> Author: lihy
	> Mail: lihaiyangcsu@gmail.com 
	> Created Time: Wed 01 Jul 2015 02:33:01 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include"definitionstack.h"

const char ADD = '+';
const char MINUS = '-';
const char MULT = '*';
const char DIVI = '/';
const char LP = '(';
const char RP = ')';

int calculator( const char*str, int *res )
{
	struct NODE* head = NULL;
	while( '\0' != *str )
	{	
		++str;
	}

	return 0;
}


int symbolmatching( const char* str )
{
	struct NODE* stack = NULL;
	if( 0 != push( &stack, (int)'#' ) )
		return -1;

	while( '\0' != *str )
	{
		char ch = 0;
		if( 0 != gettop( &stack, (int*)&ch ) )
			return -1;
		int flag = 0;
		switch( *str )
		{
			case ')':
				if( '(' == ch )
					flag = 1;
				break;
			case '}':
				if( '{' == ch )
					flag = 1;
				break;
			case ']':
				if( '[' == ch )
					flag = 1;
				break;	
		}
		if( 1 == flag )
		{
			if( 0 != pop( &stack, (int*)&ch ) )
				return -1;			
		} else {
			if( 0 != push( &stack, (int)*str ) )
				return -1;
		}
		++str;	
	}

	char ch = 0;
	if( 0 != gettop( &stack, (int*)&ch ) )
		return -1;
	if( '#' == ch )
	{
		if( 0 != pop( &stack, (int*)&ch ) )
			return -1;			
	}

	return isempty( &stack );
}


int main()
{
	const char* str = "()[]{}";	
	int ret = symbolmatching( str );
	printf( "ret %d \n", ret );

	return 0;
}


