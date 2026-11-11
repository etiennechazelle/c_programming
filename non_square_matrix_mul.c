#include <stdio.h>
#include <stdlib.h>
#define MAX 10

/* A est n x m, B est m x p, C est n x p */
void mul(int n, int m, int p,
         int Ar[][MAX], int Ai[][MAX], int Br[][MAX], int Bi[][MAX],
         int Cr[][MAX], int Ci[][MAX]) {
    for (int i = 0 ; i < n ; i++) {
        for (int j = 0 ; j < p ; j++) {
            Cr[i][j] = 0;
            Ci[i][j] = 0;
            for (int k = 0 ; k < m ; k++) {
                Cr[i][j] += Ar[i][k] * Br[k][j] - Ai[i][k] * Bi[k][j];
                Ci[i][j] += Ar[i][k] * Bi[k][j] + Ai[i][k] * Br[k][j];
            }
        }
    }
}

void print_complex(int re, int im) {
    if (re == 0 && im == 0) { printf("0"); return; }
    if (re != 0) printf("%d", re);
    if (im == 0) return;
    if (re != 0) printf("%s", im < 0 ? " - " : " + ");
    else if (im < 0) printf("-");
    int im_abs = abs(im);
    if (im_abs != 1) printf("%d", im_abs);
    printf("i");
}

void print_matrix(int rows, int cols, int Xr[][MAX], int Xi[][MAX]) {
    for (int i = 0 ; i < rows ; i++) {
        for (int j = 0 ; j < cols ; j++) {
            print_complex(Xr[i][j], Xi[i][j]);
            if (j != cols - 1) printf("\t");
        }
        printf("\n");
    }
}

int main(void) {
    int n, m, m2, p;
    int Ar[MAX][MAX], Ai[MAX][MAX], Br[MAX][MAX], Bi[MAX][MAX], Cr[MAX][MAX], Ci[MAX][MAX];

    scanf("%d %d", &n, &m);
    for (int i = 0 ; i < n ; i++) for (int j = 0 ; j < m ; j++) scanf("%d", &Ar[i][j]);
    for (int i = 0 ; i < n ; i++) for (int j = 0 ; j < m ; j++) scanf("%d", &Ai[i][j]);

    scanf("%d %d", &m2, &p);
    for (int i = 0 ; i < m2 ; i++) for (int j = 0 ; j < p ; j++) scanf("%d", &Br[i][j]);
    for (int i = 0 ; i < m2 ; i++) for (int j = 0 ; j < p ; j++) scanf("%d", &Bi[i][j]);

    printf("A * B :\n");
    if (m != m2) {
        printf("IMPOSSIBLE\n");
    } else {
        mul(n, m, p, Ar, Ai, Br, Bi, Cr, Ci);
        print_matrix(n, p, Cr, Ci);
    }
    return 0;
}