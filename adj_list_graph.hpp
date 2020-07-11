#ifndef GRAPH_H_
#define GRAPH_H_
#include "graph.hpp"
#endif

#ifndef LINK_STACK_H
#define LINK_STACK_H
#include "link_stack.hpp"
#endif


#ifndef LINK_QUEUE_H
#define LINK_QUEUE_H
#include "link_queue.hpp"
#endif


/* DAG for example */
template <class TypeOfVer, class TypeOfEdge>
class AdjListGraph: public Graph<TypeOfVer, TypeOfEdge> {
 public:
  AdjListGraph(int vSize, const TypeOfVer d[]);
  void Insert(TypeOfVer x, TypeOfVer y, TypeOfEdge w);
  void Remove(TypeOfVer x, TypeOfVer y);
  bool Exist(TypeOfVer x, TypeOfVer y) const;
  void Dfs(void) const;
  void DfsNr(void) const;
  void Dfs(int start, bool visited[]) const;
  void Bfs(void) const;
  void TopoSort(void) const;
  ~AdjListGraph();
 private:
  // Store the edge in linked manner
  struct EdgeNode {
    int end;  // Index of THIS vertex
    TypeOfEdge weight;   
    EdgeNode *next;   // Pointer
    EdgeNode(int e, TypeOfEdge w, EdgeNode *n = NULL) {
      end = e;
      weight = w;
      next = n;
    }
  };
  // Store the primal vertex (1...numVers_)
  struct VerNode {
    TypeOfVer ver;
    EdgeNode *head;
    VerNode(EdgeNode *h=NULL) {head = h;}
  };
  VerNode *verList_;
  int *inDeg_;
  int Find(TypeOfVer v) const {
    for (int i = 0; i < this->numVers_; i++) {
      if (verList_[i].ver == v) return i;
    }
    return -1;
  }
};


template <class TypeOfVer, class TypeOfEdge>
AdjListGraph<TypeOfVer, TypeOfEdge>::AdjListGraph(int vSize, const TypeOfVer d[]) {
  this->numVers_ = vSize;
  this->numEdges_ = 0;
  verList_ = new VerNode[vSize];
  inDeg_ = new int[vSize];
  for (int i = 0; i < vSize; i++){
    verList_[i].ver = d[i];
    inDeg_[i] = 0;
  }
}


template <class TypeOfVer, class TypeOfEdge>
AdjListGraph<TypeOfVer, TypeOfEdge>::~AdjListGraph() {
  EdgeNode *p;
  // Purge all edge nodes
  for (int i = 0; i < this->numVers_; i++) 
    while ((p = verList_[i].head) != NULL) {
        verList_[i].head = p->next;
        delete p;
    }
  // Purge all vertex nodes
  delete [] verList_;
}

template <class TypeOfVer, class TypeOfEdge>
void AdjListGraph<TypeOfVer, TypeOfEdge>::Insert(TypeOfVer x, TypeOfVer y, TypeOfEdge w) {
  int u = Find(x);
  int v = Find(y);
  // neck insert
  verList_[u].head = new EdgeNode(v, w, verList_[u].head);
  ++this->numEdges_;
  inDeg_[v]++;
}

template <class TypeOfVer, class TypeOfEdge>
void AdjListGraph<TypeOfVer, TypeOfEdge>::Remove(TypeOfVer x, TypeOfVer y) {
  int u = Find(x);
  int v = Find(y);
  // Double pointer
  EdgeNode *p = verList_[u].head;
  EdgeNode *q;
  // When p has no edge, so no end
  if (!p) return;
  // When 1st edge is the target
  if (p->end == v) {
    verList_[u].head = p->next;
    delete p;
    --this->numEdges_;
    inDeg_[v]--;
    return;
  }
  while (p->next && p->next->end != v) 
    p = p->next;
  // Rear or target
  if (p->next) {
    q = p->next;
    p->next = q->next;
    delete q;
    --this->numEdges_;
    inDeg_[v]--;
  }
}

template <class TypeOfVer, class TypeOfEdge>
bool AdjListGraph<TypeOfVer, TypeOfEdge>::Exist(TypeOfVer x, TypeOfVer y) const {
  int u = Find(x);
  int v = Find(y);
  EdgeNode *p = verList_[u].head;
  while (p && p->end != v)
    p = p->next;
  if (p)
    return true;
  else 
    return false;
}

