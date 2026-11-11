#include <stdio.h>
#include <stdlib.h>

/* C = A + B, parties reelle (Xr) et imaginaire (Xi) separees */
void add(int row, int col,
         int Ar[row][col], int Ai[row][col],
         int Br[row][col], int Bi[row][col],
         int Cr[row][col], int Ci[row][col]) {
    for (int i = 0 ; i < row ; i++) {
        for (int j = 0 ; j < col ; j++) {
            Cr[i][j] = Ar[i][j] + Br[i][j];
            Ci[i][j] = Ai[i][j] + Bi[i][j];
        }
    }
}

void sub(int row, int col,
         int Ar[row][col], int Ai[row][col],
         int Br[row][col], int Bi[row][col],
         int Cr[row][col], int Ci[row][col]) {
    for (int i = 0 ; i < row ; i++) {
        for (int j = 0 ; j < col ; j++) {
            Cr[i][j] = Ar[i][j] - Br[i][j];
            Ci[i][j] = Ai[i][j] - Bi[i][j];
        }
    }
}

/* matrices carrees n x n */
void mul(int n,
         int Ar[n][n], int Ai[n][n],
         int Br[n][n], int Bi[n][n],
         int Cr[n][n], int Ci[n][n]) {
    for (int i = 0 ; i < n ; i++) {
        for (int j = 0 ; j < n ; j++) {
            Cr[i][j] = 0;
            Ci[i][j] = 0;
            for (int k = 0 ; k < n ; k++) {
                int a = Ar[i][k], b = Ai[i][k];
                int c = Br[k][j], d = Bi[k][j];
                Cr[i][j] += a * c - b * d;
                Ci[i][j] += a * d + b * c;
            }
        }
    }
}

/* X est row x col, T est col x row */
void transpose(int row, int col, int X[row][col], int T[col][row]) {
    for (int i = 0 ; i < row ; i++) {
        for (int j = 0 ; j < col ; j++) {
            T[j][i] = X[i][j];
        }
    }
}

void print_complex(int re, int im) {
    if (re == 0 && im == 0) {
        printf("0");
        return;
    }
    if (re != 0) {
        printf("%d", re);
    }
    if (im == 0) {
        return;
    }
    if (re != 0) {
        printf("%s", im < 0 ? " - " : " + ");
    } else if (im < 0) {
        printf("-");
    }
    int im_abs = abs(im);
    if (im_abs != 1) {
        printf("%d", im_abs);
    }
    printf("i");
}

void print_matrix(int row, int col, int Xr[row][col], int Xi[row][col]) {
    for (int i = 0 ; i < row ; i++) {
        for (int j = 0 ; j < col ; j++) {
            print_complex(Xr[i][j], Xi[i][j]);
            if (j != col - 1) {
                printf("\t");
            }
        }
        printf("\n");
    }
}

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);

    int Ar[n][m], Ai[n][m], Br[n][m], Bi[n][m];
    for (int i = 0 ; i < n ; i++) for (int j = 0 ; j < m ; j++) scanf("%d", &Ar[i][j]);
    for (int i = 0 ; i < n ; i++) for (int j = 0 ; j < m ; j++) scanf("%d", &Ai[i][j]);
    for (int i = 0 ; i < n ; i++) for (int j = 0 ; j < m ; j++) scanf("%d", &Br[i][j]);
    for (int i = 0 ; i < n ; i++) for (int j = 0 ; j < m ; j++) scanf("%d", &Bi[i][j]);

    int Cr[n][m], Ci[n][m];

    printf("A + B :\n");
    add(n, m, Ar, Ai, Br, Bi, Cr, Ci);
    print_matrix(n, m, Cr, Ci);

    printf("A - B :\n");
    sub(n, m, Ar, Ai, Br, Bi, Cr, Ci);
    print_matrix(n, m, Cr, Ci);

    printf("A * B :\n");
    if (n != m) {
        printf("IMPOSSIBLE\n");
    } else {
        mul(n, Ar, Ai, Br, Bi, Cr, Ci);
        print_matrix(n, n, Cr, Ci);
    }

    int Tr[m][n], Ti[m][n];

    printf("A^T :\n");
    transpose(n, m, Ar, Tr);
    transpose(n, m, Ai, Ti);
    print_matrix(m, n, Tr, Ti);

    printf("B^T :\n");
    transpose(n, m, Br, Tr);
    transpose(n, m, Bi, Ti);
    print_matrix(m, n, Tr, Ti);

    return 0;
}