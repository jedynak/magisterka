#include <math.h>
#include <list>
#include <algorithm>
#include "BicubicScheduler.h"
#include "tools.h"

bool BicubicScheduler::colorVertex(int vertex, int fromVertex) {
	if ( toWhichSet[vertex] == NONE_SET ) {
		//color on other color than fromVertex
		if ( toWhichSet[fromVertex] == setNumber::FIRST_SET ) {
			toWhichSet[vertex] = setNumber::SECOND_SET;
		} else {
			toWhichSet[vertex] = setNumber::FIRST_SET;
		}
		for(int j=0;j<NUMBER_OF_NEIGHBOURS; ++j) {
			if(colorVertex(graph[vertex][j], vertex)==false) {
				return false;
			} 
		}
	} else {
		if (toWhichSet[vertex]==toWhichSet[fromVertex]) {
			return false;
		}
	}
	return true;
}

bool BicubicScheduler::findBicoloring() {
	toWhichSet[0]=FIRST_SET;
	for(int j=0;j<NUMBER_OF_NEIGHBOURS; ++j) {
		int tmpVertex = graph[0][j];
		if(colorVertex(tmpVertex, 0) == false) { 
			return false;
		}
	}
	return true;
}

int BicubicScheduler::findTripleConnection(enum setNumber fromVertex, enum setNumber toVertex){

	for (int i=0; i<numberOfVertices;++i){
		if(toWhichSet[i] == fromVertex){
			int counter = 0;
			for(int j=0;j<NUMBER_OF_NEIGHBOURS; ++j) {
				if( toWhichSet[ graph[i][j] ] == toVertex ){
					++counter;
				}
			}
			if (counter == NUMBER_OF_NEIGHBOURS) {
				return i;
			}
		}
	}
	return -1; // not found
}

void BicubicScheduler::reColorVertex(int vertex, int *verticesToBeColored) {
	verticesToBeColored[vertex] = 1;
	if(toWhichSet[vertex] == FIRST_SET){
		toWhichSet[vertex] = THIRD_SET;
	} else {
		toWhichSet[vertex] = FIRST_SET;
	}
	for(int j=0;j<NUMBER_OF_NEIGHBOURS; ++j) {
		int tmpVertex = graph[vertex][j];
		if(verticesToBeColored[ tmpVertex ] == 0) {
			reColorVertex(tmpVertex, verticesToBeColored);
		}
	}
}

void BicubicScheduler::changeColors(int vertex) {
	int *verticesToBeColored = new int[numberOfVertices];
	for(int i=0;i<numberOfVertices;++i){
		if(toWhichSet[i] == SECOND_SET) {
			verticesToBeColored[i] = 1;
		} else {
			verticesToBeColored[i] = 0;
		}
	}
	reColorVertex(vertex, verticesToBeColored);
	delete verticesToBeColored;
}

void BicubicScheduler::calculateSizes(int *usedVertices, int sizeA, int sizeC, int vertex) {
	if(toWhichSet[vertex] == FIRST_SET) {
		++sizeA;
	} else {
		++sizeC;
	}
	for(int j=0;j<NUMBER_OF_NEIGHBOURS; ++j) {
		int tmpVertex = graph[vertex][j];
		if(usedVertices[ tmpVertex ] == 0) {
			calculateSizes(usedVertices, sizeA, sizeC, tmpVertex);
		}
	}

}

bool BicubicScheduler::canBeChanged(int *usedVertices, int vertex) {
	 int setASize = 0;
	 int setCSize = 0;
	 calculateSizes(usedVertices, setASize, setCSize, vertex);
	 if (setASize == setCSize + 1) {
		 return true;
	 }
	 return false;
}

void BicubicScheduler::changeSubsetAWithSubsetC(){
	int *usedVertices = new int[numberOfVertices];
	for(int i=0;i<numberOfVertices;++i){
		if(toWhichSet[i] == SECOND_SET) {
			usedVertices[i] = 1;
		} else {
			usedVertices[i] = 0;
		}
	}
	for(int i=0;i<numberOfVertices;++i){
		if(usedVertices[i] == 0) {
			if(canBeChanged(usedVertices, i)) { 
				changeColors(i);
				return;
			}
		}
	}
	//throw exception
}

