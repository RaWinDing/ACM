// UVaOJ 10099
// The Tourist Guide
// by A Code Rabbit

#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

const int MAXV = 102;
const int MAXE = MAXV * MAXV;
const int INF = 1e9;

template <typename T>
struct Graph {
    T mat[MAXV][MAXV];
    void Init(int n) {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                mat[i][j] = i == j ? INF : 0;
    }
    void AddEdge(int u, int v, T w) {
        mat[u][v] = w;
    }
};

namespace Dijkstra {
    int v[MAXV];
    template <typename T>
    void Go(T d[MAXV], T w[MAXV][MAXV], int n, int s) {
        memset(v, 0, sizeof(v));
        for (int i = 0; i < n; i++) d[i] = i == s ? INF : 0;
        for (int i = 0; i < n; i++) {
            T m = -1;
            int x;
            for (int y = 0; y < n; y++) if (!v[y] && d[y] > m) m = d[x = y];
            v[x] = 1;
            for (int y = 0; y < n; y++) {
                m = min(d[x], w[x][y]);
                d[y] = m > d[y] ? m : d[y];
            }
        }
    }
}

int n, r;
int s, d, t;
Graph<int> graph;

int dis[MAXV];

int main() {
    int tot_case = 0;
    while (scanf("%d%d", &n, &r) && (n || r)) {
        // Input.
        graph.Init(n);
        for (int i = 0; i < r; i++) {
            int c1, c2, p;
            scanf("%d%d%d", &c1, &c2, &p);
            c1--, c2--;
            graph.AddEdge(c1, c2, p);
            graph.AddEdge(c2, c1, p);
        }
        scanf("%d%d%d", &s, &d, &t);
        s--, d--;
        // Solve.
        Dijkstra::Go(dis, graph.mat, n, s);
        // Output.
        printf("Scenario #%d\n", ++tot_case);
        printf("Minimum Number of Trips = %d\n", (t + dis[d] - 2) / (dis[d] - 1));
        printf("\n");
    }
    return 0;
}
