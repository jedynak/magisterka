#include <math.h>
#include <deque>
#include <iostream>
#include "DecyclingAlgorithm.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

int numberOfVertices;

void copySets(int *fromSet, int *toSet, int size){
	for(int i=0;i<size;++i){
		toSet[i] = fromSet[i];
	}
}

int checkIfCycleWasDeleted(int **graph, int *independentSet,std::list<int>::iterator it){
	int vertex = *it;
	int prevVertex = vertex;
	do{
		int j;
		for(j=0;j<NUMBER_OF_NEIGHBOURS;++j){
			int tmpVertex = graph[vertex][j];
			if(independentSet[tmpVertex]==0 && tmpVertex != prevVertex){
				prevVertex = vertex;
				vertex = tmpVertex;
				break;
			}
		}
		if (j == NUMBER_OF_NEIGHBOURS){
			return true;
		}
	} while(vertex != *it);
	return false;
}

bool decyclingAlogorithm(int **graph, int *independentSet){
	int *freeAndPseudoFreeVertices = new int[numberOfVertices];
	int *newIndependentSet = new int[numberOfVertices];
	for(int i=0;i<numberOfVertices;++i){
		freeAndPseudoFreeVertices[i]=VertexFreedom::NOT_FREE_VERTEX;
	}
	int *cycle = findAnyOddCycle(graph,independentSet);
	if(cycle == NULL){
		return true;
	}
	bool solutionFound=false;
	//if vertex in cycle has only neighbours outside independent set -> solution found
	for(int i=0;i<numberOfVertices;++i){
		int degree = 0;
		if(cycle[i]==1){
			for(int j=0;j<NUMBER_OF_NEIGHBOURS;++j){
				if(independentSet[graph[i][j]]==0){
					++degree;
				}
			}
			if(degree==NUMBER_OF_NEIGHBOURS){
				independentSet[i] = 1;
				solutionFound = true;
			}
		}
	}
	if(solutionFound == false){
		findFreeVertices(graph, independentSet, freeAndPseudoFreeVertices);
		findPseudoFreeVerticles(graph, independentSet, freeAndPseudoFreeVertices);

		std::list<int> *path;
		//create initial path
		path = createPath(graph, cycle, independentSet, freeAndPseudoFreeVertices); 

		int in=0;
		int out = 0;
		bool deletedCycle = alternatingPath(path, independentSet, graph, in, out);
		createNewIndependentSet(path, freeAndPseudoFreeVertices, independentSet, newIndependentSet, graph, in, out);
		if( deletedCycle == false){
			deletedCycle = checkIfCycleWasDeleted(graph,newIndependentSet,std::next(path->begin(),out-1));
		}
		while(!deletedCycle){
			copySets(newIndependentSet,independentSet,numberOfVertices);
			in = out;
			deletedCycle = nonAlternatingPath(in, out, path, freeAndPseudoFreeVertices, independentSet, newIndependentSet, graph);
		}
		copySets(newIndependentSet,independentSet,numberOfVertices);
	}
	//delete path
	return false;
}

int createPathEndingWithFreeVertex(int **graph, std::list<int> *path,int *usedVertices, int *freeAndPseudoFreeVertices, int currentVertex){
	for(int i=0;i<NUMBER_OF_NEIGHBOURS;++i){
		int vertex = graph[currentVertex][i]; 
		if(usedVertices[vertex]==0){
			usedVertices[vertex]=1;
			path->push_back(vertex);
			if(freeAndPseudoFreeVertices[vertex]>0){
				return 1;
			}
			if(createPathEndingWithFreeVertex(graph,path,usedVertices,freeAndPseudoFreeVertices, vertex)==1){
				return 1;
			} else {
				path->pop_back();
			}
		}
	}
	return 0;
}

