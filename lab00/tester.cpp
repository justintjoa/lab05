#include <iostream>
#include "arrayFuncs.h"
using namespace std;
int main () {

	int* p1;
	p1 = new int[5];
	p1[0] = 1;
	p1[1] = 4;
	p1[2] = 1;
	p1[3] = 2;
	p1[4] = 3;
	cout << indexOfMax(p1, 5) << endl;
	cout << indexOfMin(p1, 5) << endl;
	return 0;
}
	
