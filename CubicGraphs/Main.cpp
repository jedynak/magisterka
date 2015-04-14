#include <iostream>
#include <stdlib.h>
#include "DecyclingAlgorithm.h"
#include "CubicGraphs.h"
using namespace std;
void printIndependentSet(int *independentSet, int size){
	for(int i=0;i<size;++i){
		cout<<independentSet[i]<<" ";
	}
	cout<<endl;
}

int main(){
	testQubicGraphs();
	/*const int size=12;
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
	int independentSet[size]={1,1,1,1,1,0,0,0,0,0,0,0};
	*/


	/*
	numberOfVertices =20;
	int graphTmp[20][3] = {
		{1,2,12}, //1,2,16
		{0,2,16}, //0,2,12
		{1,0,12},
		{4,5,16},
		{3,5,12},
		{3,4,13},
		{14,16,17},
		{13,17,18},
		{13,14,17},
		{15,18,19},
		{15,18,19},
		{14,15,19},
		{1,0,4}, //1,2,4
		{5,7,8},
		{6,8,11},
		{9,10,11},
		{1,3,6}, //0,3,6
		{6,7,8},
		{7,9,10},
		{9,10,11}
	};
	int independentSet[20]={0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1};
	
	int **graph;
	graph = new int*[numberOfVertices];
	for(int i=0;i<numberOfVertices;++i){
		graph[i] = new int[NUMBER_OF_NEIGHBOURS];
		for(int j=0;j<NUMBER_OF_NEIGHBOURS;++j){
			graph[i][j]=graphTmp[i][j];
		}
	}
	do{
		printIndependentSet(independentSet, numberOfVertices);
	} while(!decyclingAlogorithm(graph,independentSet));
	
	printIndependentSet(independentSet, numberOfVertices);
	*/
	return 0;
}