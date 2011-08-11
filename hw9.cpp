// Name: Anthony T. Pham
// UF ID: 5038-1111
// Discussion section #: 1079

#include<iostream>
#include<fstream>
#include "hw9.h"

using namespace std;

// overload >> operator
template<class T>
istream& operator>>(istream& in, multistageGraph<T>& x)
{
	int weight, v1, v2;
	// read in the number of vertices
	in >> x.numVertices;
	// create space for adjacency list
	x.adjacencyList = new vertex<T>*[x.numVertices + 1];
	// initialize pointers to null
	for(int i = 0; i < x.numVertices + 1; i++)
	{
		x.adjacencyList[i] = NULL;
	}
	// set the number of edges
	x.numEdges = 15;
	// set the number of stages
	x.numStages = 5;
	// read in the edges into the adjacency list
	for(int i = 0; i < x.numEdges; i++)
	{
		in >> v1 >> v2 >> weight;
		// add in v2 as adjacent vertex of v1
		if(x.adjacencyList[v1] == NULL)
		{
			x.adjacencyList[v1] = new vertex<T>(v2, weight);
		}
		else
		{
			vertex<T> *vChain = x.adjacencyList[v1];
			vertex<T> *newV = new vertex<T>(v2, weight, vChain);
			x.adjacencyList[v1] = newV;
		}
	}

	for(int i = 0; i < x.numVertices + 1; i++)
	{
		for(vertex<T> *u = x.adjacencyList[i] ; u != NULL; u = u->next)
		{
			cout << u->vertexLabel << " ";
		}
		cout << endl;
	}
	cout << endl;
	return in;
}

// overload << operator
template<class T>
ostream& operator<<(ostream& out, multistageGraph<T>& x)
{
	// print forward approach shortest path
	int* pathForward = x.forwardApproachPath();
	for(int i = 1; i < x.numStages; i++)
	{
		out << pathForward[i] << "-";
	}
	out << pathForward[x.numStages] << endl;

	// print backward approach shortest parth
	int* pathBackward = x.backwardApproachPath();
	for(int i = 1; i < x.numStages; i++)
	{
		out << pathBackward[i] << "-";
	}
	out << pathBackward[x.numStages] << endl;

	// free memory
	delete [] pathForward;
	delete [] pathBackward;
	return out;
}
int main()
{
	// variable declarations and file streams
	multistageGraph<int> x;
	ifstream inFile;
	inFile.open("hw9.in");
	ofstream outFile("hw9.out");

	// read in multistage graph
	inFile >> x;

	// output multistage graph to file
	outFile << x;

	// free memory
	x.~multistageGraph();

	cout << "Writing to file complete." << endl;

	// close file streams
	inFile.close();
	outFile.close();

	return 0;
}
