//#include <cppunit>

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