// UVaOJ 558
// Wormholes
// by A Code Rabbit

#include <cstdio>
#include <cstring>

struct Edge {
    int w;
    int v;
    int next;
};

const int MAXV = 1002;
const int MAXE = 2002;
const int INF = 1e9;

int num_case;

int n, m;
Edge edge[MAXE];
int num_edge;
int first[MAXV];

int vis[MAXV];
bool exist_circle;

void Input();
void Init();
void AddEdge(int u, int v, int w);
void Solve();
void Search(int x, int t);
void Output();

int main() {
    scanf("%d", &num_case);
    while (num_case--) {
        Input();
        Solve();
        Output();
    }
    return 0;
}

void Input() {
    scanf("%d%d", &n, &m);
    Init();
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        AddEdge(u, v, w);
    }
}

void Init() {
    num_edge = 0;
    memset(first, -1, sizeof(first));
    for (int i = 0; i < n; ++i) {
        vis[i] = INF;
    }
    exist_circle = false;
}

void AddEdge(int u, int v, int w) {
    edge[num_edge].w = w;
    edge[num_edge].v = v;
    edge[num_edge].next = first[u];
    first[u] = num_edge;
    num_edge++;
}

void Solve() {
    Search(0, 0);
}

void Search(int x, int t) {
    if (exist_circle) {
        return;
    }
    int temp;
    if (t >= vis[x]) {
        return;
    }
    if (vis[x] != INF) {
        exist_circle = true;
        return;
    }
    temp = vis[x];
    vis[x] = t;
    for (int index = first[x];
        index != -1;
        index = edge[index].next)
    {
        Search(edge[index].v, t + edge[index].w);
    }
    vis[x] = temp;
}

void Output() {
    printf("%s\n", exist_circle ? "possible" : "not possible");
}
