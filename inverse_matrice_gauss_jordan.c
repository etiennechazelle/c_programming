#include <stdio.h>
#include <math.h>

/* evite d'afficher "-0.0000" */
double fix_zero(double x) {
    if (fabs(x) < 0.00005) return 0.0;
    return x;
}

int main(void) {
    int n;
    scanf("%d", &n);

    double mat[n][n];        /* la matrice A, qui deviendra l'identite */
    double inverse[n][n];    /* l'identite, qui deviendra l'inverse    */

    for (int i = 0 ; i < n ; i++) {
        for (int j = 0 ; j < n ; j++) {
            scanf("%lf", &mat[i][j]);
            inverse[i][j] = (i == j) ? 1.0 : 0.0;
        }
    }

    double det = 1.0;
    int is_singular = 0;

    for (int k = 0 ; k < n ; k++) {          /* k = colonne en cours de traitement */

        /* 1. chercher la ligne avec le plus grand pivot dans la colonne k */
        int best_row = k;
        for (int i = k + 1 ; i < n ; i++) {
            if (fabs(mat[i][k]) > fabs(mat[best_row][k])) {
                best_row = i;
            }
        }

        /* pivot nul : pas d'inverse */
        if (fabs(mat[best_row][k]) < 1e-9) {
            is_singular = 1;
            break;
        }

        /* 2. amener cette ligne en position k (dans les deux matrices) */
        if (best_row != k) {
            for (int j = 0 ; j < n ; j++) {
                double tmp = mat[best_row][j];
                mat[best_row][j] = mat[k][j];
                mat[k][j] = tmp;

                tmp = inverse[best_row][j];
                inverse[best_row][j] = inverse[k][j];
                inverse[k][j] = tmp;
            }
            det = -det;                      /* un echange change le signe */
        }

        /* 3. diviser la ligne k par le pivot */
        double pivot = mat[k][k];
        det = det * pivot;
        for (int j = 0 ; j < n ; j++) {
            mat[k][j] = mat[k][j] / pivot;
            inverse[k][j] = inverse[k][j] / pivot;
        }

        /* 4. annuler la colonne k dans toutes les autres lignes */
        for (int i = 0 ; i < n ; i++) {
            if (i == k) continue;
            double factor = mat[i][k];       /* a lire AVANT la boucle sur j */
            for (int j = 0 ; j < n ; j++) {
                mat[i][j] = mat[i][j] - factor * mat[k][j];
                inverse[i][j] = inverse[i][j] - factor * inverse[k][j];
            }
        }
    }

    if (is_singular) {
        printf("0.0000\n");
        printf("NO INVERSE\n");
        return 0;
    }

    printf("%.4f\n", fix_zero(det));
    for (int i = 0 ; i < n ; i++) {
        for (int j = 0 ; j < n ; j++) {
            if (j > 0) printf(" ");
            printf("%.4f", fix_zero(inverse[i][j]));
        }
        printf("\n");
    }
    return 0;
}