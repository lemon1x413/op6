#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "function.h"
#include <math.h>
#include <time.h>

#define MIN -1000
#define MAX 1000

int main() {
    srand(time(NULL));
    do {
        int size = validInputInt("Enter size of SLAE (from 2 to 10):\n", 2, 10);
        double eps = validInputDouble("Enter precision of calculations (from 1e-10 to 1e-3): ", 1e-10, 1e-3);

        double *x = calloc(size, sizeof(double));
        double *b = calloc(size, sizeof(double));
        double *xp = calloc(size, sizeof(double));
        double **a = calloc(size, sizeof(double *));
        for (int i = 0; i < size; i++) {
            a[i] = calloc(size, sizeof(double));
            if (a[i] == NULL) {
                printf("Memory allocation error!\n");
                freeArrays(size, x, b, xp, a);
                getch();
                return 0;
            }
        }
        if (x == NULL || b == NULL || xp == NULL || a == NULL) {
            printf("Memory allocation error!\n");
            freeArrays(size, x, b, xp, a);
            getch();
            return 0;
        }
        int choiceFilling = validInputChoice("Choose filling method (1 - manual input, 2 - random generated)\n", '1', '2');
        double diagonalElement = 0, nonDiagonalElementSum = 0;
        switch (choiceFilling) {
            case '1':
                for (int i = 0; i < size; i++) {
                    diagonalElement = 0.0;
                    do {
                        nonDiagonalElementSum = 0.0;
                        for (int j = 0; j < size; j++) {
                            if (i == j) {
                                do {
                                    printf("Enter a%d%d (Not 0)", i + 1, j + 1);
                                    a[i][j] = validInputDouble("[-1000; 1000]: ", MIN, MAX);
                                } while (a[i][j] == 0);
                            } else {
                                printf("Enter a%d%d ", i + 1, j + 1);
                                a[i][j] = validInputDouble("[-1000; 1000]: ", MIN, MAX);
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
                    b[i] = validInputDouble("[-1000; 1000]: ", MIN, MAX);
                }
                break;
            case '2':
                for (int i = 0; i < size; i++) {
                    nonDiagonalElementSum = 0.0;
                    for (int j = 0; j < size; j++) {
                        if (i != j) {
                            a[i][j] = random(MIN, MAX);
                            nonDiagonalElementSum += fabs(a[i][j]);
                        }
                        a[i][i] = nonDiagonalElementSum + random(MIN, MAX);
                    }
                    b[i] = random(MIN, MAX);
                }
                break;
            default:
                printf("Invalid input\n");
                break;
        }
        double sum = 0.0, delta = 0.0, deltaMax = 0.0;
        int iter = 0;
        do {
            deltaMax = 0.0;
            for (int i = 0; i < size; i++) {
                sum = 0.0;
                for (int j = 0; j < size; j++) {
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
            for (int i = 0; i < size; i++) {
                xp[i] = x[i];
            }
            iter++;
        } while (eps < deltaMax);

        print_elements(x, size);
        printInitSlae(size, a, b);
        printf("%d",iter);
        getch();
        freeArrays(size, x, b, xp, a);
        printf("Press ENTER to continue, or any other key to exit.");
    } while (getchar() == 13);
    return 0;
}