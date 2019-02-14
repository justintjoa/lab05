#include <iostream>
#include <cstring>
#include <sstream>
#include "table.h"

using namespace std;


Table::Table(unsigned int max_entries) {
	numentries = max_entries;
	p1 = new bucket[max_entries];
}           

Table::Table(unsigned int entries, std::istream& input) {
	numentries = entries;
	p1 = new bucket[numentries];
	for (int i = 0; i < entries; i++) {   
		Entry e;
  		input >> e;
		int a;
		a = (e.get_key())%numentries;
		((p1[a]).arr).push_back(e);
		((p1[a]).size)++;
	}
}

bool Table::remove(unsigned int key) {
        int a;
        a = key%numentries;
        bucket* p2; 
        p2 = &(p1[a]);
        for (int i = 0; i < ((p2)->size); i++) {
                if (((p2->arr).at(i)).get_key() != key) {
                        continue;
                }   
                else {
                        (p2->arr).erase((p2->arr).begin() + i); 
                        ((p2)->size)--;
			return true;
                }
        }
        return false;
}


void Table::put(unsigned int key, std::string data) {
	remove(key);	
	Entry e;
	e.set_key(key);
	e.set_data(data);
	int a;
	a = key%numentries;
	((p1[a]).arr).push_back(e);
        ((p1[a]).size)++;
}

void Table::put(Entry e) {
	int a;
	a = e.get_key();
	remove(a);
	int b;
	b = (a)%numentries;
	((p1[b]).arr).push_back(e);
        ((p1[b]).size)++;
}

std::string Table::get(unsigned int key) const {
	std::ostringstream oss;
	int a;
	a = key%numentries;
	bucket* p2;
	p2 = &(p1[a]);
  	for (int i = 0; i < ((p2)->size); i++) {
		if (((p2->arr).at(i)).get_key() != key) {
			continue;
		}
		else {
	
			oss <<  (((p2)->arr).at(i)).get_data(); 
  		}
	}
	return oss.str();
}

int Table::returnsize() const {
	return numentries;
}
Entry Table::returnentry(int key) const {
	int a;
	a = key%numentries;
	bucket* p2;
	p2 = &(p1[a]);
	  for (int i = 0; i < ((p2)->size); i++) {
                if (((p2->arr).at(i)).get_key() != key) {
                        continue;
                }
                else {
                	return ((p2)->arr).at(i);
		}
        }
}

bucket* Table::returnbuck(int index) const {
	return &(p1[index]);
}

void merge(Entry a[], size_t leftArraySize, size_t rightArraySize) {
	// Note: we are assuming the left and right sub arrays are sorted
	Entry* tempArray;		// tempArray to hold sorted elements
	size_t copied = 0; 	// num elements copied to tempArray
	size_t leftCopied = 0;	// num elements copied from leftArray
	size_t rightCopied = 0;	// num elements copied from rightArray

	// create temp array
	tempArray = new Entry[leftArraySize + rightArraySize];

	// merge left and right arrays into temp in sorted order
	while ((leftCopied < leftArraySize) && (rightCopied < rightArraySize)) {
		if ((a[leftCopied]).get_key() < ((a + leftArraySize)[rightCopied]).get_key()) {
			tempArray[copied++] = a[leftCopied++];
			/*
			int alpha = (a[leftCopied]).get_key();
			string beta = (a[leftCopied]).get_data();
			(tempArray[copied]).set_key(alpha);
			(tempArray[copied]).set_data(beta);
			copied++;
			leftCopied++;
			*/
		} else {
			tempArray[copied++] = (a + leftArraySize)[rightCopied++];
			/*
			 int alpha = (a + leftArraySize)[rightCopied].get_key();
                        string beta = ((a + leftArraySize)[rightCopied]).get_data();
                        (tempArray[copied]).set_key(alpha);
                        (tempArray[copied]).set_data(beta);
                        copied++;
                        rightCopied++;
			*/
		}
	}

	// copy remaining elements from left/right sub arrays into tempArray

	// if elements in leftArray still exist, then ...
	while (leftCopied < leftArraySize) {
		  tempArray[copied++] = a[leftCopied++]; 
		//int alpha = (a[leftCopied]).get_key();
                   //string beta = (a[leftCopied]).get_data();
                   //(tempArray[copied]).set_key(alpha);
                   //(tempArray[copied]).set_data(beta);
                   //copied++;
                   //leftCopied++;
	}


	// if elements in rightArray still exist, then ...
	while (rightCopied < rightArraySize) {
		tempArray[copied++] = (a + leftArraySize)[rightCopied++];
		/*
		int alpha = (a + leftArraySize)[rightCopied].get_key();
                string beta = ((a + leftArraySize)[rightCopied]).get_data();
                (tempArray[copied]).set_key(alpha);
                (tempArray[copied]).set_data(beta);
                copied++;
                rightCopied++;
		*/
	}
	// Replace the sorted values into the original array
	for (int i = 0; i < leftArraySize + rightArraySize; i++) {
		a[i] = tempArray[i];
		//int alpha = ((tempArray)[i]).get_key();
		//string beta = ((tempArray)[i]).get_data();
                //(a[i]).set_key(alpha);
                //(a[i]).set_data(beta);
	}

	// free up memory
	delete [] tempArray;
}


