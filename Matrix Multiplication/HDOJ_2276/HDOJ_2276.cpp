// HDOJ 2276
// Kiki & Little Kiki 2
// by A Code Rabbit

#include <cstdio>
#include <cstring>

const int LIMITS = 102;

struct Matrix {
    int element[LIMITS][LIMITS];
};

int n;
int m;
char t[LIMITS];

Matrix mat_unit;
Matrix mat_one;
Matrix mat_ans;

void INIT();

Matrix QuickPower(Matrix mat_result, Matrix mat_one, int index);
Matrix Multiply(Matrix mat_a, Matrix mat_b);

int main() {
    while (scanf("%d", &m) != EOF) {
        getchar();
        // Inputs. 
        gets(t);
        n = strlen(t);
        // Initialize.
        INIT();
        // QucikPower.
        mat_ans = QuickPower(mat_unit, mat_one, m);
        // Compete and outputs.
        for (int i = 0; i < n; ++i) {
            int sum = 0;
            for (int j = 0; j < n; ++j) {
                sum ^= (t[j] - '0') & mat_ans.element[j][i];
            }
            printf("%d", sum);
        }
        printf("\n");
    }

    return 0;
}

void INIT() {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            mat_unit.element[i][j] = i == j ? 1 : 0;
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if ((i + 1) % n == j || i == j) {
                mat_one.element[i][j] = 1; 
            } else {
                mat_one.element[i][j] = 0;
            }
        }
    }
    
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
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            mat_result.element[i][j] = 0;
            for (int k = 0; k < n; ++k) {
                mat_result.element[i][j] ^= mat_a.element[i][k] & mat_b.element[k][j];
            }
        }
    }
    return mat_result;
}