void BicubicScheduler::findAllC3Brelations(list<int> *realations) {
	for(int i=0;i<numberOfVertices;++i){
		if(toWhichSet[i] == FIRST_SET) {
			int counter = 0;
			for(int j=0;j<NUMBER_OF_NEIGHBOURS;++j){
				int tmpVertex = graph[i][j];
				if(toWhichSet[tmpVertex] == SECOND_SET ) {
					++counter;
				}
			}
			if(counter == NUMBER_OF_NEIGHBOURS) { 
				relations->insert(i);
			}
		}
	}
}



void BicubicScheduler::calculateSizesBC(int *usedVertices, int sizeB, int sizeC, int vertex) {
	if(toWhichSet[vertex] == SECOND_SET) {
		++sizeA;
	} else {
		++sizeC;
	}
	for(int j=0;j<NUMBER_OF_NEIGHBOURS; ++j) {
		int tmpVertex = graph[vertex][j];
		if(usedVertices[ tmpVertex ] == 0) {
			calculateSizes(usedVertices, sizeA, sizeC, tmpVertex);
		}
	}

}

void changeBprimCprim(list<int> *relations) {
	int *checkedVertices = new int[numberOfVertices];
	for(int i=0;i<numberOfVertices;++i) {
		if(toWhichSet[i] == FIRST_SET)
			checkedVertices[i] = 1;
		} else{
			checkedVertices[i] = 0;
		}
	}
	int setASize = 0;
	int setCSize = 0;
	for(int i=0; i<numberOfVertices; ++i) {
		if(checkedVertices[i] == 0) {
			calculateSizes(checkedVertices, setASize, setCSize, i);
			if (setASize - setCSize <= relations->size() + 1 && setASize > setCSize) {
				changeSubsets(FIRST_SET, THIRD_SET, i);
				for(int j=0;i<setASize - setCSize - 1; ++i) {
					toWhichSet[relations->at(i)] = FIRST_SET;
				}
				break;
			}
		} 
	}
	
	findComponentAB(relations->size());



}

void changeSubsets(enum setNumber firstSubset, enum setNumber secondSubset, int vertex) {
	int *usedVertices = new int[numberOfVertices];
	for(int i=0;i<numberOfVertices;++i) {
		if( usedVertices[i] != firstSubset && usedVertices[i] != secondSubset) {
			usedVertices[i] = 1;
		} else {
			usedVertices[i] = 0;
		}
	}
	changeSubsetsRecursion(usedVertices, firstSubset, secondSubset, vertex);
}

void changeSubsetsRecursion(int* usedVertices, enum setNumber firstSubset, enum setNumber secondSubset, int vertex) {
	usedVertices[vertex] = 1;
	for(int j=0;j<NUMBER_OF_NEIGHBOURS; ++j) {
		int tmpVertex = graph[vertex][j];
		if(usedVertices[ tmpVertex ] == 0) {
			changeSubsetsRecursion(usedVertices, firstSubset, secondSubset, tmpVertex);
		}
	}
}

int findA1B(){
	for (int i=0; i<numberOfVertices;++i){
		if(toWhichSet[i] == fromVertex){
			int counter = 0;
			for(int j=0;j<NUMBER_OF_NEIGHBOURS; ++j) {
				if( toWhichSet[ graph[i][j] ] == toVertex ){
					++counter;
				}
			}
			if (counter == 1) {
				return i;
			}
		}
	}
	return -1; // not found
}

bool inPrimGraph(vertex){
	if(toWhichVertex[vertex] == FIRST_SET ){
		int counterOfB = 0;
		for( int i=0; i<NUMBER_OF_NEIGHBOURS; ++i) {
			if(toWhichVertex[graph[vertex][i]] == FIRST_SET) {
				++counter;
			}
		}
		if(counter == NUMBER_OF_NEIGHBOURS) {
			++counterOfB;
		}
		if( counterOfB >= 2 ) { //if 2 neighbours are B3A
			return false;
		}
		return true;
	} else {
		int counter = 0;
		for( int i=0; i<NUMBER_OF_NEIGHBOURS; ++i) {
			if(toWhichVertex[graph[vertex][i]] == FIRST_SET) {
				++counter;
			}
		}
		if(counter == NUMBER_OF_NEIGHBOURS) {
			return false;
		}
		return true;
	}
}

