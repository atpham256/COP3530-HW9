// Name: Anthony T. Pham
// UF ID: 5038-1111
// Discussion section #: 1079

#ifndef VERTEX_H
#define VERTEX_H

template <class T>
struct vertex
{
	// data members
	T vertexLabel;
	int weight;
	vertex<T> *next;

	// constructors
	vertex()
	{
		this->vertexLabel = 0;
		this->weight = 0;
		this->next = NULL;
	}
	vertex(const T& vertexLabel)
	{
		this->vertexLabel = vertexLabel;
		this->weight = 0;
		this->next = NULL;
	}
	vertex(const T& vertexLabel, const int& weight)
	{
		this->vertexLabel = vertexLabel;
		this->weight = weight;
		this->next = NULL;
	}
	vertex(const T& vertexLabel, const int& weight, vertex<T>* next)
	{
		this->vertexLabel = vertexLabel;
		this->weight = weight;
		this->next = next;
	}
};

#endif
