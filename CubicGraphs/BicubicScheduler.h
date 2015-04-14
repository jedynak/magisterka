
enum setNumber {
	NONE_SET,
	FIRST_SET,
	SECOND_SET,
	THIRD_SET
};

class BicubicScheduler {
private:
	int **graph;
	int numberOfVertices;
	int *toWhichSet;
	bool colorVertex(int vertex, int fromVertex);
	bool findBicoloring();
	int findTripleConnection(enum setNumber fromVertex, enum setNumber toVertex);
	void reColorVertex(int vertex, int *usedVertices);
	void changeColors(int vertex);
	void changeSubsetAWithSubsetC();
	void useCLWmethod(int estimatedThirdSetSize, int currentThirdSetSize);
	void splitOnTwoSubsets(int size);
	float calcScheduling(float s1, float s2, float s3, int &a, int &b, int &c);
	void swapSolution(int newA, int newB, int newC, int &a, int &b, int &c);
	void verifyOPT(float s1, float s2, float s3, int &a, int &b, int &c);
	bool canBeChanged(int *usedVertices, int vertex);
	void calculateSizes(int *usedVertices, int sizeA, int sizeC, int vertex);

public:
	BicubicScheduler(int **_graph, int _numberOfVertices);
	~BicubicScheduler();
	bool bicubicScheduling(float s1,float s2, float s3);

};