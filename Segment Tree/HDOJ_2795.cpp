// HDOJ 2795
// Billboard
// by A Code Rabbit

#include <algorithm>
#include <cstdio>

using namespace std;

const int LIMITS = 200002;
const int ROOT = 1;

int h, w, n;
int wi;

int tree[LIMITS << 2];

void Update(int pos);
void Build(int l, int r, int pos);
int Insert(int l, int r, int pos, int x);

int main() {
    while (~scanf("%d%d%d", &h, &w, &n)) {
        int top = min(h, n);
        Build(1, top, ROOT);
        for (int i = 0; i < n; ++i) {
            scanf("%d", &wi);
            if (wi <= tree[ROOT]) {
                printf("%d\n", Insert(1, top, ROOT, wi));
            } else {
                printf("-1\n");
            }
        }
    }

    return 0;
}

#define LSon(x) (x << 1)
#define RSon(x) (x << 1 | 1)

void Update(int pos) {
    tree[pos] = max(tree[LSon(pos)], tree[RSon(pos)]);
}

void Build(int l, int r, int pos) {
    tree[pos] = w;
    if (l == r) {
        return;
    }
    int m = l + r >> 1;
    Build(l, m, LSon(pos));
    Build(m + 1, r, RSon(pos));
}

int Insert(int l, int r, int pos, int x) {
    if (l == r) {
        tree[pos] -= x;
        return l;
    }
    int m = l + r >> 1;
    int result;
    if (x <= tree[LSon(pos)]) {
        result = Insert(l, m, LSon(pos), x);
    } else {
        result = Insert(m + 1, r, RSon(pos), x);
    }
    Update(pos);
    return result;
}
