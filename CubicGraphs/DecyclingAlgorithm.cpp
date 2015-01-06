#include <math.h>
#include <deque>
#include "DecyclingAlgorithm.h"

int numberOfVertices;

bool decyclingAlogorithm(int **graph, int *independentSet, int _numberOfVertices){
	numberOfVertices = _numberOfVertices;
	int *freeAndPseudoFreeVertices = new int[numberOfVertices];
	int *cycle = new int[numberOfVertices];
	int *newIndependentSet = new int[numberOfVertices];
	for(int i=0;i<numberOfVertices;++i){
		freeAndPseudoFreeVertices[i]=VertexFreedom::NOT_FREE_VERTEX;
	}
	if(findCycle(cycle,graph,independentSet)==false){
		return true;
	}
	bool solutionFound=false;
	for(int i=0;i<numberOfVertices;++i){
		int degree = 0;
		if(cycle[i]==1){
			for(int j=0;j<NUMBER_OF_NEIGHBOURS;++j){
				if(independentSet[graph[i][j]]==0)++degree;
			}
			if(degree>=NUMBER_OF_NEIGHBOURS){
				independentSet[i] = 1;
				solutionFound = true;
			}
		}
	}
	if(solutionFound==false){
		findFreeVertices(graph, independentSet, freeAndPseudoFreeVertices);
		findPseudoFreeVerticles(graph, independentSet, freeAndPseudoFreeVertices);

		bool deletedCycle = false;
		std::list<int> *path;
		path = createPath(graph, cycle, independentSet, freeAndPseudoFreeVertices); // TO DO

		int in=0;
		int out = alternatingPath(path, independentSet, graph, in);
			
		createNewIndependentSet(path, freeAndPseudoFreeVertices, independentSet, newIndependentSet, graph, in, out);
		while(!deletedCycle){
			for(int i=0;i<numberOfVertices;++i){
				independentSet[i] = newIndependentSet[i];
			}
			in = out;
			deletedCycle = nonAlternatingPath(in, out, path, freeAndPseudoFreeVertices, independentSet, newIndependentSet, graph);
		}
	}
	//delete path
	return false;
}
/*
std::list<int> * createPath(int **graph, int *cycle, int *independentSet, int *freeAndPseudoFreeVertices){
	std::list<int> *path = new std::list<int>();
	int *usedVertices = new int[numberOfVertices];
	for( int i=0;i<numberOfVertices;++i){
		usedVertices[i]=0;
	}
	bool solutionFound=false;
	for( int i=0;i<numberOfVertices;++i){
		if(cycle[i]==1){
			std::queue<std::list<int>* > Q;
			std::list<int> *firstPath = new std::list<int>();
			usedVertices[cycle[i]]=1;
			firstPath->push_back(cycle[i]);
			Q.push(firstPath);
			int usedVerticesNumber=1;
			while(usedVerticesNumber<numberOfVertices){
				path = Q.front();
				Q.pop();
				for(int i=0;i<NUMBER_OF_NEIGHBOURS;++i){
					int vertex = graph[path->back()][i];
					if(freeAndPseudoFreeVertices[vertex]==1){
						solutionFound=true;
						while(!Q.empty()){
							delete Q.front();
							Q.pop();
						}
					} else if(usedVertices[vertex]==0){
						usedVertices[vertex] = 1;
						std::list<int> *newPath = new std::list<int>(path->begin(),path->end());
						newPath->push_back(vertex);
						Q.push(newPath);
					}
				}
				delete path;
			}
			if(solutionFound==true){
				break;
			}
		}
	}
	return path;
}*/
std::list<int> * createPath(int **graph, int *cycle, int *independentSet, int *freeAndPseudoFreeVertices){
	std::list<int> *path = new std::list<int>();
	int *usedVertices = new int[numberOfVertices];
	for( int i=0;i<numberOfVertices;++i){
		usedVertices[i]=0;
	}
	for( int i=0;i<numberOfVertices;++i){
		if(cycle[i]==1){
			if(findPathToFreeVerticle(graph, freeAndPseudoFreeVertices, path, usedVertices, i)){
				return path;
			}
		}
	}
	return path;
}
bool findPathToFreeVerticle(int **graph, int *freeAndPseudoFreeVertices, std::list<int> *path, int *usedVertices, int vertex){
	path->push_back(vertex);
	for(int i=0;i<NUMBER_OF_NEIGHBOURS;++i){
		int neighbour = graph[vertex][i];
		if(usedVertices[neighbour]==0){
			if(freeAndPseudoFreeVertices[neighbour]==0){
				if(findPathToFreeVerticle(graph, freeAndPseudoFreeVertices, path, usedVertices, neighbour)){
					return true;
				}
			} else {
				if(path->size()>1){
					path->push_back(neighbour);
					return true;
				}
			}
		}
	}
	usedVertices[vertex]=1;
	path->pop_back();
	return false;
}