std::list<int> * createPath(int **graph, int *cycle, int *independentSet, int *freeAndPseudoFreeVertices){
	std::list<int> *path = new std::list<int>();
	int *usedVertices = new int[numberOfVertices];
	for( int i=0;i<numberOfVertices;++i){
		usedVertices[i]=0;
	}
	int startVertex=-1;
	for(int i=0;i<numberOfVertices;++i){
		if(cycle[i]==1){
			if(startVertex == -1){
				startVertex=i;
			}
			usedVertices[i]=1;
		}
	}
	path->push_back(startVertex);
	createPathEndingWithFreeVertex(graph,path,usedVertices,freeAndPseudoFreeVertices, startVertex);
	return path;
}

int findPathBetweenVertices(int **graph, int *independentSet, int *usedVertices,int prevVertex, int destination,int pathLength){
	++pathLength;
	for(int j=0;j<NUMBER_OF_NEIGHBOURS;++j){
		int tmpVertex = graph[prevVertex][j];
		if(tmpVertex == destination){
			return pathLength;
		}
		if(independentSet[tmpVertex]==0 && usedVertices[tmpVertex]==0){
			usedVertices[tmpVertex]=1;
			int tmpPathLength = findPathBetweenVertices(graph,independentSet,usedVertices,tmpVertex,destination, pathLength);
			if(tmpPathLength%2==1){
				return tmpPathLength;
			}
		}
	}
	return 0;
}

bool findIfCycle(int **graph, int *independentSet, int independentVertex){
	int *usedVertices;
	usedVertices = new int[numberOfVertices];
	for(int j=0;j<NUMBER_OF_NEIGHBOURS;++j){
		int firstVertex = graph[independentVertex][j];
		int secondVertex = graph[independentVertex][(j+1)%NUMBER_OF_NEIGHBOURS];
		if( independentSet[firstVertex]==0 && independentSet[secondVertex]==0){
			for( int i=0;i<numberOfVertices;++i){
				usedVertices[i]=0;
			}
			usedVertices[firstVertex]=1;
			int pathLenght=findPathBetweenVertices(graph,independentSet,usedVertices,firstVertex,secondVertex,0);
			if (pathLenght%2==1){
				//delete usedVertices;
				return true;
			}
		}
	}
	//delete usedVertices;
	return false;
}

void findFreeVertices(int **graph, int *independentSet,int *freeAndPseudoFreeVertices){
	const int NOT_IN_PATH=0;
	const int IN_PATH=1;
	for(int i=0;i<numberOfVertices;++i){
		if(independentSet[i]==1){
			if(!findIfCycle(graph,independentSet,i)){
				freeAndPseudoFreeVertices[i]=VertexFreedom::FREE_VERTEX;
			}
		}
	}
}

void findPseudoFreeVerticles(int **graph, int *independentSet,int *freeAndPseudoFreeVertices){
	for(int i=0;i<numberOfVertices;++i){
		for(int j=0;j<numberOfVertices;++j){
			if(independentSet[i]==1&&independentSet[j]==1){
				int commonNeighbours=0;
				int u,v;
				for(int k=0;k<NUMBER_OF_NEIGHBOURS;++k){
					for(int h=0;h<NUMBER_OF_NEIGHBOURS;++h){
						if(graph[i][k]==graph[j][h]){
							if(commonNeighbours>0)u=graph[i][k];
							else v=graph[i][k];
							++commonNeighbours;
						}
					}
				}
				if(commonNeighbours==2){
					bool isDiamond=false;
					for(int k=0;k<NUMBER_OF_NEIGHBOURS;++k){
						if(graph[u][k]==v)isDiamond=true;
					}
					if(isDiamond){
						findPseudoFreeVerticlesType1(graph, independentSet, freeAndPseudoFreeVertices,u,v,i,j);
						findPseudoFreeVerticlesType2(graph, independentSet, freeAndPseudoFreeVertices,u,v,i,j);
					}
				}
			}
		}
	}
}

