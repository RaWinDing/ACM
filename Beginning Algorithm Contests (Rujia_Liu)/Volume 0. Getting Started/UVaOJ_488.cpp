// UVaOJ 488
// Triangle Wave
// by A Code Rabbit

#include  <cstdio>

int n, m;

int main() {
    int tot_case;
    bool first = true;
    scanf("%d", &tot_case);
    while (tot_case--) {
        scanf("%d%d", &n, &m);
        while (m--) {
            printf("%s", first ? first = false, "" : "\n");
            for (int i = 0; i < n; i++) {
                for (int j = 0; j <= i; j++)
                    printf("%d", i + 1);
                printf("\n");
            }
            for (int i = n - 2; i >= 0; i--) {
                for (int j = 0; j <= i; j++)
                    printf("%d", i + 1);
                printf("\n");
            }
        }
    }

    return 0;
}
