
#include "adj_list_graph.hpp"

int main(void) {
    int n,m;
    std::cin>>n>>m;
    int *array = new int[n];
    for (int i = 0; i< n; i++) 
        array[i] =  i+1;
    AdjListGraph<int, int> g(n, array);
    for (int i = 0; i< m; i++){
        int x,y;
        std::cin >> x >> y;
        g.Insert(x, y, 1);
    }
    //g.Bfs();
    //g.Dfs();
    g.TopoSort();
    delete [] array;
    
    return 0;
}