#pragma once
#include "Vector.h"
#include "Graph.h"

template <typename Tv> struct Vertex 
{ 
	Tv data;
	int inDegree, outDegree;
	VStatus status;
	int dTime, fTime;
	int parent, priority;
	//Construct function
	Vertex(const Tv &d = (Tv)0): data(d), inDegree(0), outDegree(0), status(UNDISCOVERED), dTime(-1), fTime(-1), parent(-1), priority(INT_MAX){}
};

template <typename Te> struct Edge
{
	Te data;
	int weight;
	EStatus status;
	Edge(const Te &d = (Te)0, int w = 0): data(d), weight(w), status(UNDETERMINED){}
};

template <typename Tv, typename Te> class GraphMatrix : public Graph<Tv, Te>
{
private:
	Vector<Vertex<Tv>> V;
	Vector<Vector<Edge<Te>*>> E;
public:
	GraphMatrix():n(0),e(0){}
	~GraphMatrix()
	{
		for (int j = 0; j < n; j++)
			for (int k = 0; k < n; k++)
				delete E[j][k];
	}
}