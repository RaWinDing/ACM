// CF 134
// A. Mountain Scenery
// by A Code Rabbit

#include <cstdio>

int n, k;
int r[202];
int y[202];

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 0; i < n * 2 + 1; i++) {
        scanf("%d", &r[i]);
    }

    for (int i = n * 2; i >= 0; i--) {
        if (k && r[i] - 1 > r[i - 1] && r[i] - 1 > r[i + 1]) {
            y[i] = r[i] - 1;
            k--;
        } else {
            y[i] = r[i];
        }
    }

    for (int i = 0; i < n * 2 + 1; i++) {
        printf("%d ", y[i]);
    }
    printf("\n");

    return 0;
}
