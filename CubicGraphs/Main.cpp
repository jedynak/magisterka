#include <iostream>
#include <stdlib.h>
#include "DecyclingAlgorithm.h"
using namespace std;
int main(){
	const int size=12;
	int graphTmp[size][NUMBER_OF_NEIGHBOURS] = {
		{5,6,9},
		{5,6,8},
		{5,7,8},
		{6,7,11},
		{7,8,10},
		{0,1,2},
		{0,1,3},
		{2,3,4},
		{1,2,4},
		{0,10,11},
		{4,9,11},
		{3,9,10}
	};
	int **graph;
	graph = new int*[size];
	for(int i=0;i<size;++i){
		graph[i] = new int[NUMBER_OF_NEIGHBOURS];
		for(int j=0;j<NUMBER_OF_NEIGHBOURS;++j){
			graph[i][j]=graphTmp[i][j];
		}
	}
	int independentSet[size]={1,1,1,1,1,0,0,0,0,0,0,0};
	while(!decyclingAlogorithm(graph,independentSet,size)){}
	return 0;
}