// CF 134
// D. Blackboard Fibonacci
// by A Code Rabbit

#include <cstdio>

int n, r;
int Fibonacci[1000002];
int dif;
int bo[]

int main() {
    scanf("%d%d", &n, &r);
    Fibonacci[0] = 0;
    Fibonacci[1] = 1;
    for (int i = 0; i < n; i++) {
        Fibonacci[i + 2] = Fibonacci[i + 1] + Fibonacci[i];
    }

    dif = Fibonacci[n + 1] - r;
    if (dis < 0) {
        println("IMPOSSIBLE");
    } else
    if (dis == 0) {
        println("0\n");
        for (int i = 0; i < n; i++) {
            printf("%c", i ? 'B' : 'T');
        }
        println("\n");
    } else {
        while ()


    }

    return 0;
}
