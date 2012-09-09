// CF 134
// C. Ice Skating
// by A Code Rabbit

#include <algorithm>
#include <cstdio>
using namespace std;

const int MAXV = 102;
const int MAXE = MAXV * MAXV;
const int INF = 1e9;

template <typename T>
struct Point { 
    T x, y; 
    static double GetDistance(Point a, Point b) { 
        return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2)); 
    } 
};

template <typename T> 
struct Edge { 
    int u, v; 
    T w; 
}; 

template <typename T> 
struct Graph { 
    Edge<T> edge[MAXE]; 
    int tot_edge; 
    void Init() { tot_edge = 0; } 
    void AddEdge(int u, int v, T w) { 
        edge[tot_edge].u = u; 
        edge[tot_edge].v = v; 
        edge[tot_edge].w = w; 
        tot_edge++; 
    } 
};

namespace Kruskal { 
    int p[MAXV]; 
    template <typename T> 
    int Cmp(Edge<T> a, Edge<T> b) { return a.w < b.w; } 
    int Find(int x) { return p[x] == x ? x : p[x] = Find(p[x]); } 
    template <typename T> 
    T Go(Edge<T> e[MAXE], int n, int m) {
        sort(e, e + m, Cmp<T>); 
        T ans = 0; 
        for (int i = 0; i < m; i++) { 
            int u = Find(e[i].u); int v = Find(e[i].v); 
            if (u != v) { ans++; p[u] = v; } 
        } 
        return ans; 
    } 
}

int n;
Point<int> pt[MAXV];
Graph<int> graph;
int ans;

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &pt[i].x, &pt[i].y);
    }

    graph.Init();
    for (int i = 0; i < n; i++) Kruskal::p[i] = i; 
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            graph.AddEdge(i, j, 1);
            graph.AddEdge(j, i, 1);
            if (pt[i].x == pt[j].x || pt[i].y == pt[j].y) {
                int u = Kruskal::Find(i);
                int v = Kruskal::Find(j);
                Kruskal::p[u] = v;
            }
        }
    }

    printf("%d\n", Kruskal::Go(graph.edge, n, graph.tot_edge));

    return 0;
}
