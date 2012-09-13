// HDOJ 2256
// Problem of Precision
// by A Code Rabbit

#include <cstdio>
#include <cmath>

const int DIVISOR = 1024;

struct Matrix {
    int element[2][2];
};

int t;

int n;

Matrix mat_one;
Matrix mat_ans;

void INIT();
void Multiply(Matrix& mat_a, Matrix mat_b);

int main() {
    scanf("%d", &t);
    while (t--) {
        // Inputs.
        scanf("%d", &n);       
        // INIT.
        INIT();
        // Quick Power.
        --n;
        /* Just need to compete to n - 1 */
        while (n) {
            if (n & 1) {
                Multiply(mat_ans, mat_one);
            }
            n >>= 1;
            Multiply(mat_one, mat_one);
            //printf("%d %d\n", mat_ans.element[0][0], mat_ans.element[0][1]);
            //printf("%d %d\n", mat_ans.element[1][0], mat_ans.element[1][1]);

        }
        // Compete.
        int x_n = (5 * mat_ans.element[0][0] + 2 * mat_ans.element[1][0]) % DIVISOR;
        printf("%d\n", (x_n * 2 - 1) % DIVISOR);
    }

    return 0;
}

void INIT() {
    mat_one.element[0][0] = 5;
    mat_one.element[0][1] = 2;
    mat_one.element[1][0] = 12;
    mat_one.element[1][1] = 5;
    mat_ans.element[0][0] = 1;
    mat_ans.element[0][1] = 0;
    mat_ans.element[1][0] = 0;
    mat_ans.element[1][1] = 1;
}

void Multiply(Matrix& mat_a, Matrix mat_b) {
    Matrix mat_c;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            mat_c.element[i][j] = 0;
            for (int k = 0; k < 2; k++) {
                mat_c.element[i][j] += mat_a.element[i][k] * mat_b.element[k][j];
            }
            mat_c.element[i][j] %= DIVISOR;
        }
    }
    mat_a = mat_c;
}
