// UVaOJ 10300
// Ecological Premium
// by A Code Rabbit

#include <cstdio>

int main() {
    int tot_case;
    scanf("%d", &tot_case);
    while (tot_case--) {
        int f;
        scanf("%d", &f);
        int sum = 0;
        while (f--) {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            sum += a * c;
        }
        printf("%d\n", sum);
    } 

    return 0;
}
