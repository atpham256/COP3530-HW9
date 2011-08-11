// Name: Anthony T. Pham
// UF ID: 5038-1111
// Discussion section #: 1079

#ifndef HW9_H
#define HW9_H

#include <iostream>
#include <utility>
#include <queue>
#include <stack>
#include "vertex.h"

using namespace std;
template<class T>
class multistageGraph
{
	public:
		// constructors
		multistageGraph()
		{

		}

		// methods
		int* forwardApproachPath();
		int* backwardApproachPath();
		// destructor
		~multistageGraph()
		{
			// free memory at each index
			for(int i = 0; i < numVertices - 1; i++)
			{
				//if( adjacencyList[i] != NULL )
				delete [] adjacencyList[i];
			}
			// free the rest of the array
			//delete [] adjacencyList;
		}

		// data members
		int numEdges, numVertices, numStages;
		vertex<T> **adjacencyList;
};

// Method to compute the shortest path using dynamic programming and the forward approach
template<class T>
int* multistageGraph<T>::forwardApproachPath()
{
	int* pForward = new int[numStages + 1];
	int previousVertex[numVertices + 1], cost[numVertices + 1];
	// initialize cost array
	for(int i = 0; i < numVertices + 1; i++)
	{
		cost[i] = -1;
	}
	cost[numVertices] = 0;
	for(int i = numVertices - 1; i >= 1; i--)
	{
		// go through all adjacent vertices and find the minimum cost of going
		// from vertex i to vertex t (destination vertex)
		for(vertex<T>* u = adjacencyList[i]; u != NULL; u = u->next)
		{
			// if cost[i] is -1, that means there is no cost associated with that vertex
			// therefore, we put in a cost to start out with regardless if it is minimum or not
			if(cost[i] == -1)
			{
				// store new cost
				cost[i] = u->weight + cost[u->vertexLabel];
				// store vertex visited to get this new cost
				previousVertex[i] = u->vertexLabel;
			}
			// if cost[i] is greater than the new cost we calculate, then replace the value in
			// cost[i] with the new cost we found
			else if(cost[i] > u->weight + cost[u->vertexLabel])
			{
				// store new cost
				cost[i] = u->weight + cost[u->vertexLabel];
				// store vertex visited to get this new cost
				previousVertex[i] = u->vertexLabel;
			}
		}
	}

	// find the minimum cost path
	pForward[1] = 1; // first vertex will always be source vertex
	pForward[numStages] = numVertices; // last vertex will always be destination vertex
	for(int i = 2; i <= numStages - 1; i++)
	{
		pForward[i] = previousVertex[pForward[i-1]];
	}

	// return the minimum cost path
	return pForward;
}

// Method to compute the shortest path using dynamic programming and the backward approach
template<class T>
int* multistageGraph<T>::backwardApproachPath()
{
	int* pBackward = new int[numStages + 1];
	int previousVertex[numVertices + 1], bcost[numVertices + 1];
	// initialize cost array
	for(int i = 0; i < numVertices + 1; i++)
	{
		bcost[i] = -1;
	}
	bcost[1] = 0;
	for(int i = 1; i <= numVertices; i++)
	{
		// go through all adjacent vertices and find the minimum cost of going
		// from vertex s (source vertex) to vertex i
		for(vertex<T>* u = adjacencyList[i]; u != NULL; u = u->next)
		{
			// if cost[i] is -1, that means there is no cost associated with that vertex
			// therefore, we put in a cost to start out with regardless if it is minimum or not
			if(bcost[u->vertexLabel] == -1)
			{
				// store new cost
				bcost[u->vertexLabel] = u->weight + bcost[i];
				// store vertex visited to get this new cost
				previousVertex[u->vertexLabel] = i;
			}
			// if cost[i] is greater than the new cost we calculate, then replace the value in
			// cost[i] with the new cost we found
			else if(bcost[u->vertexLabel] > u->weight + bcost[i])
			{
				// store new cost
				bcost[u->vertexLabel] = u->weight + bcost[i];
				// store vertex visited to get this new cost
				previousVertex[u->vertexLabel] = i;
			}
		}
	}

	// find the minimum cost path
	pBackward[1] = 1; // first vertex will always be source vertex
	pBackward[numStages] = numVertices; // last vertex will always be destination vertex
	for(int i = numStages - 1; i >= 2; i--)
	{
		pBackward[i] = previousVertex[pBackward[i+1]];
	}

	// return the minimum cost path
	return pBackward;
}
#endif