/* Traverse */
template <class TypeOfVer, class TypeOfEdge>
void AdjListGraph<TypeOfVer, TypeOfEdge>::Dfs(void) const {
  bool *visited = new bool[this->numVers_];
  for (int i = 0; i < this->numVers_; i++) 
    visited[i] = false;
  std::cout << "DFS(" << this->numVers_<< "): (Each row as one connect component) " << std::endl;
  
  for (int i = 0; i < this->numVers_; i++) {
    if (visited[i]) 
      continue;
    std:: cout<< "[DEBUG]ROW: " ;
    Dfs(i, visited);
    std::cout << std::endl;
  }
}

template <class TypeOfVer, class TypeOfEdge>
void AdjListGraph<TypeOfVer, TypeOfEdge>::Dfs(int start, bool visited[]) const {
  visited[start] = true;  // Flag
  EdgeNode *p = verList_[start].head;
  
  std::cout << verList_[start].ver << ' ';
  while (p) {
    if (!visited[p->end]) 
      Dfs(p->end, visited);   // recursive
    p = p->next;
  }
}

/* Non-recursive implementation */
template <class TypeOfVer, class TypeOfEdge>
void AdjListGraph<TypeOfVer, TypeOfEdge>::DfsNr(void) const {
  LinkStack<int> s;
  int start;
  EdgeNode *p;
  bool *visited = new bool[this->numVers_];
  for (int i = 0; i < this->numVers_; i++) 
    visited[i] = false;
  std::cout << "DFS(" << this->numVers_<< "): (Each row as one connect component) " << std::endl;
  for (int i = 0; i < this->numVers_; i++) {
    if (visited[i]) continue;
    s.push(i);
    while (!s.isEmpty()) {
      start = s.pop();
      if (visited[start]) continue;
      std::cout << verList_[start].ver << '\t';
      visited[start] = true;
      // children
      p = verList_[start].head;
      while (p) {
        if (!visited[p->end]) s.push(p->end);
        p = p->next;
      }//while
    }//while
    // one connected component end
    std::cout << std::endl;
  }//for

}

template <class TypeOfVer, class TypeOfEdge>
void AdjListGraph<TypeOfVer, TypeOfEdge>::Bfs(void) const {
  LinkQueue<int> q;
  EdgeNode *p;
  int currentNode;
  bool *visited = new bool[this->numVers_];
  // init
  for (int i = 0; i < this->numVers_; i++) 
    visited[i] = false;
  
  std::cout << "BFS: (Each row as one connect component) " << std::endl;
  
  for (int i = 0; i < this->numVers_; i++) {
    // Connect Component
    if (visited[i]) 
      continue;
    std:: cout<< "[DEBUG]ROW: " ;
    q.enQueue(i);
    while (!q.isEmpty()) {
      currentNode = q.deQueue();
      if (visited[currentNode]) 
        continue;
      std::cout << verList_[currentNode].ver << ' '; 
      visited[currentNode] = true;
      p = verList_[currentNode].head;
      while (p) {
        if (!visited[p->end]) 
          q.enQueue(p->end);
        p = p->next;
      }
    }// while
    std::cout << std::endl;
  }// for
}



template<class TypeOfVer, class TypeOfEdge>
void AdjListGraph<TypeOfVer, TypeOfEdge>::TopoSort(void) const { 
  LinkQueue<int> q;
  LinkQueue<int> qTerm;
  EdgeNode *p;
  int currentNode;
  int currentTerm;
  bool *visited = new bool[this->numVers_];

  for (int i = 0; i < this->numVers_; i++) 
    visited[i] = false;
  
  currentTerm = 0;
  for (int i = 0; i < this->numVers_; i++) {
    if (inDeg_[i] == 0) {  // starting element
      q.enQueue(i);
      qTerm.enQueue(currentTerm);
    }
  }
  //std::cout << "Topological sort: " << std::endl;
  while (!q.isEmpty()) {
    currentNode = q.deQueue();
    currentTerm = qTerm.deQueue();
    //std::cout << verList_[currentNode].ver << std::endl;
    // enqueue the child node that degree-1==0
    for (p = verList_[currentNode].head; p != NULL; p = p->next) {
      if (--inDeg_[p->end] == 0) {
        q.enQueue(p->end);
        qTerm.enQueue(currentTerm + 1);
      }
    }
  }
  std::cout << currentTerm + 1 << std::endl;
}