void mergesort(Entry a[], size_t size) {
	size_t leftArraySize;
	size_t rightArraySize;
	//cout << "R1" << (a[0]).get_key() << endl;
	if (size > 1) {
		leftArraySize = size / 2;
		rightArraySize = size - leftArraySize;
	
		// call mergesort on left array
		mergesort(a, leftArraySize); 
		//cout << "R2" << (a[0]).get_key() << endl;	
		// call mergesort on right array
		mergesort((a + leftArraySize), rightArraySize);
		//cout << "R3" << (a[0]).get_key() << endl;
		// left and right sorted arrays together
		merge(a, leftArraySize, rightArraySize);
		//cout << "R4" << (a[0]).get_key() << endl;
	}
	
}


std::ostream& operator<< (std::ostream& out, const Table& t) {
	int k;
	k = 0;
	for (int a = 0; a < (t.returnsize()); a++) {
		k = k + (t.returnbuck(a))->size;
	}
	Entry array[k];
	k = 0;
	for (int i = 0; i < t.returnsize(); i++) {
		for (int j = 0; j < (t.returnbuck(i))->arr.size(); j++) {
			unsigned int alpha;
			string beta;
			alpha = ((t.returnbuck(i))->arr.at(j)).get_key();
			beta = ((t.returnbuck(i))->arr.at(j)).get_data();
			(array[k]).set_key(alpha);
			(array[k]).set_data(beta);		
			k++;
		}
	}
	mergesort(array, k);
	for (int i = 0; i < k; i++) {
		out << (array[i]) << "\n";
	}
	return out;
}

Table::~Table() {
	int a;
	a = numentries;
	for (int i = 0; i < a; i++) {
		 for (int j = 0; j < (p1[i]).size; j++) {
			((p1[i]).arr).clear();
                        ((p1[i]).size) = 0;
                }  
		numentries--;
	}
	delete [] p1;
}

Table& Table::operator=(const Table& input) {
	this->~Table();
	int size;
	size = input.returnsize();
	numentries = size;
	p1 = new bucket[size];
	for (int i = 0; i < size; i++) {
		((p1[i]).arr).resize((input.returnbuck(i))->size);
		for (int j = 0; j < (input.returnbuck(i))->size; j++) {
			((p1[i]).arr).at(j) = ((input.returnbuck(i))->arr).at(j);
			(p1[i]).size++;
		}
	}
	return (*this);
}

Table::Table(const Table& input) {
	int size;
        size = input.returnsize();
	numentries = size;
        p1 = new bucket[size];
        for (int i = 0; i < size; i++) {
                ((p1[i]).arr).resize((input.returnbuck(i))->size);
		for (int j = 0; j < (input.returnbuck(i))->size; j++) {
                        ((p1[i]).arr).at(j) = ((input.returnbuck(i))->arr).at(j);
                        (p1[i]).size++;
                }   
        }
} 
