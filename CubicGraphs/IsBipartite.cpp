#include "IsBipartite.h"
#include "tools.h"

int IsBipartite(int **graph, int numberOfVertices){
	int colorTable[MAX_VERTEX_NUMBER];
	for(int i=0;i<numberOfVertices;++i){
		colorTable[i]=0;
	}
	for(int i=0;i<numberOfVertices;++i){
		if(colorTable[i]==0){
			colorTable[i]=1;
			if(colorVertices(graph, numberOfVertices,colorTable,i)==0){
				return 0;
			}
		}
	}
	return 1;
}
int colorVertices(int **graph, int numberOfVertices,int *colorTable,int num){
	int neighbour;
	int result=1;
	for(int i=0;i<NUMBER_OF_NEIGHBOURS;++i){
		neighbour=graph[num][i];
		if(neighbour!=-1){
			if(colorTable[neighbour]==colorTable[num]){
				return 0;
			}
			else{
				if(colorTable[neighbour]==0){
					colorTable[neighbour]=3-colorTable[num];
					result *= colorVertices(graph, numberOfVertices,colorTable,neighbour);
				}
			}
		}
	}
	return result;
}