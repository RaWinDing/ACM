// HDOJ 2294
// pendant
// by A Code Rabbit

#include <cstdio>
#include <cstring>

const int ORDER = 33;
const int DIVISOR = 1234567891;

struct Matrix {
    long long element[ORDER][ORDER];
};

int t;
int n;
int k;

Matrix mat_unit;
Matrix mat_one;
Matrix mat_ans;

void INIT();
Matrix QuickPower(Matrix mat_one, int index);
Matrix Multiply(Matrix mat_a, Matrix mat_b);


int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &k);   
        INIT();
        mat_ans = QuickPower(mat_one, n);
        printf("%d\n", k * mat_ans.element[1][0] % DIVISOR);
    }

    return 0;
}

void INIT() {
    memset(mat_unit.element, 0, sizeof(mat_unit.element));
    for (int i = 0; i < k + 1; ++i) {
        mat_unit.element[i][i] = 1;
    }
    memset(mat_one.element, 0, sizeof(mat_one.element));
    mat_one.element[0][0] = 1;
    mat_one.element[k][0] = 1;
    for (int i = 1; i < k + 1; ++i) {
        mat_one.element[i][i] = i;
        if (i > 1) {
            mat_one.element[i - 1][i] = k - i + 1;
        }
    }
}

Matrix QuickPower(Matrix mat_one, int index) {
    Matrix mat_result = mat_unit;
    while (index) {
        if (index & 1) {
            mat_result = Multiply(mat_result, mat_one);
        }
        mat_one = Multiply(mat_one, mat_one);
        index >>= 1;
    }
    return mat_result;
}

Matrix Multiply(Matrix mat_a, Matrix mat_b) {
    Matrix mat_result;
    int order = k + 1;
    for (int i = 0; i < order; ++i) {
        for (int j = 0; j < order; ++j) {
            mat_result.element[i][j] = 0;
            for (int k = 0; k < order; ++k) {
                mat_result.element[i][j] += mat_a.element[i][k] * mat_b.element[k][j] % DIVISOR;
            }
            mat_result.element[i][j] %= DIVISOR;
        }
    }
    return mat_result;
}
