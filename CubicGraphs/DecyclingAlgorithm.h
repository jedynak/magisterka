#include <queue>
#include <list>
#include "tools.h"

extern int numberOfVertices;

enum VertexFreedom{
	NOT_FREE_VERTEX,
	PSEUDO_FREE_VERTEX_TYPE1,
	PSEUDO_FREE_VERTEX_TYPE2,
	FREE_VERTEX
};
bool isEqualNumberOfCycles(int **graph,int *independentSet,int *newIndependentSet);

bool decyclingAlogorithm(int **graph, int *independentSet);

std::list<int> * createPath(int **graph, int *cycle, int *independentSet, int *freeAndPseudoFreeVertices);

bool findIfCycle(int **graph, int *independentSet,int destinationVertex,int *usedVertices,int currentVertex);

void findFreeVertices(int **graph, int *independentSet,int *freeAndPseudoFreeVertices);

void findPseudoFreeVerticles(int **graph, int *independentSet,int *freeAndPseudoFreeVertices);

bool findOddCycle(int **graph, int *independentSet,int destinationVertex,int *usedVertices,int currentVertex,int length);

void findPseudoFreeVerticlesType1(int **graph, int *independentSet,int *freeAndPseudoFreeVertices, int indep1, int indep2, int notIndep1, int notIndep2);

void findPseudoFreeVerticlesType2(int **graph, int *independentSet,int *freeAndPseudoFreeVertices, int indep1, int indep2,int notIndep1, int notIndep2);

bool alternatingPath(std::list<int> *path, int *independentSet, int**graph,int num, int &out);

void createNewIndependentSet(std::list<int> *path,int* pseudoFreeVerticle, int *independentSet, int *newIndependentSet, int**graph,int in,int out);

bool nonAlternatingPath(int in,int &out,std::list<int> *path, int* freeAndPseudoFreeVertices, int *independentSet, int *newIndependentSet, int**graph);

void setIndependentSet(std::list<int> &path,int* freeAndPseudoFreeVertices, int *independentSet, int *newIndependentSet, int**graph);

bool hasOddCycle(int **graph, int *usedVertices, int *cycle, int prevVertex, int currVertex, int destVertex, int cycleLenght);

int* findCycle(int **graph,int *independentSet, int v1, int v2);

int *findAnyOddCycle(int **graph,int *independentSet);

bool findPathToFreeVerticle(int **graph, int *freeAndPseudoFreeVertices, std::list<int> *path, int *usedVertices, int vertex);