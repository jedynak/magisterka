#include "tools.h"
#include <fstream>
#include <iostream>
using namespace std;

void deleteSet(int **graph,int **limitedGraph, int numberOfVertices,int *solution){
	int neigbour;
	int count=0;
	for(int i=0;i<numberOfVertices;++i){
		if(solution[i]==0){
			for(int j=0;j<NUMBER_OF_NEIGHBOURS;++j){
				neigbour=graph[i][j];
				if(solution[neigbour]==0){
					limitedGraph[i][j]=neigbour;
				}
				else{
					limitedGraph[i][j]=-1;
				}
			}
		}
		else{
			for(int j=0;j<NUMBER_OF_NEIGHBOURS;++j){
				limitedGraph[i][j]=-1;
			}
		}
	}
}

void printGraph(int **graph, int numberOfVertices, int *solution){
	ofstream myfile;
	char buffer [L_tmpnam];
	char * pointer;
	tmpnam (buffer);
	pointer = tmpnam (NULL);
	myfile.open (pointer);
	myfile << numberOfVertices<<"x"<<numberOfVertices<<"\n";
	char sign[2];
	sign[1]=0;
	for(int i=0;i<numberOfVertices;++i){
		for(int h=0;h<numberOfVertices;++h){
			sign[0]='0';
			for(int j=0;j<NUMBER_OF_NEIGHBOURS;++j){
				if(graph[i][j]==h){
					sign[0]='1';
				}
			}
			myfile << sign;
		}
		myfile << endl;
	}
	myfile << "independent set:\n";
	for(int i=0;i<numberOfVertices;++i){
		if(solution[i]==0){
			myfile << "0";
		}
		else{
			myfile << "1";
		}
	}
	myfile << endl;
	myfile.close();
}