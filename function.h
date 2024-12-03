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
void printInitSlae( unsigned rows, double **a, double *b ) {
    printf("\nInitial SLAE: \n\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < rows; j++) {
            if(j == 0) {
                printf(" %.2lf*x%d", a[i][j], j+1);
            } else {
                printf(" %+.2lf*x%d", a[i][j], j+1);
            }
        }
        printf(" = %.2lf\n", b[i]);
    }
}

void print_elements(double *arr, int rows)
{
    for (int i = 0; i < rows; i++)
    {
        printf("[%02d] = %.10lf\n", i+1, arr[i]);
    }
}




#endif