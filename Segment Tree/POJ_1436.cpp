// POJ 1436
// Horizontally Visible Segments
// by A Code Rabbit

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

#define LSon(x) (x << 1)
#define RSon(x) (x << 1 | 1)

const int MAXN = 8002;
const int ROOT = 1;

int tree[MAXN * 2 << 2];

void Build();
void Push(int pos);
void Modify(int l, int r, int pos, int x, int y, int z);
void Query(int l, int r, int pos, int x, int y, int z);

struct Seg {
    int y1, y2;
    int x0;
};

int n;
Seg seg[MAXN];

vector<int> vec[MAXN];
bool exist[MAXN];

int Cmp(Seg a, Seg b) { return a.x0 < b.x0; }

int main() {
    int tot_case;
    scanf("%d", &tot_case);
    while (tot_case--) {
        // Input.
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf("%d%d%d", &seg[i].y1, &seg[i].y2, &seg[i].x0);
            seg[i].y1 *= 2;
            seg[i].y2 *= 2;
        }
        // Solve.
        sort(seg, seg + n, Cmp);
        for (int i = 0; i < n; i++)
            vec[i].clear();
        Build();
        for (int i = 0; i < n; i++) {
            memset(exist, false, sizeof(exist));
            Query(0, 8000 * 2, ROOT, seg[i].y1, seg[i].y2, i);
            Modify(0, 8000 * 2, ROOT, seg[i].y1, seg[i].y2, i);
        }
        int ans = 0;
        for (int i = 0; i < n; i++) {
            int num_seg1= i;
            for (int j = 0; j < vec[num_seg1].size(); j++) {
                int num_seg2 = vec[num_seg1][j];
                for (int k = 0; k < vec[num_seg2].size(); k++)
                    for (int l = 0; l < vec[num_seg1].size(); l++)
                        if (vec[num_seg1][l] == vec[num_seg2][k])
                            ans++;
            }
        }
        printf("%d\n", ans);
    }
    
    return 0;
}

void Build() {
    memset(tree, -1, sizeof(tree));
}

void Push(int pos) {
    if (tree[pos] != -1) {
        tree[LSon(pos)] = tree[RSon(pos)] = tree[pos];
        tree[pos] = -1;
    }
}

void Modify(int l, int r, int pos, int x, int y, int z) {
    if (x <= l && r <= y) {
        tree[pos] = z;
        return;
    }
    Push(pos);
    int m = l + r >> 1;
    if (x <= m) Modify(l, m, LSon(pos), x, y, z);
    if (y > m) Modify(m + 1, r, RSon(pos), x, y, z);
}

void Query(int l, int r, int pos, int x, int y, int z) {
    if (tree[pos] != -1) {
        if (!exist[tree[pos]]) {
            vec[z].push_back(tree[pos]);
            exist[tree[pos]] = true;
        }
        return;
    }
    if (l == r) return;
    int m = l + r >> 1;
    if (x <= m) Query(l, m, LSon(pos), x, y, z);
    if (y > m) Query(m + 1, r, RSon(pos), x, y, z);
}