void reversePath(int firstVertex) { 
	int *reversed = new int[numberOfVertices];
	for (int i=0; i<numberOfVertices;++i){
		reversed = 0;
	}
	int vertex;
	//choose first vertex from path
	for( int i=0; i<NUMBER_OF_NEIGHBOURS; ++i) {
		vertex = graph[firstVertex][i];
		if(inPrimGraph(vertex)) {
			break;
		}
	}
	int prevVertex
	do {
		prevVertex = vertex;

		for( int i=0; i<NUMBER_OF_NEIGHBOURS; ++i) {
			int tmpVertex = graph[vertex][i];
			if( reversed[tmpVertex] == 0 && inPrimGraph(tmpVertex)){
				vertex = tmpVertex;
			}
		}

		if( toWhichVertex[vertex] == FIRST_SET ){
			toWhichVertex[vertex] = SECOND_SET;
		} else {
			toWhichVertex[vertex] = FIRST_SET;
		}
	} while(prevVertex != vertex);

}

list<int> * findAllB3Arelations() {

}

int notAllNeighboursOfC3A(int B1, int B2, int C) {
	for( int i=0; i<NUMBER_OF_NEIGHBOURS; ++i) {
		for( int j=0; j<NUMBER_OF_NEIGHBOURS; ++j) {
			int tmpVertex = graph[B1][i];
			if(tmpVertex == graph[B2][j]) {
				bool isNeigbourOfC = false;
				for( int k=0; k<NUMBER_OF_NEIGHBOURS; ++k) {
					if(graph[C][k] == tmpVertex){
						isNeigbourOfC = true;
						break;
					}
				}
				if( isNeigbourOfC == false ){
					return tmpVertex;
				}
			}

		}
	}
	return -1;
}

void BicubicScheduler::useCLWmethod(int estimatedThirdSetSize, int currentThirdSetSize) {
	
	while(currentThirdSetSize < estimatedThirdSetSize) {
		int relation = findTripleConnection(FIRST_SET, SECOND_SET);//A3B
		if( relation > -1){
			toWhichSet[relation] = THIRD_SET;
		} else {
			int relation1 = findTripleConnection(THIRD_SET, FIRST_SET);//C3A
			if( relation1 == -1){
				changeSubsetAWithSubsetC();
			} else {
				int relation2 = findTripleConnection(SECOND_SET, FIRST_SET);//B3A
				if( relation2 == -1){
					list<int> *relations = new list<int>();
					findAllC3Brelations(relations);
					//do some more magic
					changeBprimCprim(relations);	// almost done
				} else {
					int relation3 = findTripleConnection(FIRST_SET, THIRD_SET);//A3C
					if( relation3 > -1){
						toWhichSet[relation2] = THIRD_SET;
						toWhichSet[relation3] = SECOND_SET;
					} else {
						int counter;
						int tmpVertex;
						int element = findAgreaterThanBSubsetWithoutA3B()
						if( element == -1) {
							changeSubsets(FIRST_SET,SECOND_SET, element);	// to check
							toWhichSet[relation2] = THIRD_SET;
						} else {
							int element2 = findA1B(relation2);
							if (element2 != -1) {
								toWhichSet[relation2] = THIRD_SET;
								toWhichSet[element2] = SECOND_SET;
							} else {
								list<int> *relations2 = findAllB3Arelations();
								//list<int> *relations3 = checkNumberOfCommonNeighbours(relations2.at(0),relations2.at(1));
								int foundNeighbour = -1;
								if(relations2.size > 1 && 
									(foundNeighbour = notAllNeighboursOfC3A(relations2->at(0), 
									relations2->at(1), relation1)) != -1) {
									
									toWhichSet[relations2->at(0)] = THIRD_SET;
									toWhichSet[relations2->at(1)] = THIRD_SET;
									toWhichSet[relation1] = SECOND_SET;
									toWhichSet[foundNeighbour] = SECOND_SET;
								} else {
									reversePath(relations2->at(1));
								}
								delete relations2;
							}
						}
					}
				}
			}
		}
		++currentThirdSetSize;
	}
}

