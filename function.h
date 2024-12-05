#ifndef OP6_FUNCTION_H
#define OP6_FUNCTION_H

void freeArrays( int n,double *x ,double *b ,double *xp, double **a ) {
    for (int i = 0; i < n; i++) {
        free(a[i]);
    }
    free(x);
    free(b);
    free(xp);
    free(a);
}

int validInputInt ( char *message, int min, int max ) {
    int value = 0, validInput = 0;
    do
    {
        printf("%s", message);
        validInput = scanf("%d", &value);
        if (validInput != 1 || value < min || value > max)
        {
            printf("Invalid input\n");
        }
        fflush(stdin);
    } while (validInput != 1 || value < min || value > max);
    return value;
}

int validInputDouble ( char *message, double min, double max ) {
    double value = 0;
    int validInput = 0;
    do
    {
        printf("%s", message);
        validInput = scanf("%lf", &value);
        if (validInput != 1 || value < min || value > max)
        {
            printf("Invalid input\n");
        }
        fflush(stdin);
    } while (validInput != 1 || value < min || value > max);
    return value;
}

int validInputChoice ( char *message, int choice1, int choice2 ) {
    int value = 0;
    do
    {
        printf("%s", message);
        value = getch();
        if (value != choice1 && value != choice2)
        {
            printf("Invalid input\n");
        }
        fflush(stdin);
    } while (value != choice1 && value != choice2);
    return value;
}

double random( double min, double max ) {
    double range = (max - min);
    double div = RAND_MAX / range;
    return min + (rand() / div);
}

void randomMatrixFilling(int size, int min, int max, double **a, double *b ) {
    double nonDiagonalElementSum = 0;
    for (int i = 0; i < size; i++) {
        nonDiagonalElementSum = 0.0;
        for (int j = 0; j < size; j++) {
            if (i != j) {
                a[i][j] = random(min, max);
                nonDiagonalElementSum += fabs(a[i][j]);
            }
            a[i][i] = nonDiagonalElementSum + /*fabs(random(min, max))*/1.0;
        }
        b[i] = random(min, max);
    }
}

void manualMatrixFilling(int size, int min, int max, double **a, double *b ) {
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
                printf("Sum of non diagonal elements must be less then diagonal element\n");
            }
        } while (diagonalElement <= nonDiagonalElementSum);
        printf("Enter b%d ", i + 1);
        b[i] = validInputDouble("[-1000; 1000]: ", min, max);
    }
}

void calculateSlae( double **a, double *b, double *xp, double *x, int n, double epsilon ) {
    double sum = 0.0, delta = 0.0, deltaMax = 0.0;
    do {
        deltaMax = 0.0;
        for (int i = 0; i < n; i++) {
            sum = 0.0;
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

void printInitSlae( unsigned rows, double **a, double *b, int precision ) {
    printf("\nInitial SLAE: \n\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < rows; j++) {
            if(j == 0) {
                printf(" %.*lf*x%d", precision, a[i][j], j+1);
            } else {
                printf(" %+.*lf*x%d", precision, a[i][j], j+1);
            }
        }
        printf(" = %.*lf\n", precision, b[i]);
    }
}

void printElements( double *arr, int rows, int precision )
{
    for (int i = 0; i < rows; i++)
    {
        printf("x[%02d] = %.*lf\n", i+1, precision, arr[i]);
    }
}

#endif