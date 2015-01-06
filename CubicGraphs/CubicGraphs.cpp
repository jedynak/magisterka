/*
 * Author: Tomasz Jedynak
 * 
 * This program generates cubic graphs
 * 
 */
#include "CubicGraphGenerator.h"
#include "Halldorsson.h"
#include <iostream>
#include <time.h>
#include "IsBipartite.h"
#include "tools.h"

using namespace std;
/*
int main(){

	int **graph = new int*[MAX_VERTEX_NUMBER];
	int **limitedGraph = new int*[MAX_VERTEX_NUMBER];
	for(int h=0; h<MAX_VERTEX_NUMBER; ++h){
			graph[h] = new int[NUMBER_OF_NEIGHBOURS];
			limitedGraph[h] = new int[NUMBER_OF_NEIGHBOURS];
	}
	int *solution;
	int ratio;
	int foundNotBipartite=0;
	srand(time( NULL ));
	solution = new int[MAX_VERTEX_NUMBER];
	int independentSetSize;
	int isBipartite;
	int hasSet40,doBipartite;
	
	int graphNum=NUMBER_OF_GRAPH;

	for(int i=MIN_VERTEX_NUMBER;i<=MAX_VERTEX_NUMBER;i+=INCREASE_NUMBER_OF_VERTICES){
		hasSet40=0;
		foundNotBipartite=0;
		doBipartite=0;
		for(int j=0;j<graphNum;++j){
			isBipartite=1;
			generateCubicGraph(graph, i);
			Halldorsson(graph, i, solution);
			independentSetSize=0;
			for(int h=0; h<i; ++h){
				if(solution[h]==1)++independentSetSize;
			}

			deleteSet(graph,limitedGraph,i,solution);
			if(IsBipartite(limitedGraph,i)==0){
				isBipartite=0;
			}
			ratio = (independentSetSize*100/i);
			if(ratio>=40){
				++hasSet40;
			}
			if(isBipartite==0){
				++doBipartite;
			}
			if(isBipartite==0&&ratio>40){
				//cout<<i<<" vertices ratio: "<<ratio<<"% set size:"<<independentSetSize<<"*\n";
				++foundNotBipartite;
				//printGraph(graph,i,solution);
			}
			else{
				//cout<<i<<" vertices ratio: "<<ratio<<"% set size:"<<independentSetSize<<"\n";
			}
		}
		cout<<i<<" "<<foundNotBipartite<<" "<<hasSet40<<" "<<doBipartite<<endl;
	}
	//cout<<"found "<<foundNotBipartite<<" not bipartite graphs\n";
	for(int h=0; h<NUMBER_OF_NEIGHBOURS; ++h){
		delete [] graph[h];
	}
	delete []solution;
	delete []graph;
	return 0;
}*/