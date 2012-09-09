// UVaOJ 490
// Rotating Sentences
// by A Code Rabbit

#include <cstdio>
#include <cstring>

char str[102][102];
int tot_str;

int main() {
    int max = 0;
    for (tot_str = 0; gets(str[tot_str]); tot_str++)
        if (strlen(str[tot_str]) > max)
            max = strlen(str[tot_str]);
    tot_str--;
    for (int i = 0; i < max; i++) {
        for (int j = tot_str; j >= 0; j--)
            printf("%c", str[j][i] ? str[j][i] : ' ');
        printf("\n");
    }

    return 0;
}
