// LatinSquare.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Node.h"
#include <chrono>
#include <ctime>

using namespace std;

const int N = 4;
Node* graph[N][N];
Node* list[N*N];
long results = 0;
int backs = 0;

void deleteGraph() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (graph[i][j] != nullptr) {
				delete(graph[i][j]);
			}
		}
	}
}

void initializeGraph() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			Node *node = new Node(N);
			graph[i][j] = node;
			list[i*N + j] = node;
		}
	}
}

void addNeighbours() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			for (int k = 0; k < N; k++) {
				if (i != k) {
					graph[i][j]->addNeighbourArray(graph[k][j]);
				}
				if (j != k) {
					graph[i][j]->addNeighbourArray(graph[i][k]);
				}
			}
		}
	}
}

void printGraph() {
	cout << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << graph[i][j]->currentValue << " ";
		}
		cout << endl;
	}
}

void backtracking() {
	int i = 0;
	while (i < N*N) {
		//cout << endl << "Jestem: " << i << endl;
		if (!list[i]->findNextValueArray()) {
			if (i == 0) return;
			list[i]->setDefaultDomainArray();
			//backs++;
			i = i - 1;
		} else {
			i = i + 1;
		}
		//cout << "\r" << backs;
		//printGraph();
		//cout << "Bede: " << i << endl;
		if (i == N * N) {
			results++;
			//cout << "Znalezionych rozwiazan: " << results << endl;
			//printGraph();
			list[i - 1]->setDefaultDomainArray();
			i = i - 2;
			backs = 0;
		}
	}
}

void printAllDomains() {
	cout << "Domeny:" << endl;
	for (int i = 0; i < N * N; i++) {
		for (int j = 0; j < Node::N; j++) {
			cout << list[i]->domainStatus[j] << " ";
		}
		cout << endl;
	}
}

void forwardChecking() {
	int i = 0;
	while (i < N*N) {
		//cout << endl << i << endl;
		//printAllDomains();
		if (!list[i]->checkForward()) {
			if (i == 0) return;
			list[i]->restoreMyDomain();
			list[i]->restoreNeighboursDomain();
			backs++;
			i = i - 1;
			//printGraph();
			//cout << "Powrot" << endl;
		} else {
			i = i + 1;
			//printGraph();
			//cout << "Bez powrotu" << endl;
		}
		//printAllDomains();
		if (i == N * N) {
			//cout << "Rozwiazanie: " << results << endl;
			//printGraph();
			list[i - 1]->restoreMyDomain();
			list[i - 1]->restoreNeighboursDomain();
			i = i - 2;
			backs = 0;
			results++;
			//printAllDomains();
		}
	}
}

int main() {

	initializeGraph();
	addNeighbours();
	long ms = chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now().time_since_epoch()).count();

	//backtracking();
	forwardChecking();
	cout << "\nCzas: " << chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now().time_since_epoch()).count() - ms << "ms" << " Rozwiazan: " << results << endl;

	//printGraph();
	//deleteGraph();
	return 0;
}