void BicubicScheduler::splitOnTwoSubsets(int size) {
	for(int i=numberOfVertices-1; i>=0; ++i) {
		if(size>0 && toWhichSet[i] == SECOND_SET) {
			toWhichSet[i] = THIRD_SET;
			--size;
		}
	}
}
float BicubicScheduler::calcScheduling(float s1, float s2, float s3, int &a, int &b, int &c) {
	return std::max( a/s1, std::max( b/s2, c/s3));
}

void BicubicScheduler::swapSolution(int newA, int newB, int newC, int &a, int &b, int &c) {
	a = newA;
	b = newB;
	c = newC;
}

void BicubicScheduler::verifyOPT(float s1, float s2, float s3, int &a, int &b, int &c) {
	float speedSum = s1 + s2 + s3;
	float n1,n2,n3;
	int tmpA, tmpB, tmpC;
	n1 = numberOfVertices * s1 / speedSum;
	n2 = numberOfVertices * s2 / speedSum;
	n3 = numberOfVertices * s3 / speedSum;
	a = floor(n1);
	b = ceil(n2);
	c = numberOfVertices - a - b;
	float result = calcScheduling(s1, s2, s3, a, b, c);
	tmpA = floor(n1);
	tmpA = floor(n1);
	tmpC = numberOfVertices - a - b;
	float tmpResult = calcScheduling(s1, s2, s3, tmpA, tmpB, tmpC);
	if(tmpResult < result) {
		result = tmpResult;
		swapSolution(tmpA, tmpB, tmpC, a, b, c);
	}
	tmpA = ceil(n1);
	tmpA = floor(n2);
	tmpC = numberOfVertices - a - b;
	float tmpResult = calcScheduling(s1, s2, s3, tmpA, tmpB, tmpC);
	if(tmpResult < result) {
		result = tmpResult;
		swapSolution(tmpA, tmpB, tmpC, a, b, c);
	}
	tmpA = ceil(n1);
	tmpA = ceil(n2);
	tmpC = numberOfVertices - a - b;
	float tmpResult = calcScheduling(s1, s2, s3, tmpA, tmpB, tmpC);
	if(tmpResult < result) {
		result = tmpResult;
		swapSolution(tmpA, tmpB, tmpC, a, b, c);
	}
}

void BicubicScheduler::sortSpeeds(float &s1,float &s2, float &s3){
	if(s1 < s2) { 
		swap(s1,s2);
	}
	if(s1 < s3) { 
		swap(s1,s3);
	}
	if(s2 < s3) { 
		swap(s2,s3);
	}
}

bool BicubicScheduler::bicubicScheduling(float s1,float s2, float s3) {
	sortSpeeds(s1, s2, s3);
	if(findBicoloring() == false) {
		return false; // not bicubic graphh
	}
	if( s1 < s2 + s3) { 

		int a,b,c;
		verifyOPT(s1, s2, s3, a, b, c);

		splitOnTwoSubsets(numberOfVertices/2 - b);
		useCLWmethod(c, numberOfVertices/2 - b);

	} else {
		int size = ceil((numberOfVertices/2) *s2 / (float)(s1 + s3)); 
		size = numberOfVertices/2 - size;
		splitOnTwoSubsets(size);
		return true;
	}
}

BicubicScheduler::BicubicScheduler(int **_graph, int _numberOfVertices):
	graph(_graph), numberOfVertices(_numberOfVertices) {
		
	toWhichSet = new int[_numberOfVertices];
	std::fill_n(toWhichSet, _numberOfVertices, NONE_SET);
}
BicubicScheduler::~BicubicScheduler() {
	delete toWhichSet;
}