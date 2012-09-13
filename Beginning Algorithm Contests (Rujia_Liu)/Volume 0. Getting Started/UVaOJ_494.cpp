// UVaOJ 494
// Kindergarten Counting Game
// by A Code Rabbit

#include <cstdio>
#include <cstring>

char str[10000];
int cnt;
bool bo;

int main() {
    while (gets(str)) {
        cnt = 0;
        bo = false;
        for (int i = 0; i < strlen(str); i++) {
            if ('a' <= str[i] && str[i] <= 'z' ||
                'A' <= str[i] && str[i] <= 'Z')
            {
                if (!bo) cnt++;
                bo = true;
            } else {
                bo = false;
            }
        }
        printf("%d\n", cnt);
    }

    return 0;
}
