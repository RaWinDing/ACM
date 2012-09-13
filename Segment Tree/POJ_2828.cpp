// POJ 2828
// Buy Tickets
// by A Code Rabbit

#include <cstdio>

const int LIMITS = 200002;
const int ROOT = 1;

struct Person {
    int pos;
    int val;
};

int n;
Person person[LIMITS];

int tree[LIMITS << 2];

int queue[LIMITS];

void Update(int pos);
void Build(int l, int r, int pos);
int Insert(int l, int r, int pos, int x);

int main() {
    while (~scanf("%d", &n)) {
        for (int i = 0; i < n; ++i) {
            scanf("%d%d", &person[i].pos, &person[i].val);
        }
        Build(0, n - 1, ROOT);
        for (int i = n - 1; i >= 0; --i) {
            queue[Insert(0, n - 1, ROOT, person[i].pos)] = person[i].val;
        }
        for (int i = 0; i < n - 1; ++i) {
            printf("%d ", queue[i]);
        }
        printf("%d\n", queue[n - 1]);
    }

    return 0;
}

#define LSon(x) (x << 1)
#define RSon(x) (x << 1 | 1)

void Update(int pos) {
    tree[pos] = tree[LSon(pos)] + tree[RSon(pos)];
}

void Build(int l, int r, int pos) {
    if (l == r) {
        tree[pos] = 1;
        return;
    }
    int m = l + r >> 1;
    Build(l, m, LSon(pos));
    Build(m + 1, r, RSon(pos));
    Update(pos);
}

int Insert(int l, int r, int pos, int x) {
    if (l == r) {
        tree[pos] = 0;
        return l;
    }
    int m = l + r >> 1;
    int result;
    if (x < tree[LSon(pos)]) {
        result = Insert(l, m, LSon(pos), x);
    } else {
        result = Insert(m + 1, r, RSon(pos), x - tree[LSon(pos)]);
    }
    Update(pos);
    return result;
}
