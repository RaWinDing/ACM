// HDOJ 1698
// Just a Hook
// by A Code Rabbit

#include <cstdio>

#define LSon(x) (x << 1)
#define RSon(x) (x << 1 | 1)

const int MAXN = 100002;
const int ROOT = 1;

struct Seg {
    int val;
    int flag;
};

Seg tree[MAXN << 2];

void Update(int pos);
void Build(int l, int r, int pos);
void Push(int l, int r, int pos);
void Modify(int l, int r, int pos, int x, int y, int z);
int Query(int l, int r, int pos, int x, int y);

int n, q;
int x, y, z;

int main() {
    int tot_case;
    scanf("%d", &tot_case);
    for (int t = 0; t < tot_case; t++) {
        scanf("%d", &n);
        scanf("%d", &q);
        Build(1, n, ROOT);
        for (int i = 0; i < q; ++i) {
            scanf("%d%d%d", &x, &y, &z);
            Modify(1, n, ROOT, x, y, z);
        }
        printf("Case %d: The total value of the hook is %d.\n", t + 1, Query(1, n, ROOT, 1, n));
    }

    return 0;
}

void Update(int pos) {
    tree[pos].val = tree[LSon(pos)].val + tree[RSon(pos)].val;
}

void Build(int l, int r, int pos) {
    tree[pos].flag = 0;
    if (l == r) {
        tree[pos].val = 1;
        return;
    }
    int m = l + r >> 1;
    Build(l, m, LSon(pos));
    Build(m + 1, r, RSon(pos));
    Update(pos);
}

void Push(int l, int r, int pos) {
    Seg& father = tree[pos];
    if (father.flag) {
        Seg& lson = tree[LSon(pos)];
        Seg& rson = tree[RSon(pos)];
        int m = l + r >> 1;
        lson.val = father.flag * (m + 1 - l);
        rson.val = father.flag * (r - m);
        lson.flag = rson.flag = father.flag;
        father.flag = 0;
    }
}

void Modify(int l, int r, int pos, int x, int y, int z) {
    if (x <= l && r <= y) {
        tree[pos].val = z * (r + 1 - l);
        tree[pos].flag = z;
        return;
    }
    Push(l, r, pos);
    int m = l + r >> 1;
    if (x <= m) Modify(l, m, LSon(pos), x, y, z);
    if (y > m) Modify(m + 1, r, RSon(pos), x, y, z);
    Update(pos);
}

int Query(int l, int r, int pos, int x, int y) {
    if (x <= l && r <= y) {
        return tree[pos].val;
    }
    Push(l, r, pos);
    int m = l + r >> 1;
    int ans = 0;
    if (x <= m) ans += Query(l, m, LSon(pos), x, y);
    if (y > m) ans += Query(m + 1, r, RSon(pos), x, y);
    return ans;
}
