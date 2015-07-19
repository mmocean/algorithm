/*************************************************************************
	> File Name: testgraph.cpp
	> Author: lihy
	> Mail: lihaiyangcsu@gmail.com 
	> Created Time: 2015-07-19 19:16:13
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>

//storage definition
//adjacency list
struct ArcNode
{
	int indexvertex;
	int info;			//eg. arc weight
	ArcNode *nextarc;
};

struct VertexNode
{	
	int data;			//eg. vertex name
	ArcNode *firstarc;
};

struct Graph
{
	int numbervertex;
	int numberarc;
	VertexNode *vertex;	
};


/*
 * eg. 'A,B,321)'
 * *start == 'A', *end == ')'
 *
 * */
int parsetriple( const char *start, const char *end, int *v, int *w, int *weight )
{
	if( NULL == start || NULL == end )
		return -1;

	*v = (int)*start;
	start += 2;
	*w = (int)*start;
	start += 2;
	*weight = (int)*start;

	return 0;
}


struct VertexNode* getvertex( const struct Graph *graph, int vertex )
{
	if( NULL == graph || NULL == graph->vertex )
		return NULL;
	
	struct VertexNode *vt = graph->vertex;	
	for( int i = 0; i < graph->numbervertex; ++i )
	{
		if( vertex == vt->data )
			return vt;
		++vt;	
	}

	return NULL;
}


int locatevertex( const struct Graph *graph, int vertex ) 
{
	if( NULL == graph || NULL == graph->vertex )
		return -1;

	struct VertexNode *vt = graph->vertex;	
	for( int i = 0; i < graph->numbervertex; ++i )
	{
		if( vertex == vt->data )
			return i;
		++vt;	
	}

	return -1;
}


int insertarc( const struct Graph *graph, int v, int w, int weight )
{
	if( NULL == graph || NULL == graph->vertex )
		return -1;
	
	struct VertexNode *vertex = getvertex( graph, v );
	if( NULL == vertex )
		return -1;

	int indexvertex = locatevertex( graph, w );
	if( -1 == indexvertex )		
		return -1;

	struct ArcNode *arc = (struct ArcNode *)malloc( sizeof(struct ArcNode) );
	if( NULL == arc )
		return -1; 
	arc->indexvertex = indexvertex;
	arc->info = weight;

	//insert into list
	arc->nextarc = vertex->firstarc;
	vertex->firstarc = arc;

	return 0;
}


/*
 *1. on success 0 is returned, otherwise -1 returned;
 *2. the format of triplearc is like this(vertex,vertex,weight): "(a,b,3),(b,c,5),...(e,f,8)";
 *3. meanwhile 0 or MAX_INT can represent infinity of weight;
 *
 * */
int creategraph( struct Graph *graph, int vertex[], int numbervertex, const char *triplearc )
{
	if( NULL == graph || NULL == triplearc || numbervertex <= 0 )
		return -1;

	//vertex number
	graph->numbervertex = numbervertex;

	struct VertexNode *vt = (struct VertexNode *)malloc( numbervertex*sizeof(struct VertexNode) );
	if( NULL == vt )
		return -1;
	graph->vertex = vt;

	//add vertex info
	//ignore duplicate checking, assume vertexes are varied
	for( int i = 0; i<numbervertex; ++i )
	{
		vt->data = *(vertex+i);
		vt->firstarc = NULL;
		++vt;	
	}

	//add arc info
	while( '\0' != *triplearc )
	{
		const char *lbrace = triplearc;
		const char *rbrace = triplearc;

		while( '\0' != *lbrace && '(' != *lbrace )
			++lbrace;
		while( '\0' != *rbrace && ')' != *rbrace )
			++rbrace;
	
		if( '\0' == *lbrace || '\0' == *rbrace )
			break;

		//parsing a trpile from lbrace to rbrace
		if( lbrace+1 < rbrace )
		{
			int v = 0, w = 0, weight = 0;
			
			if( 0 != parsetriple( lbrace+1, rbrace, &v ,&w, &weight ) )
				return -1;
	
			if( 0 != insertarc( graph, v, w, weight ) )
				return -1;

			//arc number
			++graph->numberarc;
		}	
		
		triplearc = ++rbrace;
	}
	
	return 0;
}


int main()
{
	int vertex[] = { 'A','B','C' };
	const char *triplearc = "(A,B,3),(A,C,5),(B,C,4)";

	struct Graph graph;
	int ret = creategraph( &graph, vertex, sizeof(vertex)/sizeof(int), triplearc );
	printf( "%d \n", ret );

	return 0;
}