bool findOddCycle(int **graph, int *independentSet,int destinationVertex,int *usedVertices,int currentVertex,int length){
	const int NOT_IN_PATH=0;
	const int IN_PATH=1;
	usedVertices[currentVertex]=IN_PATH;
	for(int j=0;j<NUMBER_OF_NEIGHBOURS;++j){
		if(graph[currentVertex][j]==destinationVertex&&length%2==1)return true;
		if(independentSet[currentVertex]==0&&usedVertices[j]==NOT_IN_PATH){
			if(findOddCycle(graph,independentSet,destinationVertex,usedVertices,j,length+1)==true)return true;
			usedVertices[j]=NOT_IN_PATH;
		}
	}
	return false;
}

void findPseudoFreeVerticlesType1(int **graph, int *independentSet,int *freeAndPseudoFreeVertices, int indep1, int indep2, int notIndep1, int notIndep2){
	const int NOT_IN_PATH=0;
	const int IN_PATH=1;
	int *usedVertices;
	usedVertices = new int[numberOfVertices];
	for(int k=0;k<numberOfVertices;++k){
		usedVertices = NOT_IN_PATH;
	}
	if(findOddCycle(graph, independentSet, notIndep1, usedVertices, notIndep2,5)==false){
		freeAndPseudoFreeVertices[indep1]=VertexFreedom::PSEUDO_FREE_VERTEX_TYPE1;
		freeAndPseudoFreeVertices[indep2]=VertexFreedom::PSEUDO_FREE_VERTEX_TYPE1;
	}
}

void findPseudoFreeVerticlesType2(int **graph, int *independentSet,int *freeAndPseudoFreeVertices, int indep1, int indep2,int notIndep1, int notIndep2){
	int cycleVertex1, cycleVertex2;
	for(int k=0;k<NUMBER_OF_NEIGHBOURS;++k){
		if(graph[indep1][k]!=notIndep1&&graph[indep1][k]!=notIndep2)
			cycleVertex1=graph[indep1][k];
		if(graph[indep2][k]!=notIndep1&&graph[indep2][k]!=notIndep2)
			cycleVertex2=graph[indep1][k];
	}
	for(int k=0;k<NUMBER_OF_NEIGHBOURS;++k){
		for(int h=0;h<NUMBER_OF_NEIGHBOURS;++h){
			if(graph[cycleVertex1][k]==graph[cycleVertex2][h]&&independentSet[graph[cycleVertex2][h]]==1){
				freeAndPseudoFreeVertices[indep1]=VertexFreedom::PSEUDO_FREE_VERTEX_TYPE2;
				freeAndPseudoFreeVertices[indep2]=VertexFreedom::PSEUDO_FREE_VERTEX_TYPE2;
			}
		}
	}
}

bool alternatingPath(std::list<int> *path, int *independentSet, int**graph,int num, int &out){
	std::list<int>::iterator it=path->begin();
	bool retVal = false;
	while(it!=path->end()){
		if(num<path->size()-1){
			++num;
			++it;
		}
		if(independentSet[*it]==0){
			--num;
			break;
		}
		if(num==path->size()-1){
			++num;
			retVal = true;
			break;
		}
		++num;
		++it;
		int independentNeighbours=0;
		for(int k=0;k<NUMBER_OF_NEIGHBOURS;++k){
			if(independentSet[graph[*it][k]]==1)++independentNeighbours;
		}
		if(independentSet[independentNeighbours]==NUMBER_OF_NEIGHBOURS){
			break;
		}
	}
	out = num;
	return retVal;
}

