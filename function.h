#ifndef OP6_FUNCTION_H
#define OP6_FUNCTION_H

#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define BLUE "\x1b[36m"
#define YELLOW  "\x1b[33m"
#define RESET "\033[0m"

void freeArrays(int n, double **a, double *xp, double *x, double *b) {
    for (int i = 0; i < n; i++) {
        free(a[i]);
    }
    free(a);
    free(x);
    free(xp);
    free(b);
}

int validInputInt(char *message, int min, int max) {
    int value = 0, validInput = 0;
    do {
        printf(GREEN);
        printf("%s", message);
        printf(RESET);
        validInput = scanf("%d", &value);
        if (validInput != 1 || value < min || value > max) {
            printf(RED);
            printf("Invalid input\n");
            printf(RESET);
        }
        fflush(stdin);
    } while (validInput != 1 || value < min || value > max);
    return value;
}

double validInputDouble(char *message, double min, double max) {
    double value = 0;
    int validInput = 0;
    do {
        printf(GREEN);
        printf("%s", message);
        printf(RESET);
        validInput = scanf("%lf", &value);
        if (validInput != 1 || value < min || value > max) {
            printf(RED);
            printf("Invalid input\n");
            printf(RESET);
        }
        fflush(stdin);
    } while (validInput != 1 || value < min || value > max);
    return value;
}

int validInputChoice(char *message, int choice1, int choice2) {
    int value = 0;
    do {
        printf(GREEN);
        printf("%s", message);
        printf(RESET);
        value = getch();
        if (value != choice1 && value != choice2) {
            printf(RED);
            printf("Invalid input\n");
            printf(RESET);
        }
        fflush(stdin);
    } while (value != choice1 && value != choice2);
    return value;
}

double random(double min, double max) {
    double range = (max - min);
    double div = RAND_MAX / range;
    return min + (rand() / div);
}

void manualMatrixFilling(int size, int min, int max, double **a, double *b) {
    printf(YELLOW);
    printf("Input matrix must be diagonally dominant (sum of non diagonal elements must be less the diagonal element in each row)\n");
    printf(RESET);
    double diagonalElement = 0, nonDiagonalElementSum = 0;
    for (int i = 0; i < size; i++) {
        diagonalElement = 0.0;
        do {
            nonDiagonalElementSum = 0.0;
            for (int j = 0; j < size; j++) {
                if (i == j) {
                    do {
                        printf("Enter a%d%d (Not 0)", i + 1, j + 1);
                        a[i][j] = validInputDouble("[-1000; 1000]: ", min, max);
                    } while (a[i][j] == 0);
                } else {
                    printf("Enter a%d%d ", i + 1, j + 1);
                    a[i][j] = validInputDouble("[-1000; 1000]: ", min, max);
                }
                if (i == j) {
                    diagonalElement = fabs(a[i][j]);
                } else {
                    nonDiagonalElementSum += fabs(a[i][j]);
                }
            }
            if (diagonalElement <= nonDiagonalElementSum) {
                printf(RED);
                printf("Input matrix isn`t diagonally dominant.\n");
                printf(RESET);
            }
        } while (diagonalElement <= nonDiagonalElementSum);
        printf("Enter b%d ", i + 1);
        b[i] = validInputDouble("[-1000; 1000]: ", min, max);
    }
}

void randomMatrixFilling(int size, int min, int max, double **a, double *b) {
    double nonDiagonalElementSum = 0;
    for (int i = 0; i < size; i++) {
        nonDiagonalElementSum = 0.0;
        for (int j = 0; j < size; j++) {
            if (i != j) {
                a[i][j] = random(min, max);
                nonDiagonalElementSum += fabs(a[i][j]);
            }
            a[i][i] = nonDiagonalElementSum + random(1.0, 10.0);
        }
        b[i] = random(min, max);
    }
}

void calculateSlae(double **a, const double *b, double *xp, double *x, int n, double epsilon) {
    double sum = 0.0, delta = 0.0, deltaMax = 0.0;
    do {
        deltaMax = 0.0;
        for (int i = 0; i < n; i++) {
            sum = 0.0;
            x[i] = b[i] / a[i][i];
            for (int j = 0; j < n; j++) {
                if (i != j) {
                    sum += a[i][j] * xp[j];
                }
            }
            x[i] = (b[i] - sum) / a[i][i];
            delta = fabs(x[i] - xp[i]);
        }
        if (deltaMax < delta) {
            deltaMax = delta;
        }
        for (int i = 0; i < n; i++) {
            xp[i] = x[i];
        }
    } while (epsilon < deltaMax);
}

void printElements(double *arr, int rows, unsigned precision) {
    for (int i = 0; i < rows; i++) {
        printf(BLUE);
        printf("x[%02d] = %.*lf\n", i + 1, precision, arr[i]);
        printf(RESET);
    }
}

void print_init_slae(double **a, const double *b, const int size) {
    printf("Initial SLAE:\n");
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if(j == 0) {
                printf(" %.1lf * x%d", a[i][j], j+1);
            } else {
                printf(" %+.1lf * x%d", a[i][j], j+1);
            }
        }
        printf(" = %.1lf\n", b[i]);
    }
}
#endif