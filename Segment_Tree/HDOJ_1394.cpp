// HDOJ 1394
// Minimum Inversion Number
// by A Code Rabbit

#include <cstdio>
#include <cstring>

const int LIMITS = 5002;

int n;
int a[LIMITS];

int tree[LIMITS << 2];

void Update(int pos);
void Build();
void Insert(int l, int r, int pos, int x);
int Query(int l, int r, int pos, int x, int y);

int main() {
    while (~scanf("%d", &n)) {
        Build();
        int sum = 0;
        for (int i = 0; i < n; ++i) {
            scanf("%d", &a[i]);
            sum += Query(0, n - 1, 1, a[i], n - 1);          
            /**
             * Query(0, n - 1, 1, a[i] + 1, n - 1) is error, because a[i] + 1 is
             * maybe more than n - 1.
             */
            Insert(0, n - 1, 1, a[i]);
        }
        int min = sum;
        for (int i = 0; i < n - 1; ++i) {
            sum += n - a[i] - 1;
            sum -= a[i];
            min = sum < min ? sum : min;
        }
        printf("%d\n", min);
    }

    return 0;
}

#define LSon(x) (x << 1)
#define RSon(x) (x << 1 | 1)

void Update(int pos) {
    tree[pos] = tree[lson(pos)] + tree[rson(pos)];   
}

void Build() {
    memset(tree, 0, sizeof(tree));
}

void Insert(int l, int r, int pos, int x) {
    if (l == r) {
        tree[pos] = 1;
        return;
    }
    int m = l + r >> 1;
    if (x <= m) {
        Insert(l, m, lson(pos), x);
    } else {
        Insert(m + 1, r, rson(pos), x);
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
        return Query(l, m, lson(pos), x, y);
    } else
    if (x >= m + 1) {
        return Query(m + 1, r, rson(pos), x, y);
    } else {
        return Query(l, m, lson(pos), x, m) + Query(m + 1, r, rson(pos), m + 1, y);
    }
}
