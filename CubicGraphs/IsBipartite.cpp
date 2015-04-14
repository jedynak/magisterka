#include "IsBipartite.h"
#include "tools.h"

int IsBipartite(int **graph, int numberOfVertices, int *solution){
	int colorTable[MAX_VERTEX_NUMBER];
	for(int i=0;i<numberOfVertices;++i){
		colorTable[i]=0;
	}
	for(int i=0;i<numberOfVertices;++i){
		if(colorTable[i]==0&&solution[i]==0){
			colorTable[i]=1;
			if(colorVertices(graph, numberOfVertices,colorTable,i, solution)==0){
				return 0;
			}
		}
	}
	return 1;
}
int colorVertices(int **graph, int numberOfVertices,int *colorTable,int num, int *solution){
	int neighbour;
	for(int i=0;i<NUMBER_OF_NEIGHBOURS;++i){
		neighbour=graph[num][i];
		if(colorTable[neighbour]==colorTable[num]){
			return 0;
		} else{
			if(colorTable[neighbour]==0 && solution[i]==0){
				colorTable[neighbour]=3-colorTable[num];
				if( colorVertices(graph, numberOfVertices,colorTable,neighbour, solution) == 0) {
					return 0;
				}
			}
		}
	}
	return 1;
}