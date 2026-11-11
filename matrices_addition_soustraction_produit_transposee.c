MATRICES : 

#include <stdio.h>

void add(int x, int y, int a[x][y], int b[x][y], int res[x][y]) {
    for (int i = 0 ; i < x ; i++) {
        for (int j = 0 ; j < y ; j++) {
            res[i][j] = a[i][j] + b[i][j];
        }
    }
}

void sub(int x, int y, int a[x][y], int b[x][y], int res[x][y]) {
    for (int i = 0 ; i < x ; i++) {
        for (int j = 0 ; j < y ; j++) {
            res[i][j] = a[i][j] - b[i][j];
        }
    }
}

/* Multiplication de deux matrices carrees n x n */
void mul(int n, int a[n][n], int b[n][n], int res[n][n]) {
    for (int i = 0 ; i < n ; i++) {
        for (int j = 0 ; j < n ; j++) {
            res[i][j] = 0;
            for (int k = 0 ; k < n ; k++) {
                res[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

/* mat est x lignes * y colonnes, res est y lignes * x colonnes */
void transpose(int x, int y, int mat[x][y], int res[y][x]) {
    for (int i = 0 ; i < x ; i++) {
        for (int j = 0 ; j < y ; j++) {
            res[j][i] = mat[i][j];
        }
    }
}

void print_matrix(int x, int y, int mat[x][y]) {
    for (int i = 0 ; i < x ; i++) {
        for (int j = 0 ; j < y ; j++) {
            printf("%d\t", mat[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    int row, col;
    scanf("%d %d", &row, &col);

    int A[row][col];
    for (int i = 0 ; i < row ; i++) {
        for (int j = 0 ; j < col ; j++) {
            scanf("%d", &A[i][j]);
        }
    }

    int B[row][col];
    for (int i = 0 ; i < row ; i++) {
        for (int j = 0 ; j < col ; j++) {
            scanf("%d", &B[i][j]);
        }
    }

    int AplusB[row][col];
    add(row, col, A, B, AplusB);
    printf("A + B :\n");
    print_matrix(row, col, AplusB);

    int AminusB[row][col];
    sub(row, col, A, B, AminusB);
    printf("A - B :\n");
    print_matrix(row, col, AminusB);

    if (row == col) {
        int AmulB[row][col];
        mul(row, A, B, AmulB);
        printf("A * B :\n");
        print_matrix(row, col, AmulB);
    } else {
        printf("A * B : impossible (matrices non carrees)\n");
    }

    int At[col][row];
    transpose(row, col, A, At);
    printf("At :\n");
    print_matrix(col, row, At);

    int Bt[col][row];
    transpose(row, col, B, Bt);
    printf("Bt :\n");
    print_matrix(col, row, Bt);

    return 0;
}




