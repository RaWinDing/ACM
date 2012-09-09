// HDOJ 1754
// I Hate It
// by A Code Rabbit

#include <algorithm>
#include <cstdio>

using namespace std;

const int LIMITS = 200002;

int n, m;
char c;
int a, b;

int tree[LIMITS << 2];

void Update(int pos);
void Build(int l, int r, int pos);
void Modify(int l, int r, int pos, int x, int y);
int Query(int l, int r, int pos, int x, int y);

int main() {
    while (~scanf("%d%d", &n, &m)) {
        Build(1, n, 1);
        for (int i = 0; i < m; ++i) {
            getchar();
            scanf("%c%d%d", &c, &a, &b);
            if (c == 'Q') {
                printf("%d\n", Query(1, n, 1, a, b));
            } else
            if (c == 'U') {
                Modify(1, n, 1, a, b);
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
    if (l == r) {
        scanf("%d", &tree[pos]);
        return;
    }
    int m = l + r >> 1;
    Build(l, m, LSon(pos));
    Build(m + 1, r, RSon(pos));
    Update(pos);
}

void Modify(int l, int r, int pos, int x, int y) {
    if (l == r) {
        tree[pos] = y;
        return;
    }
    int m = l + r >> 1;
    if (x <= m) {
        Modify(l, m, LSon(pos), x, y);
    } else {
        Modify(m + 1, r, RSon(pos), x, y);
    }
    Update(pos);
}

int Query(int l, int r, int pos, int x, int y) {
    if (l == x &&
        r == y)
    {
        return tree[pos];
    }
    int m = l + r >> 1;
    if (y <= m) {
        return Query(l, m, LSon(pos), x, y);
    } else
    if (x >= m + 1) {
        return Query(m + 1, r, RSon(pos), x, y);
    } else {
        return max(Query(l, m, LSon(pos), x, m), Query(m + 1, r, RSon(pos), m + 1, y));
    }
}