void createNewIndependentSet(std::list<int> *path,int* freeAndPseudoFreeVertices, int *independentSet, int *newIndependentSet, int**graph,int in,int out){
	for(int i=0;i<numberOfVertices;++i){
		newIndependentSet[i]=independentSet[i];
	}
	int isOdd=1;
	std::list<int>::iterator it=path->begin();
	for(int i=in;i<out;++i){
		if(isOdd==1){
			newIndependentSet[*it]=1;
		}else{
			newIndependentSet[*it]=0;
		}
		isOdd=1-isOdd;
		++it;
	}
	int u=path->back();
	int finalA,a,b;
	if( out==path->size()+1 && 
		(freeAndPseudoFreeVertices[u]==VertexFreedom::PSEUDO_FREE_VERTEX_TYPE1 ||
		freeAndPseudoFreeVertices[u]==VertexFreedom::PSEUDO_FREE_VERTEX_TYPE2)){
		for(int k=0;k<NUMBER_OF_NEIGHBOURS;++k){
			a=graph[u][k];
			b=graph[u][(k+1)%NUMBER_OF_NEIGHBOURS];
			for(int i=0;i<NUMBER_OF_NEIGHBOURS;++i){
				if(graph[a][i]==b){
					finalA=a;
				}
			}
		}
		newIndependentSet[finalA]=1;
		newIndependentSet[u]=0;
	}
}

bool nonAlternatingPath(int in,int &out,std::list<int> *path,int* freeAndPseudoFreeVertices , int *independentSet, int *newIndependentSet, int**graph){
	bool deletedCycle = true;
	std::list<int>::iterator it = std::next(path->begin(),in-1);
	std::list<int>::iterator it2 = std::next(path->begin(),in);
	int * cycle = findCycle(graph,independentSet,*it,*it2);
	int numOfNeighbours;
	int i=0;
	if(cycle == NULL){
		return true;
	}
		std::cout<<"a"<<independentSet[19]<<" ";
	while(i<numberOfVertices){
		numOfNeighbours=0;
		if(cycle[i]==1){
			for(int j=0; j<NUMBER_OF_NEIGHBOURS;++j){
				if(independentSet[graph[i][j]]==0){
					++numOfNeighbours;
				}
			}
			if(numOfNeighbours==NUMBER_OF_NEIGHBOURS){
				break;
			}
		}
		++i;
	}
		std::cout<<"m"<<independentSet[19]<<" ";
	if(numOfNeighbours==NUMBER_OF_NEIGHBOURS){
		independentSet[i]=1;
		out = (int)distance(path->begin(),path->end());
		deletedCycle = true;  
		std::cout<<"l"<<independentSet[19]<<" ";
	}else{
		std::cout<<"k"<<independentSet[19]<<" ";
		it = std::next(path->begin(),in+1);
		while(it!=path->end()){
			if(cycle[*it]==0){
				break;
			}else{
				++it;
			}
		}
		std::cout<<"j"<<independentSet[19]<<" ";
		int i=*it;
		if(independentSet[i]==1){
			out = std::distance(path->begin(),it)-1;
			for(int i=0;i<numberOfVertices;++i){
				newIndependentSet[i] = independentSet[i];
			}
			deletedCycle = false; 
		std::cout<<"i"<<independentSet[19]<<" ";
		}else{
			std::list<int> tmpPath(next(path->begin(),in+1),path->end());
		std::cout<<"h"<<independentSet[19]<<" ";
			setIndependentSet(tmpPath,freeAndPseudoFreeVertices, independentSet, newIndependentSet,graph);
		std::cout<<"g"<<independentSet[19]<<" ";
			out = i;
		}
	}
		std::cout<<"f"<<independentSet[19]<<" ";
	//delete cycle;
	return deletedCycle;
}

