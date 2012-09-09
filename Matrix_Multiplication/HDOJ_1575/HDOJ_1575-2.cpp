// HDOJ 1575
// Tr A
// by A Code Rabbit

#include <cstdio>
#include <cstring>

const int LIMITS = 12;
const int DIVISOR = 9973;

struct Matrix {
    int element[LIMITS][LIMITS];
};

int t;

Matrix matrix_one;
int n, k;

Matrix matrix_ans;

void Multiply(Matrix& a, Matrix b);
int GetTrace(Matrix a);

int main() {
    scanf("%d", &t);
    while (t--) {
        // Inputs.
        scanf("%d%d", &n, &k);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                scanf("%d", &matrix_one.element[i][j]);
            }
        }
        // Unitization.
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                matrix_ans.element[i][j] = i == j ? 1 : 0; 
            }
        }
        // Quick Power.
        while (k) {
            if (k & 1) {
                Multiply(matrix_ans, matrix_one);
            }
            k >>= 1;
            Multiply(matrix_one, matrix_one);
        }
        // Outputs.
        printf("%d\n", GetTrace(matrix_ans));
    }

    return 0;
}

void Multiply(Matrix& a, Matrix b) {
    Matrix c;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            c.element[i][j] = 0;
            for (int k = 0; k < n; ++k) {
                c.element[i][j] += a.element[i][k] * b.element[k][j];
            }
            c.element[i][j] %= DIVISOR;
        }
    }
    a = c;
}

int GetTrace(Matrix a) {
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += a.element[i][i];
    }
    return sum % DIVISOR;
}