bool findIfCycle(int **graph, int *independentSet,int destinationVertex,int *usedVertices,int currentVertex){
	const int NOT_IN_PATH=0;
	const int IN_PATH=1;
	usedVertices[currentVertex]=IN_PATH;
	for(int j=0;j<NUMBER_OF_NEIGHBOURS;++j){
		if(graph[currentVertex][j]==destinationVertex)return true;
		if(independentSet[currentVertex]==0&&usedVertices[j]==NOT_IN_PATH){
			if(findIfCycle(graph,independentSet,destinationVertex,usedVertices,j)==true)return true;
			usedVertices[j]=NOT_IN_PATH;
		}
	}
	return false;
}

void findFreeVertices(int **graph, int *independentSet,int *freeAndPseudoFreeVertices){
	const int NOT_IN_PATH=0;
	const int IN_PATH=1;
	int *usedVertices;
	usedVertices = new int[numberOfVertices];
	for(int i=0;i<numberOfVertices;++i){
		if(independentSet[i]==1){
			for(int j=0;j<NUMBER_OF_NEIGHBOURS;++j){
				for(int k=0;k<numberOfVertices;++k){
					usedVertices[k] = NOT_IN_PATH;
				}
				if(!findIfCycle(graph,independentSet,(j+1)%NUMBER_OF_NEIGHBOURS,usedVertices,j)){
					freeAndPseudoFreeVertices[i]=VertexFreedom::FREE_VERTEX;
				}
			}
		}
	}
	delete []usedVertices;
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

int alternatingPath(std::list<int> *path, int *independentSet, int**graph,int num){
	std::list<int>::iterator it=path->begin();
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
			break;
		}
		++num;
		++it;
		int independentNeighbours=0;
		for(int k=0;k<NUMBER_OF_NEIGHBOURS;++k){
			if(independentSet[graph[*it][k]]==1)++independentNeighbours;
		}
		if(independentSet[independentNeighbours]==NUMBER_OF_NEIGHBOURS)break;
	}
	return num;
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
	int * cycle=new int[numberOfVertices];
	findCycle(cycle,graph,independentSet);
	int numOfNeighbours;
	int i=0;
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
	if(numOfNeighbours==NUMBER_OF_NEIGHBOURS){
		independentSet[i]=1;
		out = (int)distance(path->begin(),path->end());
		deletedCycle = true;  
	}else{
		std::list<int>::iterator it = std::next(path->begin(),in+1);
		while(it!=path->end()){
			if(cycle[*it]==0){
				break;
			}else{
				++it;
			}
		}
		int i=*it;
		if(independentSet[i]==1){
			out = std::distance(path->begin(),it)-1;
			for(int i=0;i<numberOfVertices;++i){
				newIndependentSet[i] = independentSet[i];
			}
			deletedCycle = false; 
		}else{
			std::list<int> tmpPath(next(path->begin(),in+1),path->end());
			setIndependentSet(tmpPath,freeAndPseudoFreeVertices, independentSet, newIndependentSet,graph);
			out = i;
		}
	}
	delete cycle;
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

bool findCycle(int *cycle, int **graph,int *independentSet){
	int *checkedVertices=new int(numberOfVertices);
	for(int i=0;i<numberOfVertices;++i){
		checkedVertices[i]=independentSet[i];
		cycle[i]=0;
	}
	std::deque<int> *verticeStack = new std::deque<int>();
	for(int i=0;i<numberOfVertices;++i){
		if(checkedVertices[i]==0){
			if(hasCycle(graph,independentSet,verticeStack,checkedVertices,cycle,i)){
				//delete checkedVertices;
				return true;
			}
		}
	}
	//delete checkedVertices;
	return false;
}

bool hasCycle(int **graph,int *independentSet, std::deque<int> *verticeStack, int *checkedVertices, int *cycle, int vertex){
	verticeStack->push_back(vertex);
	for(int i=0;i<NUMBER_OF_NEIGHBOURS;++i){
		int neighbour = graph[vertex][i];
		std::deque<int>::iterator it=std::find(verticeStack->begin(), verticeStack->end(), neighbour);
		int distance = std::distance(it,verticeStack->end());
		if(distance>2){
			for(;it!=verticeStack->end();++it){
				cycle[*it]=1;
			}
			return true;
		}
		if(independentSet[neighbour]==0&&checkedVertices[neighbour]==0&&distance!=2){
			if(hasCycle(graph, independentSet, verticeStack, checkedVertices, cycle, neighbour)){
				return true;
			}
		}
	}
	checkedVertices[vertex]=1;
	verticeStack->pop_back();
	return false;
}
