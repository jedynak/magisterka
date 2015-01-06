/*
 * This generator allows to generates cubic graphs
 *  
 * 
 */
#include <time.h>
#include <cstdlib>
#include "CubicGraphGenerator.h"
#include "tools.h"

void generateCubicGraph(int **graph, int numberOfVertices){

	for(int i=0;i<BASE_SIZE;++i){
		for(int j=0;j<NUMBER_OF_NEIGHBOURS;++j){
			if(i<=j)graph[i][j]=j+1;
			else graph[i][j]=j;
		}
	}
	for(int i=BASE_SIZE;i<numberOfVertices-1;i+=2){
		int v1,v2,v3,v4; //4 vertices
		v1=rand()%i;
		v2=graph[v1][rand()%NUMBER_OF_NEIGHBOURS];
		v3=rand()%i;
		do{
			v4=graph[v3][rand()%NUMBER_OF_NEIGHBOURS];
		}
		while((v1==v3&&v2==v4)||(v1==v4&&v2==v3));

		graph[i][0]=i+1;
		graph[i][1]=v1;
		graph[i][2]=v2;
		graph[i+1][0]=i;
		graph[i+1][1]=v3;
		graph[i+1][2]=v4;
		for(int j=0;j<NUMBER_OF_NEIGHBOURS;++j){
			if(graph[v1][j]==v2)graph[v1][j]=i;
			if(graph[v2][j]==v1)graph[v2][j]=i;
			if(graph[v3][j]==v4)graph[v3][j]=i+1;
			if(graph[v4][j]==v3)graph[v4][j]=i+1;
		}
	}
}