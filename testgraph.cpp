/*************************************************************************
	> File Name: testgraph.cpp
	> Author: lihy
	> Mail: lihaiyangcsu@gmail.com 
	> Created Time: 2015-07-19 19:16:13
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include"definitionqueue.h"

//storage definition
//adjacency list
struct ArcNode
{
	int vertexindex;
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
	int graphsize;		//max vertex number
	int graphtype;
	int vertexnumber;
	int arcnumber;
	VertexNode vertex[0];	
};

enum 
{
	TYPE_DIRECTED_GRAPH,
	TYPE_UNDIRECTED_GRAPH,
	TYPE_DIRECTED_NETWORK,
	TYPE_UNDIRECTED_NETWORK
};

/*
 * eg. 'A,B,321)'
 * input : *start == 'A', size = 8, *(start+size) == ')'
 * output: *v = 'A', *w = 'B', *weight = 321
 * */
int parsetriple( const char *start, int size, int *v, int *w, int *weight )
{
	if( NULL == start || size < 1 )
		return -1;

	*v = (int)*start;
	start += 2;
	*w = (int)*start;
	start += 2;
	*weight = atoi(start);

	return 0;
}


struct VertexNode* getvertex( const struct Graph *graph, int vertex )
{
	if( NULL == graph )
		return NULL;
	
	struct VertexNode *vt = (struct VertexNode *)graph->vertex;	
	for( int i = 0; i < graph->vertexnumber; ++i )
	{
		if( vertex == vt->data )
			return vt;
		++vt;	
	}

	return NULL;
}


int locatevertex( const struct Graph *graph, int vertex ) 
{
	if( NULL == graph )
		return -1;

	struct VertexNode *vt = (struct VertexNode *)graph->vertex;	
	for( int i = 0; i < graph->vertexnumber; ++i )
	{
		if( vertex == vt->data )
			return i;
		++vt;	
	}

	return -1;
}


int insertarc( const struct Graph *graph, int v, int w, int weight )
{
	if( NULL == graph )
		return -1;
	
	struct VertexNode *vertex = getvertex( graph, v );
	if( NULL == vertex )
	{
		printf( "vertex %d does not exist\n", v );
		return -1;
	}

	int vertexindex = locatevertex( graph, w );
	if( -1 == vertexindex )		
	{
		printf( "vertexindex %d does not exist\n", v );
		return -1;
	}

	struct ArcNode *arc = vertex->firstarc;
	struct ArcNode *tail = vertex->firstarc;
	while( NULL != arc )
	{
		//if a same arc has been existed then terminate
		if( vertexindex == arc->vertexindex )	
			return -1;
		tail = arc;
		arc = arc->nextarc;
	}

	//allocate a new ArcNode
	arc = (struct ArcNode *)malloc( sizeof(struct ArcNode) );
	if( NULL == arc )
	{
		printf( "malloc error\n" );
		return -1; 
	}
	arc->vertexindex = vertexindex;
	arc->nextarc = NULL;

	//insert into list tail
	if( NULL == tail )
	{
		arc->nextarc = vertex->firstarc;
		vertex->firstarc = arc;
	} else {
		tail->nextarc = arc;	
	}

	switch( graph->graphtype )
	{
		case TYPE_DIRECTED_GRAPH:
			arc->info = 1;
			break;
		case TYPE_UNDIRECTED_GRAPH:
			insertarc( graph, w, v, weight );
			arc->info = 1;
			break;
		case TYPE_DIRECTED_NETWORK:
			arc->info = weight;
			break;
		case TYPE_UNDIRECTED_NETWORK:
			insertarc( graph, w, v, weight );
			arc->info = weight;
			break;
	}

	return 0;
}


/*
 *1. on success 0 is returned, otherwise -1 returned;
 *2. the format of triplearc is like this(vertex,vertex,weight): "(a,b,3),(b,c,5),...(e,f,8)";
 *3. meanwhile 0 or MAX_INT can represent infinity of weight;
 *
 * */
struct Graph* creategraph( int graphtype, int graphsize, int vertex[], int vertexnumber, const char *triplearc )
{
	if( NULL == triplearc || vertexnumber <= 0 || graphsize <= 0 || vertexnumber > graphsize )
		return NULL;
	
	struct Graph *graph = (struct Graph *)malloc( sizeof(struct Graph) + graphsize*sizeof(struct VertexNode) );
	if( NULL == graph )
	{
		printf( "malloc error\n" );
		return NULL;
	}

	//graph size
	graph->graphsize = graphsize;
	//graph type
	graph->graphtype = graphtype;
	//vertex number
	graph->vertexnumber = vertexnumber;

	//add vertex info
	//ignore duplicate checking, assume vertexes are varied
	struct VertexNode *vt = graph->vertex;
	for( int i = 0; i<vertexnumber; ++i )
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
			
			if( 0 != parsetriple( lbrace+1, rbrace-lbrace, &v ,&w, &weight ) )
			{
				printf( "parsetriple error\n" );
				return NULL;
			}

			if( 0 != insertarc( graph, v, w, weight ) )
			{
				printf( "insertarc error\n" );
				return NULL;
			}
			//arc number
			++graph->arcnumber;
		}	
		
		triplearc = ++rbrace;
	}
	
	return graph;
}


