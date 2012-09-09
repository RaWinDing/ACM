// POJ 3225
// Help with Intervals
// by A Code Rabbit

#include <cstdio>

#define LSon(x) (x << 1)
#define RSon(x) (x << 1 | 1)

const int N = 65537 * 4;
const int MAXN = N + 2;
const int ROOT = 1;
const int FALSE = 0;
const int TRUE = 1;
const int NOT = 2;

struct Node {
    int val;
    int flag;
};

Node tree[MAXN << 2];

void Build();
int Not(int x);
void Push(int pos);
void Modify(int l, int r, int pos, int x, int y, int z);
void Query(int l, int r, int pos);

char command[20];

bool exist[MAXN];
int num;

int main() {
    // Input and solve.
    Build();
    while (gets(command)) {
        if (command[0] == '\0') {
            continue;
        }
        int p, q; 
        char x, ch1, ch2;
        sscanf(command, "%c %c%d,%d%c", &x, &ch1, &p, &q, &ch2);
        p *= 2;
        q *= 2;
        if (ch1 == '(') {
            p++;
        }
        if (ch2 == ')') {
            q--;
        }
        switch (x) {
        case 'U':
            Modify(0, N, ROOT, p, q, TRUE);
            break;
        case 'I':
            Modify(0, N, ROOT, 0, p - 1, FALSE);
            Modify(0, N, ROOT, q + 1, N, FALSE);
            break;
        case 'D':
            Modify(0, N, ROOT, p, q, FALSE);
            break;
        case 'C':
            Modify(0, N, ROOT, p, q, NOT);
            Modify(0, N, ROOT, 0, p - 1, FALSE);
            Modify(0, N, ROOT, q + 1, N, FALSE);
            break;
        case 'S':
            Modify(0, N, ROOT, p, q, NOT);
            break;
        }
    }
    // Output.
    num = 0;
    Query(0, N, ROOT);
    int p = -1;
    bool is_first = true;
    bool is_empty = true;
    for (int q = 0; q <= N; q++) {
        if (exist[q]) {
            is_empty = false;
        } else {
            int l = p + 1;
            int r = q - 1;
            if (l <= r) {
                printf("%s", is_first ? is_first = false, "" : " ");
                char ch1 = '[';
                char ch2 = ']';
                if (l % 2) ch1 = '(';
                if (r % 2) ch2 = ')';
                printf("%c%d,%d%c", ch1, l / 2, (r + 1) / 2, ch2);
                p = q - 1;
            }
            p++;
        }
    }
    printf("%s\n", is_empty ? "empty set" : "");

    return 0;
}

void Build() {
    for (int i = 0; i < MAXN << 2; i++) {
        tree[i].val = 0;
        tree[i].flag = -1;
    }
}

int Not(int x) {
    if (x == NOT) {
        return -1;
    } else
    if (x == -1) {
        return NOT;
    } else {
        return x ^ 1;
    }
}

void Push(int pos) {
    int& num = tree[pos].flag;
    if (num == -1) {
        return;
    }
    if (num == NOT) {
        tree[LSon(pos)].val ^= 1; 
        tree[RSon(pos)].val ^= 1;
        tree[LSon(pos)].flag = Not(tree[LSon(pos)].flag);
        tree[RSon(pos)].flag = Not(tree[RSon(pos)].flag);
    } else {
        tree[LSon(pos)].val = tree[RSon(pos)].val = num;
        tree[LSon(pos)].flag = tree[RSon(pos)].flag = num;
    }
    num = -1;
}

void Modify(int l, int r, int pos, int x, int y, int z) {
    if (x > y) {
        return;
    }
    if (x <= l && r <= y) {
        if (z == 2) {
            tree[pos].val ^= 1;
            if (tree[pos].flag == -1) {
                tree[pos].flag = 2;
            } else
            if (tree[pos].flag == 2) {
                tree[pos].flag = -1;
            } else {
                tree[pos].flag ^= 1;
            }
        } else {
            tree[pos].val = z;
            tree[pos].flag = z;
        }
        return;
    }
    Push(pos);
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
        exist[num++] = tree[pos].val;
        return;
    }
    Push(pos);
    int m = l + r >> 1;
    Query(l, m, LSon(pos));
    Query(m + 1, r, RSon(pos));
}
