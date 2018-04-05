#pragma once
#include <vector>
#include <iostream>
#include <algorithm>
#include <random>
#include <array>

using namespace std;
class Node {
public:
	Node();
	Node(int number);

	static const int N = 4;
	static const int MAX_NEIGHBOURS_NUMBER = N*N;

	int currentValue;
	bool checkConstraints();
	bool setNextValueArray();
	void setDefaultDomainArray();
	bool findNextValueArray();
	void addNeighbourArray(Node *node);

	//forward-checking
	bool domainStatus[N];
	bool checkForward();
	void restoreMyDomain();
	void restoreNeighboursDomain();

	~Node();
private:
	bool isAssigned;
	int arrayDomain[N];
	int arrayDefaultDomain[N];
	Node* neighboursArray[MAX_NEIGHBOURS_NUMBER];
	int currentIndex;
	int neighboursCount;
	int numberOfElements;

	//forward-checking
	//bool domainStatus[COLORS_NUMBER];
	bool neighboursStatus[MAX_NEIGHBOURS_NUMBER];
	int neighboursDeletedValues[MAX_NEIGHBOURS_NUMBER][N];
	bool myDeletedValues[N];
	bool assignUnusedValueFC();
	bool modifyNeighboursDomain();
	bool isDomainEmpty();
};

