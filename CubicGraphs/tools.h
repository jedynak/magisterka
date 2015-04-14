
	static const int NUMBER_OF_NEIGHBOURS=3;
	static const int BASE_SIZE=4;

	//these consts you can change
	static const int MIN_VERTEX_NUMBER=10;
	static const int MAX_VERTEX_NUMBER=120;
	static const int NUMBER_OF_GRAPH=1000000;
	static const int INCREASE_NUMBER_OF_VERTICES=10;

	void deleteSet(int **graph, int **limitedGraph, int numberOfVertices, int *solution);
	void printGraph(int **graph, int numberOfVertices, int *solution);
	/*
	graph[0][0]=4;
	graph[0][1]=6;
	graph[0][2]=5;
	graph[1][0]=5;
	graph[1][1]=9;
	graph[1][2]=3;
	graph[2][0]=5;
	graph[2][1]=7;
	graph[2][2]=8;
	graph[3][0]=1;
	graph[3][1]=9;
	graph[3][2]=4;
	graph[4][0]=0;
	graph[4][1]=9;
	graph[4][2]=3;
	graph[5][0]=0;
	graph[5][1]=1;
	graph[5][2]=2;
	graph[6][0]=0;
	graph[6][1]=7;
	graph[6][2]=8;
	graph[7][0]=2;
	graph[7][1]=6;
	graph[7][2]=8;
	graph[8][0]=2;
	graph[8][1]=7;
	graph[8][2]=6;
	graph[9][0]=1;
	graph[9][1]=3;
	graph[9][2]=4;
	*/