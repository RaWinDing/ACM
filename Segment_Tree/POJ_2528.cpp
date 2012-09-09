// POJ 2528
// Mayor's posters
// by A Code Rabbit

#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

#define LSon(x) x << 1
#define RSon(x) x << 1 | 1

const int LIMITS = 10002;
const int ROOT = 1;

struct Node {
    int val;
    int flag;
};

Node tree[LIMITS * 4 << 2];

void PushDown(int pos);
void Build();
void Modify(int l, int r, int pos, int x, int y, int z);
void Query(int l, int r, int pos);

struct Poster {
    int l;
    int r;
};

int t;

int n;
Poster poster[LIMITS];

int* pointer[LIMITS << 2];

bool CMP(int* x, int* y);

bool hash[LIMITS];

int main() {
    scanf("%d", &t);
    while (t--) {
        // Inputs.
        scanf("%d", &n);
        for (int i = 0; i < n; ++i) {
            scanf("%d%d", &poster[i].l, &poster[i].r);
            pointer[i * 2] = &poster[i].l;
            pointer[i * 2 + 1] = &poster[i].r;
        }
        // Discretization.
        sort(pointer, pointer + 2 * n, CMP);
        int num_bytes = 1;
        for (int i = 0; i < 2 * n - 1; ++i) {
            int temp = num_bytes;
            if (*pointer[i] != *pointer[i + 1]) {
                if (*pointer[i] + 1 == *pointer[i + 1]) {
                    num_bytes += 1;
                } else {
                    num_bytes += 1;
                    /* the correct answer should be: num_bytes += 2; */
                } }
            *pointer[i] = temp;
        }
        *pointer[2 * n - 1] = num_bytes;
        // Stick posters by the segments tree.
        Build();
        int num_posters = 1;
        for (int i = 0; i < n; ++i) {
            Modify(1, num_bytes, ROOT, poster[i].l, poster[i].r, num_posters++);
        }
        // Compete and outputs.
        memset(hash, false, sizeof(hash));
        Query(1, num_bytes, ROOT);
        int sum = 0;
        for (int i = 0; i < num_posters; ++i) {
            if (hash[i]) {
                ++sum;
            }
        }
        printf("%d\n", sum);
    }
}

void PushDown(int pos) {
    if (tree[pos].flag) {
        tree[LSon(pos)].flag = tree[pos].flag;
        tree[RSon(pos)].flag = tree[pos].flag;
        tree[LSon(pos)].val = tree[pos].flag;
        tree[RSon(pos)].val = tree[pos].flag;
        tree[pos].flag = 0;
    }
}

void Build() {
    memset(tree, 0, sizeof(tree));
}

void Modify(int l, int r, int pos, int x, int y, int z) {
    if (x <= l && r <= y) {
        tree[pos].val = z;
        tree[pos].flag = z;
        return;
    }
    PushDown(pos);
    int m = l + r >> 1;
    if (x <= m) {
        Modify(l, m, LSon(pos), x, y, z);
    }
    if (y > m) {
        Modify(m + 1, r, RSon(pos), x, y, z);
    }
}

void Query(int l, int r, int pos) {
    if (l == r) {
        hash[tree[pos].val] = true;
        return;
    }
    PushDown(pos);
    int m = l + r >> 1;
    Query(l, m, LSon(pos));
    Query(m + 1, r, RSon(pos));
}

bool CMP(int* x, int* y) {
    return *x < *y;
}
