#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <time.h>
#include "function.h"

#define MIN -1000
#define MAX 1000
#define MIN_SIZE 2
#define MAX_SIZE 100
#define MIN_EPS 1e-15
#define MAX_EPS 1e-1
#define ENTER 13

#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define BLUE "\x1b[36m"
#define YELLOW  "\x1b[33m"
#define RESET "\033[0m"

int main() {
    srand(time(NULL));
    do {
        printf(YELLOW);
        printf("This program solves SLAE\n");
        printf(RESET);
        int size = validInputInt("Enter size of SLAE (from 2 to 100):\n", MIN_SIZE, MAX_SIZE);
        double epsilon = validInputDouble("Enter precision of calculations (from 1e-15 to 1e-1):\n", MIN_EPS, MAX_EPS);
        unsigned precision = (unsigned) fabs(log10(epsilon));
        double *x = calloc(size, sizeof(double));
        double *b = calloc(size, sizeof(double));
        double *xp = calloc(size, sizeof(double));
        double **a = calloc(size, sizeof(double *));
        for (int i = 0; i < size; i++) {
            a[i] = calloc(size, sizeof(double));
            if (a[i] == NULL) {
                freeArrays(size, a, xp, x, b);
                return 0;
            }
        }
        if (x == NULL || b == NULL || xp == NULL || a == NULL) {
            freeArrays(size, a, xp, x, b);
            return 0;
        }
        int choiceMatrixFilling = validInputChoice("Choose filling method (1 - manual input, 2 - random generated)\n",
                                                   '1', '2');
        switch (choiceMatrixFilling) {
            case '1':
                manualMatrixFilling(size, MIN, MAX, a, b);
                break;
            case '2':
                randomMatrixFilling(size, MIN, MAX, a, b);
                break;
            default:
                printf("Invalid input\n");
                break;
        }
        calculateSlae(a, b, xp, x, size, epsilon);
        printElements(x, size, precision);
        print_init_slae(a, b, size);
        freeArrays(size, a, xp, x, b);
        printf(YELLOW);
        printf("Press ENTER to continue, or any other key to exit.\n");
        printf(RESET);
    } while (getch() == ENTER);
    return 0;
}