void setIndependentSet(std::list<int> &path,int* freeAndPseudoFreeVertices, int *independentSet, int *newIndependentSet, int**graph){
	std::list<int>::iterator it=path.begin();
	if(it!=path.end()&&++it!=path.end()){
		++it;
	}
	int subcase=1;
	int vertexNum=2;

	while(it!=path.end()){
		int neighboursInIndependentSet=0;
		for(int i=0;i<NUMBER_OF_NEIGHBOURS;++i){
			if(independentSet[graph[*it][i]]==1){
				++neighboursInIndependentSet;
			}
			if(neighboursInIndependentSet!=2){
				subcase=2;
			}
		}
		if(subcase == 2){
			break;
		}
		++it;
		if(it!=path.end()){
			++it;
		}
		vertexNum+=2;
	}
	if(subcase==1){
		for(int i=0;i<numberOfVertices;++i){
			newIndependentSet[i]=independentSet[i];
		}
		int i=1;
		for(auto it:path){
			if(i%2==0){
				newIndependentSet[it]=1;
			} else {
				newIndependentSet[it]=0;
			}
			++i;
		}
		int lastElementInPath = *(--path.end());
		if(freeAndPseudoFreeVertices[lastElementInPath]==VertexFreedom::PSEUDO_FREE_VERTEX_TYPE1 ||
			freeAndPseudoFreeVertices[lastElementInPath]==VertexFreedom::PSEUDO_FREE_VERTEX_TYPE2){
				for(int i=0;i<NUMBER_OF_NEIGHBOURS;++i){
					int currentNeighbour=graph[lastElementInPath][i];
					if(graph[lastElementInPath][(i+1)%NUMBER_OF_NEIGHBOURS]==currentNeighbour){
						int anotherIndependentVertex=-1;
						for(int j=0;j<NUMBER_OF_NEIGHBOURS;++j){
							if(independentSet[graph[lastElementInPath][j]]==1 &&
								graph[lastElementInPath][j]!=lastElementInPath){
								anotherIndependentVertex=graph[lastElementInPath][j];
							}
						}
						newIndependentSet[currentNeighbour]=1;
						newIndependentSet[anotherIndependentVertex]=0;
						break;
					}
				}
		}
	} else {
		it=path.begin();
		for(int i=0;i<vertexNum;++i){
			if(i%2==0){
				independentSet[*it]=1;
			} else {
				independentSet[*it]=0;
			}
			++it;
		}
	}

}

int *findAnyOddCycle(int **graph,int *independentSet){
	for(int j=0;j<numberOfVertices;++j){
		for(int i=0;i<NUMBER_OF_NEIGHBOURS;++i){
			int tmpVertex = graph[j][i];
			if(tmpVertex > j ){ //to prevent checking pair of vertices twice
				if(independentSet[j] == 0 && independentSet[tmpVertex] == 0){
					int *cycle = findCycle(graph,independentSet, j, tmpVertex);
					if(cycle != NULL){
						return cycle;
					}
				}
			}
		}
	}
	return NULL;
}

int* findCycle(int **graph,int *independentSet, int v1, int v2){
	int *cycle=new int[numberOfVertices];
	int *usedVertices=new int[numberOfVertices];
	for(int i=0;i<numberOfVertices-2;++i){
		usedVertices[i]=independentSet[i];
		cycle[i]=0;
	}
	cycle[v1]=1;
	cycle[v2]=1;
	usedVertices[v1]=1;
	usedVertices[v2]=1;
	for(int i=0;i<NUMBER_OF_NEIGHBOURS;++i){
		int tmpVertex = graph[v1][i];
		if( usedVertices[tmpVertex] == 0){
			usedVertices[tmpVertex]=1;
			cycle[tmpVertex]=1;
			if(hasOddCycle(graph,usedVertices,cycle,v1, tmpVertex, v2, 3)){
				delete[] usedVertices;
				return cycle;
			}
			usedVertices[tmpVertex]=0;
			cycle[tmpVertex]=0;
		}
	}
	delete[] usedVertices;
	delete[] cycle;
	return NULL;
}

bool hasOddCycle(int **graph, int *usedVertices, int *cycle, int prevVertex, int currVertex, int destVertex, int cycleLenght){
	for(int i=0;i<NUMBER_OF_NEIGHBOURS;++i){
		int tmpVertex = graph[currVertex][i];
		if(tmpVertex == destVertex && cycleLenght % 2 == 1){
			return true;
		}
		if(usedVertices[tmpVertex] == 0){
			cycle[tmpVertex]=1;
			usedVertices[tmpVertex]=1;
			if(hasOddCycle(graph,usedVertices,cycle, currVertex, tmpVertex, destVertex, cycleLenght+1)){
				return true;
			} else {
				cycle[tmpVertex]=0;
				usedVertices[tmpVertex]=0;
			}
		}
	}
	return false;
}