int destorygraph( struct Graph *graph )
{
	if( NULL == graph )
		return -1;
	
	struct VertexNode *vt = graph->vertex;
	for( int i = 0; i < graph->graphsize; ++i )
	{
		printf( "[vertex][name:%c index:%d] -> ", vt->data, i );
		struct ArcNode *arc = vt->firstarc;
		while( NULL != arc )			
		{
			struct ArcNode *tmp = arc->nextarc;
			printf( "[arc][index:%d weight:%d] -> ", arc->vertexindex, arc->info );
			free( (void*)arc );
			arc = arc->nextarc;		
		}
		printf( "NULL\n" );
		++vt;
	}

	free( (void*) graph );
	graph = NULL;

	return 0;
}


//a simple visit
int visit( const struct Graph *graph, int vertex )
{
	if( NULL == graph || vertex >= graph->vertexnumber )
		return -1;

	//node name
	printf( "%c -> ", (graph->vertex+vertex)->data );

	return 0;
}


int getfirstadjacency( const struct Graph *graph, int vertex )
{
	if( NULL == graph || vertex >= graph->vertexnumber )
		return -1;
	
	struct ArcNode *arc = (graph->vertex+vertex)->firstarc;
	if( NULL == arc )
		return -1;

	return arc->vertexindex;
}


int getnextadjacency( const struct Graph *graph, int vertex1, int vertex2 )
{
	if( NULL == graph || vertex1 >= graph->vertexnumber )
		return -1;
	
	struct ArcNode *arc = (graph->vertex+vertex1)->firstarc;
	while( NULL != arc )
	{
		if( vertex2 == arc->vertexindex )
			break;
		arc = arc->nextarc;
	}

	if( NULL == arc || NULL == arc->nextarc)
		return -1;

	return arc->nextarc->vertexindex;
}


//resursive
int DFSvisit( const struct Graph *graph, int v, char visited[] )
{
	visit( graph, v );
	*(visited+v) = 1;	//has been visited

	for( int w = getfirstadjacency( graph, v ); w >= 0; w = getnextadjacency( graph, v, w ) )
	{
		if( 0 == *(visited+w) )
		{
			DFSvisit( graph, w, visited );	
		}
	}

	return 0;
}


int DFStraversal( const struct Graph *graph )
{
	if( NULL == graph )
		return -1;

	char *visited = (char *)calloc( graph->vertexnumber, sizeof(char) );	
	if( NULL == visited )
	{
		printf( "calloc error\n" );
		return -1;
	}

	for( int i = 0; i<graph->vertexnumber; ++i )
	{
		if( 0 == *(visited+i) )	
		{
			printf( "<tree: \n" );
			DFSvisit( graph, i, visited );
			printf( "\n" );
		}	
	}
	printf( "\n" );

	if( NULL != visited )
		free( (void*)visited );

	return 0;
}


//non-resursive
int BFStraversal( const struct Graph *graph )
{
	if( NULL == graph )
		return -1;
	
	char *visited = (char *)calloc( graph->vertexnumber, sizeof(char) );	
	if( NULL == visited )
	{
		printf( "calloc error\n" );
		return -1;
	}
	
	struct Queue q;
	q.front = q.rear = NULL;
	
	for( int i = 0; i<graph->vertexnumber; ++i )
	{
		if( 0 != *(visited+i) )
			continue;		
		
		printf( "<tree: \n" );
		visit( graph, i );
		*(visited+i) = 1;	//has been visited
		
		if( 0 != enqueue( &q, i ) )
			return -1;

		while( 0 != isempty( &q ) )
		{
			int v = -1;
			if( 0 != dequeue( &q, (int*)&v ) )
				return -1;

			for( int w = getfirstadjacency( graph, v ); w >= 0; w = getnextadjacency( graph, v, w ) )
			{
				if( 0 != *(visited+w) )
					continue;		
				
				visit( graph, w );
				*(visited+w) = 1;	//has been visited

				if( 0 != enqueue( &q, w ) )
					return -1;
			}
		}	
		printf( "\n" );
	}
	printf( "\n" );

	if( NULL != visited )
		free( (void*)visited );

	return 0;
}


int main()
{
	/*
	int vertex[] = { 'A','B','C','D' };
	const char *triplearc = "(A,B,3), (A,C,5), (B,C,4), (C,D,2)";
	*/
	int vertex[] = { '1','2','3','4','5','6','7','8','9','A' };
	const char *triplearc = "(1,2),(1,3),(2,4),(2,5),(3,6),(3,7),(4,8),(5,8),(6,7),(9,A)";

	printf( "creategraph:\n" );
	printf( "triplearc:%s\n", triplearc );
	struct Graph *graph = creategraph( TYPE_DIRECTED_NETWORK, sizeof(vertex)/sizeof(int), vertex, sizeof(vertex)/sizeof(int), triplearc );
	if( NULL == graph )
		printf( "creategraph error \n" );

	printf( "DFStraversal:\n" );
	if ( 0 != DFStraversal( graph ) )
		printf( "DFStraversal error \n" );

	printf( "BFStraversal:\n" );
	if ( 0 != BFStraversal( graph ) )
		printf( "BFStraversal error \n" );

	printf( "destorygraph:\n" );
	if( NULL != graph )
		if( 0 != destorygraph( graph ) )
			printf( "destorygraph error \n" );

	return 0;
}


