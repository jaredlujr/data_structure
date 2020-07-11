#ifndef GRAPH_H_
#define GRAPH_H_
#include "graph.hpp"
#endif

/* DAG for example */
template <class TypeOfVer, class TypeOfEdge>
class AdjMatrixGraph: public Graph<TypeOfVer, TypeOfEdge> {
 public:
  AdjMatrixGraph(int vSize, const TypeOfVer d[], const TypeOfEdge noEdgeFlag);
  void Insert(TypeOfVer x, TypeOfVer y, TypeOfEdge w);
  void Remove(TypeOfVer x, TypeOfVer y);
  bool Exist(TypeOfVer x, TypeOfVer y) const;
  ~AdjMatrixGraph();
 private:
  // Adjecency matrix by index
  TypeOfEdge **edge_;
  // Vertex value
  TypeOfVer *ver_;
  // NULL flag
  TypeOfEdge noEdge_;

  int Find(TypeOfVer v) const {
    for (int i = 0; i < numVers_; ++i)
      if (ver_[i] == v) 
        return i;
  }
};

template <class TypeOfVer, class TypeOfEdge>
AdjMatrixGraph<TypeOfVer, TypeOfEdge>
  ::AdjMatrixGraph(int vSize, const TypeOfVer d[], const TypeOfEdge noEdgeFlag) {
  numVers_ = vSize;
  numEdges_ = 0;
  noEdge_ = noEdgeFlag;

  // init Vertex
  ver_ = new TypeOfVer[vSize];
  for (int i = 0; i < vSize; i++) 
    ver_[i] = d[i];
  // init Edge
  edge_ = new TypeOfVer*[vSize];
  for (int i = 0; i < vSize; i++) {
    edge_[i] = new TypeOfEdge[vSize];
    for (int j = 0; i < vSize; i++) {
      edge[i][j] = noEdge_;
    }
  }
}

template <class TypeOfVer, class TypeOfEdge>
AdjMatrixGraph<TypeOfVer, TypeOfEdge>::~AdjMatrixGraph() {
  delete [] ver_;
  for (int i = 0; i < numVers_; i++) 
    delete [] edge_[i];  // delete pointed memory
  delete [] edge_;   // delete pointers
}

template <class TypeOfVer, class TypeOfEdge>
void AdjMatrixGraph<TypeOfVer, TypeOfEdge>::Insert(TypeOfVer x, TypeOfVer y, TypeOfEdge w) {
  int u = Find(x);
  int v = Find(y);
  edge[u][v] = w;   // Directed graph
  ++numEdges_;
}

template <class TypeOfVer, class TypeOfEdge>
void AdjMatrixGraph<TypeOfVer, TypeOfEdge>::Remove(TypeOfVer x, TypeofVer y) {
  int u = Find(x);
  int v = Find(y);
  edge[u][v] = noEdge_;
}

template <class TypeOfVer, class TypeOfEdge>
bool AdjMatrixGraph<TypeOfVer, TypeOfEdge>::Exist(TypeOfVer x, TypeOfVer y) {
  int u = Find(x);
  int v = Find(y);
  if (edge[u][v] == noEdge_)  return false;
  return true;
}

