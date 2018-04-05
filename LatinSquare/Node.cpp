#include "stdafx.h"
#include "Node.h"


Node::Node() {
}

Node::Node(int number) {
	numberOfElements = number;
	for (int i = 1; i <= numberOfElements; i++) {
		arrayDomain[i-1] = i;
		domainStatus[i-1] = true;
		myDeletedValues[i-1] = false;
	}

	for (int i = 0; i < MAX_NEIGHBOURS_NUMBER; i++) {
		for (int j = 0; j < N; j++) {
			neighboursDeletedValues[i][j] = false;
		}
	}

	isAssigned = false;
	currentValue = 0;
	neighboursCount = 0;
}

void Node::addNeighbourArray(Node *node) {
	neighboursArray[neighboursCount++] = node;
}

bool Node::findNextValueArray() {
	while (currentIndex < numberOfElements) {
		if (setNextValueArray()) {
			isAssigned = true;
			return true;
		}
	}
	return false;
}

bool Node::setNextValueArray() {
	currentValue = arrayDomain[currentIndex++];
	return checkConstraints();
}

void Node::setDefaultDomainArray() {
	currentValue = 0;
	isAssigned = false;
	currentIndex = 0;
}

bool Node::checkConstraints() {
	for (int i = 0; i < neighboursCount; i++) {
		if (neighboursArray[i]->currentValue == currentValue) {
			return false;
		}
	}
	return true;
}

bool Node::checkForward() {
	while (assignUnusedValueFC()) {
		isAssigned = true;
		if (modifyNeighboursDomain()) {
			//cout << "Modify true" << endl;
			return true;
		} else {
			//cout << "Modify false" << endl;
		}
	}
	return false;
}

void Node::restoreMyDomain() {
	isAssigned = false;
	currentValue = -1;
	for (int i = 0; i < N; i++) {
		if (myDeletedValues[i]) {
			domainStatus[i] = true;
		}
	}
}

bool Node::assignUnusedValueFC() {
	for (int i = 0; i < N; i++) {
		if (domainStatus[i]) {
			//cout << "Przydzielam wartosc: " << i  << endl;
			restoreNeighboursDomain();
			domainStatus[i] = false;
			currentValue = i;
			myDeletedValues[currentValue] = true;
			isAssigned = true;
			return true;
		}
	}
	return false;
}

bool Node::modifyNeighboursDomain() {
	for (int i = 0; i < neighboursCount; i++) {
		if (!neighboursArray[i]->isAssigned) {
			if (neighboursArray[i]->domainStatus[currentValue]) {
				neighboursArray[i]->domainStatus[currentValue] = false;
				neighboursDeletedValues[i][currentValue] = true;
				neighboursStatus[i] = true;
			}
			if (neighboursArray[i]->isDomainEmpty()) {
				//cout << "Zwykly: " << i << endl;
				return false;
			}
		}
	}
	return true;
}

bool Node::isDomainEmpty() {
	for (int i = 0; i < N; i++) {
		if (domainStatus[i]) {
			return false;
		}
	}
	return true;
}

void Node::restoreNeighboursDomain() {
	/*cout << "Zmodyfikowani: " << endl;
	for (int i = 0; i < neighboursCount + diagonalNeighboursCount; i++) {
	for (int j = 0; j < COLORS_NUMBER; j++) {
	cout << neighboursDeletedValues[i][j] << " ";
	}
	cout << endl;

	}
	cout << "Koniec" << endl;*/
	for (int i = 0; i < neighboursCount; i++) {
		if (neighboursStatus[i]) {
			for (int j = 0; j < N; j++) {
				if (neighboursDeletedValues[i][j]) {
					neighboursDeletedValues[i][j] = false;
					for (int j = 0; j < N; j++) {
						neighboursArray[i]->myDeletedValues[j] = false;
					}
					neighboursArray[i]->domainStatus[j] = true;
					
				}
			}
		}
	}
}

Node::~Node() {

}
