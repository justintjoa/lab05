//
//  table.h
//  W19 - Lab04
//
#ifndef table_h
#define table_h
#include <iostream>
#include "entry.h"
#include <vector>

using namespace std;

  struct bucket {
        vector<Entry> arr;
        int size = 0;
   };

void merge(int a[], size_t leftArraySize, size_t rightArraySize);

void mergesort(int a[], size_t size);

class Table {
public:
	Table(unsigned int max_entries = 100);
	Table(unsigned int entries, std::istream& input);
	void put(unsigned int key, std::string data);
	void put(Entry e);
	std::string get(unsigned int key) const;
	bool remove(unsigned int key);
	friend std::ostream& operator<< (std::ostream& out,const Table& t);
	int returnsize() const;
	Entry returnentry(int key) const;
	bucket* returnbuck(int index) const;
	Table& operator=(const Table& input);
	Table(const Table& input);
	~Table();

private:
	int numentries;
	bucket* p1;

};

#endif /* table_h */
