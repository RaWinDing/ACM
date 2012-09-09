// HDOJ 1166
// 敌兵布阵
// by A Code Rabbit

#include <cstdio>
#include <cstring>

#define LSon(x) (x << 1) 
#define RSon(x) (x << 1 | 1)

const int MAXN = 50002;
const int ROOT = 1;

int tree[MAXN << 2];

void Update(int pos);
void Build(int l, int r, int pos);
void Modify(int l, int r, int pos, int x, int y);
int Query(int l, int r, int pos, int x, int y);

int n;
char command[20];
int x, y;

int main() {
    int tot_case = 0;
    scanf("%d", &tot_case);
    for (int t = 0; t < tot_case; t++) {
        scanf("%d", &n);
        Build(1, n, 1);
        printf("Case %d:\n", t + 1);
        while (1) {
            getchar();
            scanf("%s", command);
            if (!strcmp(command, "Add")) {
                scanf("%d%d", &x, &y);
                Modify(1, n, 1, x, y);
            } else
            if (!strcmp(command, "Sub")) {
                scanf("%d%d", &x, &y);
                Modify(1, n, 1, x, -y);
            } else
            if (!strcmp(command, "Query")) {
                scanf("%d%d", &x, &y);
                printf("%d\n", Query(1, n, 1, x, y));
            } else
            if (!strcmp(command, "End")) {
                break;
            }
        }
    }

	return 0;
}

void Update(int pos) {
    tree[pos] = tree[LSon(pos)] + tree[RSon(pos)];
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
        tree[pos] += y;
        return;
    }
    int m = l + r >> 1;
    if (x <= m) Modify(l, m, LSon(pos), x, y);
    else Modify(m + 1, r, RSon(pos), x, y);
    Update(pos);
}

int Query(int l, int r, int pos, int x, int y) {
    if (x <= l && r <= y) {
        return tree[pos];
    }
    int m = l + r >> 1;
    int ans = 0;
    if (x <= m) ans += Query(l, m, LSon(pos), x, y);
    if (y > m) ans += Query(m + 1, r, RSon(pos), x, y);
    return ans;
}
