#include <stack>
#include <iostream>
#include "grafo.h"

template <class T, class U>
Graph<T, U>::Graph() {}

template <class T, class U>
void Graph<T, U>::setVertices(std::vector<T> v) {
    this->vertices = v;
}

template <class T, class U>
void Graph<T, U>::setAristas(std::vector< std::list< std::pair<int,U> > > a) {
    this->aristas = a;
}

template <class T, class U>
std::vector<T> Graph<T, U>::getVertices() {
    return this->vertices;
}

template <class T, class U> 
std::vector< std::list< std::pair<int,U> > > Graph<T, U>::getAristas() {
    return this->aristas;
}

template <class T, class U>
int Graph<T, U>::cantVertices() { return vertices.size(); }

template <class T, class U>
int Graph<T, U>::cantAristas()  {
    int suma = 0;
    for (int i = 0; i < cantVertices(); i++) {
        suma += aristas[i].size();
    }
    return suma;
}

template <class T, class U>
int Graph<T, U>::buscarVertice(T vert) {
    int ind = -1;
    for (int i = 0; i < cantVertices(); i++) {
        if (vertices[i] == vert)  ind = i;
    }
    return ind;
}

template <class T, class U>
bool Graph<T, U>::insertarVertice(T vert) {
    bool res = false;
    if (buscarVertice(vert) == -1) {
        vertices.push_back(vert);
        std::list< std::pair<int,U> > *nlist = new std::list< std::pair<int,U> >;
        aristas.push_back(*nlist);
    }
    return res;
}

template <class T, class U>
bool Graph<T, U>::insertarArista(T ori, T des, U cos) {
    bool res = false;
    int i_ori = buscarVertice(ori);
    int i_des = buscarVertice(des);
    if ( i_ori != -1 && i_des != -1 ) {
        bool esta = false;
        typename std::list< std::pair<int,U> >::iterator itList = aristas[i_ori].begin();
        for (; itList != aristas[i_ori].end(); itList++) {
            if (itList->first == i_des)  esta = true;
        }
        if (!esta) {
            std::pair<int,U> *n_par = new std::pair<int,U>;
            n_par->first = i_des;
            n_par->second = cos;
            aristas[i_ori].push_back(*n_par);
            res = true;
        }
    }
    return res;
}

template <class T, class U>
U Graph<T, U>::buscarArista(T ori, T des) {
    U res = -1;
    int i_ori = buscarVertice(ori);
    int i_des = buscarVertice(des);
    if ( i_ori != -1 && i_des != -1 ) {
        typename std::list< std::pair<int,U> >::iterator itList = aristas[i_ori].begin();
        for (; itList != aristas[i_ori].end(); itList++) {
            if (itList->first == i_des)  res = itList->second;
        }
    }
    return res;
}

template <class T, class U>
bool Graph<T, U>::eliminarVertice(T vert) {
    bool res = false;
    int i_vert = buscarVertice(vert);
    if ( i_vert != -1) {
        typename std::vector< std::list< std::pair<int,U> > >::iterator itA, posE;
        int ind = 0;
        for (itA = aristas.begin(); itA != aristas.end(); itA++, ind++) {
            if (ind == i_vert) {
                posE = itA;
            } else {
                typename std::list< std::pair<int,U> >::iterator itList, posEE;
                for (itList = itA->begin(); itList != itA->end(); itList++) {
                    if (itList->first == i_vert) {
                        posEE = itList;
                    }
                }
                itA->erase(posEE);
            }
        }
        aristas.erase(posE);
    }
    return res;
}

template <class T, class U> 
bool Graph<T, U>::eliminarArista(T ori, T des) {
    bool res = false;
    int i_ori = buscarVertice(ori);
    int i_des = buscarVertice(des);
    if ( i_ori != -1 && i_des != -1 ) {
        typename std::list< std::pair<int,U> >::iterator itList, posE;
        for (itList = aristas[i_ori].begin(); itList != aristas[i_ori].end(); itList++) {
            if (itList->first == i_des)  posE = itList;
        }
        aristas[i_ori].erase(posE);
    }
    return res;
}

template <class T, class U>
T Graph<T, U>::getVertice(long ind) {
    T vacio;
    if(ind < 0 || ind >= vertices.size()) {
        return vacio;
    }
    return vertices[ind];
}

template <class T, class U>
std::vector<long> Graph<T, U>::Dijkstra(long start, long end) {
    //Inicializar los arreglos
    std::vector<U> pesos(this->vertices.size(), std::numeric_limits<U>::max()); //No hayamos infinito, asi que lo pusimos al maximo posible
    std::vector<long> predecesores (this->vertices.size(), -1);
    std::vector<bool> visitados (this->vertices.size(), false);
    //Iteradores necesarios
    typename std::list<std::pair<int,U>>::iterator itAristas;
    typename std::vector<U>::iterator itPesos;
    //Variables auxiliares
    U pesoAux;
    U pesoMinAux;
    long indAux;
    std::stack<long> auxRuta;
    std::vector<long> ruta;
    long predecesorAux;
    //Iniciar el nodo con el indice
    long nodoActual = start;
    pesos[nodoActual] = 0;
    predecesores[nodoActual] = -1; //Es el inicial asi que su predecesor es indefinido   
    while(nodoActual != -1) {
        visitados[nodoActual] = true;
        for(itAristas = this->aristas[nodoActual].begin(); itAristas != this->aristas[nodoActual].end(); itAristas++) {
            pesoAux = pesos[nodoActual] + itAristas->second;
            if(pesos[itAristas->first] > pesoAux) {
                pesos[itAristas->first] = pesoAux;
                predecesores[itAristas->first] = nodoActual;
            }
        }
        pesoMinAux = std::numeric_limits<U>::max();
        indAux = 0;
        for(itPesos = pesos.begin(); itPesos != pesos.end(); itPesos++) {
            if(pesoMinAux > *itPesos && !visitados[indAux]) {
                pesoMinAux = *itPesos;
                nodoActual = indAux;
            }
            indAux++;
        }
        
        if(pesoMinAux == std::numeric_limits<U>::max()) {
            //Ya todos los nodos estan visitados
            nodoActual = -1;
        }
    }
    auxRuta.push(end);
    predecesorAux = predecesores[end];  
    if(predecesorAux == -1) {
        std::cout<<"No es posible establecer una ruta entre dichos vertices\n";
        return ruta;
    }  
    while(predecesorAux != start) {
        auxRuta.push(predecesorAux);
        predecesorAux = predecesores[predecesorAux];
    }
    auxRuta.push(start);
    while(!auxRuta.empty()) {
        ruta.push_back(auxRuta.top());
        auxRuta.pop();
    }
    return ruta;    
}

