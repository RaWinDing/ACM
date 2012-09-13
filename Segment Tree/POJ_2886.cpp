// POJ 2886
// Who Gets the Most Candies
// by A Code Rabbit

#include <cstdio>
#include <cstring>

const int LIMITS = 500002;
const int LEN_NAME = 12;
const int ROOT = 1;

const int anti_prime[] = {
    1, 2, 4, 6, 12, 24, 36, 48, 60,
    120, 180, 240, 360, 720, 840, 1260, 1680, 2520, 5040,
    7560, 10080, 15120, 20160, 25200, 27720, 45360, 50400, 55440, 83160,
    110880, 166320, 221760, 277200, 332640, 498960, 554400,
};

struct Child {
    char name[LEN_NAME];
    int number;
};

int n, k;
Child child[LIMITS];

char max_name[LEN_NAME];

int tree[LIMITS << 2];

void Update(int pos);
void Build(int l, int r, int pos);
Child Insert(int l, int r, int pos, int x);

int Compete(int x);

int main() {
    while (~scanf("%d%d", &n, &k)) {
        for (int i = 0; i < n; ++i) {
            getchar();
            scanf("%s%d", child[i].name, &child[i].number);
        }
        Build(0, n - 1, ROOT);
        int pos_insert = k;
        int num_remain = n;
        int top_anti_prime = 0;
        while (num_remain) {
            Child child_jump_out = Insert(0, n - 1, ROOT, pos_insert - 1);
            --num_remain;
            if (anti_prime[top_anti_prime] == n - num_remain) {
                strcpy(max_name, child_jump_out.name);
                ++top_anti_prime;
            }
            if (num_remain) {
                int number = child_jump_out.number;
                if (number > 0) {
                    pos_insert = (pos_insert - 1 + number - 1) % num_remain + 1;
                } else {
                    number = (-number) % num_remain;
                    pos_insert = (pos_insert + num_remain - number - 1) % num_remain + 1;
                }
            }
        }
        printf("%s %d\n", max_name, Compete(anti_prime[top_anti_prime - 1]));
    }

    return 0;
}

#define LSon(x) (x << 1)
#define RSon(x) (x << 1 | 1)

void Update(int pos) {
    tree[pos] = tree[lson(pos)] + tree[rson(pos)];
}

void Build(int l, int r, int pos) {
    if (l == r) {
        tree[pos] = 1;
        return;
    }
    int m = l + r >> 1;
    Build(l, m, lson(pos));
    Build(m + 1, r, rson(pos));
    Update(pos);
}

Child Insert(int l, int r, int pos, int x) {
    if (l == r) {
        tree[pos] = 0;
        return child[l];
    }
    int m = l + r >> 1;
    Child result;
    if (tree[lson(pos)] > x) {
        result = Insert(l, m, lson(pos), x);
    } else {
        result = Insert(m + 1, r, rson(pos), x - tree[lson(pos)]);
    }
    Update(pos);
    return result;
}

int Compete(int x) {
    int result = 0;
    for (int i = 1; i * i <= x; ++i) {
        if (x % i == 0) {
            result += i * i == x ? 1 : 2;
        }
    }
    return result;
}
