// UVaOJ 414
// Machined Surfaces
// by A Code Rabbit

#include <cstdio>
#include <cstring>

int n;
char str[100000];

int main() {
    while (scanf("%d", &n) && n) {
        gets(str);
        int min = 30;
        int sum = 0;
        for (int i = 0; i < n; i++) {
            gets(str);
            int cnt = 0;
            for (int i = 0; i < strlen(str); i++)
                if (str[i] == ' ') cnt++;
            min = cnt < min ? cnt : min;
            sum += cnt;
        }
        printf("%d\n", sum - n * min);
    }

    return 0;
}
