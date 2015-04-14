//#include <cppunit>
#include "tools.h"
#include <time.h>
#include "CubicGraphGenerator.h"
#include "Halldorsson.h"
#include <iostream>
#include "IsBipartite.h"
#include "BicubicScheduler.h"

void func(){
	int graph1[10][3] = {
		{1,2,3},
		{0,2,3},
		{1,0,4},
		{1,0,5},
		{6,2,5},
		{6,3,4},
		{4,5,7},
		{6,8,9},
		{7,9,9},
		{7,8,8}
	};
	int independentSet1a[10]={0,0,1,1,0,0,1,0,0,1};
	int independentSet1b[10]={0,0,1,1,0,0,1,0,0,0};
	int graph2[8][3] = {
		{1,2,3},
		{0,2,3},
		{1,0,4},
		{1,0,5},
		{2,6,7},
		{3,6,7},
		{4,5,7},
		{4,5,6}
	};
	int independentSet2a[8]={0,0,1,1,0,0,0,0};
	int independentSet2b[8]={0,0,1,1,0,0,0,1};
	int graph3[20][3] = {
		{1,2,12},
		{0,2,16},
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
		{1,2,4},
		{5,7,8},
		{6,8,11},
		{9,10,11},
		{0,3,6},
		{6,7,8},
		{7,9,10},
		{9,10,11}
	};
	int independentSet3[20]={0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1};

}

void testBiQubicGraphs(){

	int **graph = new int*[MAX_VERTEX_NUMBER];
	for(int h=0; h<MAX_VERTEX_NUMBER; ++h){
			graph[h] = new int[NUMBER_OF_NEIGHBOURS];
	}
	int *solution;
	int ratio;
	int foundNotBipartite=0;
	srand(time( NULL ));
	solution = new int[MAX_VERTEX_NUMBER];
	int independentSetSize;
	bool isBipartite;
	
	int graphNum=NUMBER_OF_GRAPH;

	for(int i=MIN_VERTEX_NUMBER;i<=MAX_VERTEX_NUMBER;i+=INCREASE_NUMBER_OF_VERTICES){
		for(int j=0;j<graphNum;++j){
			isBipartite = true;
			generateCubicGraph(graph, i);
			Halldorsson(graph, i, solution);
			independentSetSize=0;
			for(int h=0; h<i; ++h){
				if(solution[h]==1)++independentSetSize;
			}

			isBipartite = IsBipartite(graph,i,solution);
		
			if(isBipartite == true){
				BicubicScheduler scheduler(graph, i);
				float a = rand()/10000.0;
				float b = rand()/10000.0;
				float c = rand()/10000.0;
				std::cout<<"Speeds "<<a<<" "<<b<<" "<<c<<std::endl;
				scheduler.bicubicScheduling(a, b, c);
			}
		}
	}
	for(int h=0; h<NUMBER_OF_NEIGHBOURS; ++h){
		delete [] graph[h];
	}
	delete []solution;
	delete []graph;
}