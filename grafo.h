#ifndef __GRAFO_GRUPO3__
#define __GRAFO_GRUPO3__

#include <list>
#include <vector>
#include <utility>

//Lista de adyacencia
template <class T, class U>
class Graph {
private:
	std::vector<T> vertices;
	std::vector< std::list< std::pair<int,U> > > aristas;
public:
	Graph();
	void setVertices(std::vector<T> v);
	void setAristas(std::vector< std::list< std::pair<int,U> > > a);
	std::vector<T> getVertices();
	std::vector< std::list< std::pair<int,U> > > getAristas();
	int cantVertices();
	int cantAristas();
	int buscarVertice(T vert);
	bool insertarVertice(T vert);
	bool insertarArista(T ori, T des, U cos);
	U buscarArista(T ori, T des);
	bool eliminarVertice(T vert);
	bool eliminarArista(T ori, T des);
    T getVertice(long ind);
    std::vector<long> Dijkstra(long start, long end);
};

#include "grafo.hxx"	

#endif