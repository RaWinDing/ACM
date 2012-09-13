// HDOJ 2842
// Chinese Rings
// by A Code Rabbit

#include <cstdio>

const int ORDER = 3;
const int DIVISOR = 200907;

struct Matrix {
    long long element[ORDER][ORDER];
};

int n;

Matrix mat_unit;
Matrix mat_one;
Matrix mat_ans;

int original_solution[] = {
    2, 1, 1,
};

void INIT();

Matrix QuickPower(Matrix mat_result, Matrix mat_one, int index);
Matrix Multiply(Matrix mat_a, Matrix mat_b);

int main() {
    while (scanf("%d", &n), n) {
        INIT();
        if (n <= 2) {
            printf("%d\n", original_solution[2 - n]);
            continue;
        } else {
            mat_ans = QuickPower(mat_unit, mat_one, n - 2);
            int sum = 0;
            for (int i = 0; i < ORDER; ++i) {
                sum += original_solution[i] * mat_ans.element[i][0];
            }
            printf("%d\n", sum % DIVISOR);
        }
    }

    return 0;
}

void INIT() {
    for (int i = 0; i < ORDER; ++i) {
        for (int j = 0; j < ORDER; ++j) {
            mat_unit.element[i][j] = i == j ? 1 : 0;
        }
    }
    for (int i = 0; i < ORDER; ++i) {
        for (int j = 0; j < ORDER; ++j) {
            mat_one.element[i][j] = 0;
        }
    }
    mat_one.element[0][0] = 1;
    mat_one.element[0][1] = 1;
    mat_one.element[1][0] = 2;
    mat_one.element[2][0] = 1;
    mat_one.element[2][2] = 1;
}

Matrix QuickPower(Matrix mat_result, Matrix mat_one, int index) {
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
    for (int i = 0; i < ORDER; ++i) {
        for (int j = 0; j < ORDER; ++j) {
            mat_result.element[i][j] = 0;
            for (int k = 0; k < ORDER; ++k) {
                mat_result.element[i][j] += mat_a.element[i][k] * mat_b.element[k][j];
            }
            mat_result.element[i][j] %= DIVISOR;
        }
    }
    return mat_result;
}
