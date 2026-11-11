CRIBLE ERATH : 

#include <stdio.h>

#define N 100

int main(void) {
    char est_premier[N + 1];

    for (int i = 0; i <= N; i++) est_premier[i] = 1;
    est_premier[0] = est_premier[1] = 0;

    for (int i = 2; i * i <= N; i++) {
        if (est_premier[i]) {
            for (int j = i * i; j <= N; j += i) {
                est_premier[j] = 0;
            }
        }
    }

    for (int i = 2; i <= N; i++) {
        if (est_premier[i]) printf("%d ", i);
    }
    printf("\n");
    return 0;
}

ECART TYPE : 

#include <stdio.h>
#include <math.h>

#define NB 6

int main(void) {
    double notes[NB] = {12.5, 15, 9, 18, 11.5, 14};
    double somme = 0, somme_carres = 0;

    for (int i = 0; i < NB; i++) somme += notes[i];
    double moyenne = somme / NB;

    for (int i = 0; i < NB; i++) {
        double ecart = notes[i] - moyenne;
        somme_carres += ecart * ecart;
    }
    double ecart_type = sqrt(somme_carres / NB);

    printf("Moyenne : %.2f\nEcart-type : %.2f\n", moyenne, ecart_type);
    return 0;
}

PRODUIT DE DEUX POLYNOMES : 

#include <stdio.h>

#define DEG_A 2
#define DEG_B 1

int main(void) {
    int a[DEG_A + 1] = {1, 2, 3};          /* 1 + 2x + 3x^2 */
    int b[DEG_B + 1] = {4, 5};             /* 4 + 5x */
    int c[DEG_A + DEG_B + 1] = {0};

    for (int i = 0; i <= DEG_A; i++)
        for (int j = 0; j <= DEG_B; j++)
            c[i + j] += a[i] * b[j];

    for (int k = 0; k <= DEG_A + DEG_B; k++)
        printf("%+d x^%d ", c[k], k);
    printf("\n");
    return 0;
}



TRIANGLE DE PASCAL : 

#include <stdio.h>

#define MAX     20   /* nombre maximal de lignes */
#define LARGEUR 7    /* largeur d'affichage de chaque nombre */

int main(void) {
    unsigned long long pascal[MAX][MAX] = {0};
    int n;

    printf("Nombre de lignes (1 a %d) : ", MAX);
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX) {
        printf("Valeur invalide.\n");
        return 1;
    }

    /* Calcul : chaque case est la somme des deux cases au-dessus */
    for (int i = 0; i < n; i++) {
        pascal[i][0] = 1;
        pascal[i][i] = 1;
        for (int j = 1; j < i; j++) {
            pascal[i][j] = pascal[i - 1][j - 1] + pascal[i - 1][j];
        }
    }

    /* Affichage centré */
    for (int i = 0; i < n; i++) {
        printf("%*s", (n - 1 - i) * LARGEUR / 2, "");
        for (int j = 0; j <= i; j++) {
            printf("%*llu", LARGEUR, pascal[i][j]);
        }
        printf("\n");
    }

    return 0;
}


#include <stdio.h>

#define LIGNES 8

int main(void) {
    int pascal[LIGNES][LIGNES] = {0};

    for (int i = 0; i < LIGNES; i++) {
        pascal[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            pascal[i][j] = pascal[i - 1][j - 1] + pascal[i - 1][j];
        }
    }

    for (int i = 0; i < LIGNES; i++) {
        for (int j = 0; j <= i; j++) printf("%d ", pascal[i][j]);
        printf("\n");
    }
    return 0;
}






