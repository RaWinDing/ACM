// POJ 3468
// A Simple Problem with Integers
// by A Code Rabbit

#include <cstdio>

#define LSon(x) (x << 1)
#define RSon(x) (x << 1 | 1)

const int LIMITS = 100002;
const int ROOT = 1;

struct Node {
    long long val;
    int flag;
};

Node tree[LIMITS << 2];

void PushUp(int pos) {
    tree[pos].val = tree[LSon(pos)].val + tree[RSon(pos)].val;
}

void PushDown(int l, int r, int pos) {
    if (tree[pos].flag) {
        int len = r + 1 - l;
        tree[LSon(pos)].flag += tree[pos].flag;
        tree[RSon(pos)].flag += tree[pos].flag;
        // Pay attention to changing int into long long.
        tree[LSon(pos)].val += (long long)tree[pos].flag * (len - (len >> 1));
        tree[RSon(pos)].val += (long long)tree[pos].flag * (len >> 1);
        tree[pos].flag = 0;
    }
}

void Build(int l, int r, int pos) {
    tree[pos].flag = 0;
    if (l == r) {
        scanf("%lld", &tree[pos].val);
        return;
    }
    int m = l + r >> 1;
    Build(l, m, LSon(pos));
    Build(m + 1, r, RSon(pos));
    PushUp(pos);
}

void Modify(int l, int r, int pos, int x, int y, int z) {
    if (x <= l && r <= y) {
        int len = r + 1 - l;
        // Pay attention to changing int into long long.
        tree[pos].val += (long long)z * len;
        tree[pos].flag += z;
        return;
    }
    PushDown(l, r, pos);
    int m = l + r >> 1;
    if (x <= m) {
        Modify(l, m, LSon(pos), x, y, z);
    }
    if (y > m) {
        Modify(m + 1, r, RSon(pos), x, y, z);
    }
    PushUp(pos);
}

long long Quary(int l, int r, int pos, int x, int y) {
    if (x <= l && r <= y) {
        return tree[pos].val;
    }
    PushDown(l, r, pos);
    int m = l + r >> 1;
    long long result = 0;
    if (x <= m) {
        result += Quary(l, m, LSon(pos), x, y);
    }
    if (y > m) {
        result += Quary(m + 1, r, RSon(pos), x, y);
    }
    PushUp(pos);
    return result;
}

int n, q;
char ch;
int a, b, c;

int main() {
    while (~scanf("%d%d", &n, &q)) {
        Build(1, n, ROOT);
        while (q--) {
            getchar();
            scanf("%c", &ch);
            if (ch == 'Q') {
                scanf("%d%d", &a, &b);
                printf("%lld\n", Quary(1, n, ROOT, a, b));
            } else
            if (ch == 'C') {
                scanf("%d%d%d", &a, &b, &c);
                Modify(1, n, ROOT, a, b, c);
            }
        }
    }

    return 0;
}
