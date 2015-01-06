/*
 * Halldorsson algorithm is a greedy algorithm that
 * chooses vertices with lowest degree and adds them
 * to the solution. Next it deletes from the graph this
 * vertex and its neighbours.
 */
#include "Halldorsson.h"
#include "tools.h"
/* 
 * params: 
 * graph - representation of vertices and theirs three neighbours
 *	       e.g. graph[i][j] ( for j = {0,1,2} ) is equals k means that
 *         the verticex number k is neighbour to the vertex number i
 * numberOfVertices - number of vertices in graph
 *
 * returns:
 * verticesTab - this table says if vertex is in solution
 *         e.g. vertexTab[i] is 1 (true) if and only if
 *         the vertex number i is in the solution
 */

void Halldorsson(int **graph, int numberOfVertices, int *solution){
	bool isVertexDeleted[MAX_VERTEX_NUMBER];
	for(int i=0; i<numberOfVertices; ++i){
		solution[i]=0;
		isVertexDeleted[i]=false;
	}
	//copy graph to graphTmp just to be able to delete vertices
	int graphTmp[MAX_VERTEX_NUMBER][NUMBER_OF_NEIGHBOURS];
	for(int i=0; i<numberOfVertices; ++i){
		for(int j=0; j<NUMBER_OF_NEIGHBOURS; ++j){
			graphTmp[i][j]=graph[i][j];
		}
	}

	int finalNumberOfVertices=numberOfVertices;
	int minDegree;
	int tmpDegree;
	int vertexWithLowestDegree;
	while( finalNumberOfVertices > 0 ){
		minDegree=4;
		for(int i=0;i<numberOfVertices;++i){
			if(!isVertexDeleted[i]){
				tmpDegree=0;
				for(int j=0; j<NUMBER_OF_NEIGHBOURS; ++j){
					if(graphTmp[i][j]!=-1)++tmpDegree;
				}
				if(minDegree>tmpDegree){
					minDegree=tmpDegree;
					vertexWithLowestDegree=i;
				}
			}
		}
		int neighbourNumber,neighbourOfNeighbourNumber;
		for(int j=0; j<NUMBER_OF_NEIGHBOURS; ++j){
			neighbourNumber=graphTmp[vertexWithLowestDegree][j];
			if(!isVertexDeleted[neighbourNumber]){
				for(int h=0; h<NUMBER_OF_NEIGHBOURS; ++h){
					neighbourOfNeighbourNumber=graphTmp[neighbourNumber][j];
					if(!isVertexDeleted[neighbourOfNeighbourNumber]){
						for(int k=0; k<NUMBER_OF_NEIGHBOURS; ++k){
							if(graphTmp[neighbourOfNeighbourNumber][k]==neighbourNumber){
								graphTmp[neighbourOfNeighbourNumber][k]=-1;
							}
						}
					}
				}
				graphTmp[vertexWithLowestDegree][j]=-1;
				--finalNumberOfVertices;
				isVertexDeleted[neighbourNumber]=true;
			}
		}
		--finalNumberOfVertices;
		isVertexDeleted[vertexWithLowestDegree]=true;
		solution[vertexWithLowestDegree]=1;
	}

}