/*
 * Boite a outils : matrices de nombres complexes (sans struct)
 *
 * Chaque matrice complexe = deux matrices de reels : partie reelle (xr) et partie imaginaire (xi).
 *
 * ENTREE
 *   n m
 *   <n lignes : parties reelles de A>
 *   <n lignes : parties imaginaires de A>
 *   <n lignes : parties reelles de B>
 *   <n lignes : parties imaginaires de B>
 *   puis des questions, une par ligne, jusqu'a la fin de l'entree :
 *     A + B    A - B    A * B     (et B + A, A * A, ... : n'importe quelle combinaison de A et B)
 *     T A      transposee
 *     H A      transposee conjuguee
 *     C A      conjuguee (on change le signe des parties imaginaires)
 *     INV A    inverse (elimination de Gauss avec division complexe)
 *     DET A    determinant
 *     TR A     trace
 *     MOD A    module |z| de chaque element
 *
 * SORTIE : une ligne de titre ("A + B :"), puis le resultat (colonnes separees par une tabulation).
 *   Un resultat impossible (produit/inverse/det/trace d'une matrice non carree) s'ecrit IMPOSSIBLE,
 *   une matrice non inversible s'ecrit NO INVERSE.
 *
 * FORMAT d'un complexe : 4 decimales, jamais "-0.0000", pas de partie nulle, "3.0000 - 2.5000i".
 */
#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAX 10
#define SHORT_I 1      /* 1 : |partie imaginaire| = 1.0000 s'ecrit "i" ; 0 : "1.0000i" */
#define EPS 1e-9

/* ---------- affichage ---------- */

double round4(double x) {
    double q = round(x * 10000.0) / 10000.0;
    return q == 0.0 ? 0.0 : q;                 /* supprime le "-0.0000" */
}

void print_complex(double re, double im) {
    double r = round4(re), m = round4(im);
    if (r == 0.0 && m == 0.0) { printf("0.0000"); return; }
    if (m == 0.0) { printf("%.4f", r); return; }
    if (r != 0.0) printf("%.4f", r);
    if (r != 0.0) printf("%s", m < 0 ? " - " : " + ");
    else if (m < 0) printf("-");
    double a = fabs(m);
    if (SHORT_I && a == 1.0) printf("i");
    else printf("%.4fi", a);
}

void print_matrix(int rows, int cols, double xr[][MAX], double xi[][MAX]) {
    for (int i = 0 ; i < rows ; i++) {
        for (int j = 0 ; j < cols ; j++) {
            print_complex(xr[i][j], xi[i][j]);
            if (j != cols - 1) printf("\t");
        }
        printf("\n");
    }
}

/* ---------- operations sur un nombre complexe (a + bi) et (c + di) ---------- */

void cmul(double a, double b, double c, double d, double *re, double *im) {
    *re = a * c - b * d;
    *im = a * d + b * c;
}

void cdiv(double a, double b, double c, double d, double *re, double *im) {
    double den = c * c + d * d;
    *re = (a * c + b * d) / den;
    *im = (b * c - a * d) / den;
}

/* ---------- operations sur les matrices ---------- */

void add(int n, int m, double ar[][MAX], double ai[][MAX], double br[][MAX], double bi[][MAX],
         double cr[][MAX], double ci[][MAX]) {
    for (int i = 0 ; i < n ; i++)
        for (int j = 0 ; j < m ; j++) {
            cr[i][j] = ar[i][j] + br[i][j];
            ci[i][j] = ai[i][j] + bi[i][j];
        }
}

void sub(int n, int m, double ar[][MAX], double ai[][MAX], double br[][MAX], double bi[][MAX],
         double cr[][MAX], double ci[][MAX]) {
    for (int i = 0 ; i < n ; i++)
        for (int j = 0 ; j < m ; j++) {
            cr[i][j] = ar[i][j] - br[i][j];
            ci[i][j] = ai[i][j] - bi[i][j];
        }
}

/* matrices carrees n x n */
void mul(int n, double ar[][MAX], double ai[][MAX], double br[][MAX], double bi[][MAX],
         double cr[][MAX], double ci[][MAX]) {
    for (int i = 0 ; i < n ; i++)
        for (int j = 0 ; j < n ; j++) {
            cr[i][j] = 0;
            ci[i][j] = 0;
            for (int k = 0 ; k < n ; k++) {
                double pr, pi;
                cmul(ar[i][k], ai[i][k], br[k][j], bi[k][j], &pr, &pi);
                cr[i][j] += pr;
                ci[i][j] += pi;
            }
        }
}

/* x est n x m, t est m x n ; conj = 1 : transposee conjuguee */
void transpose(int n, int m, double xr[][MAX], double xi[][MAX], double tr[][MAX], double ti[][MAX], int conj) {
    for (int i = 0 ; i < n ; i++)
        for (int j = 0 ; j < m ; j++) {
            tr[j][i] = xr[i][j];
            ti[j][i] = conj ? -xi[i][j] : xi[i][j];
        }
}

void conjugate(int n, int m, double xr[][MAX], double xi[][MAX], double cr[][MAX], double ci[][MAX]) {
    for (int i = 0 ; i < n ; i++)
        for (int j = 0 ; j < m ; j++) {
            cr[i][j] = xr[i][j];
            ci[i][j] = -xi[i][j];
        }
}

/*
 * Elimination de Gauss-Jordan sur (w | v), ou v part de l'identite.
 * A la fin : w = identite, v = inverse, et *detr + *deti i = determinant.
 * Retourne 0 si la matrice est singuliere (aucun pivot de module >= EPS), 1 sinon.
 */
int gauss(int n, double wr[][MAX], double wi[][MAX], double vr[][MAX], double vi[][MAX],
          double *detr, double *deti) {
    for (int i = 0 ; i < n ; i++)
        for (int j = 0 ; j < n ; j++) {
            vr[i][j] = (i == j) ? 1.0 : 0.0;
            vi[i][j] = 0.0;
        }
    *detr = 1.0;
    *deti = 0.0;

    for (int k = 0 ; k < n ; k++) {
        int best = k;
        for (int i = k + 1 ; i < n ; i++)
            if (hypot(wr[i][k], wi[i][k]) > hypot(wr[best][k], wi[best][k])) best = i;
        if (hypot(wr[best][k], wi[best][k]) < EPS) {
            *detr = 0.0;
            *deti = 0.0;
            return 0;
        }
        if (best != k) {
            for (int j = 0 ; j < n ; j++) {
                double t;
                t = wr[best][j]; wr[best][j] = wr[k][j]; wr[k][j] = t;
                t = wi[best][j]; wi[best][j] = wi[k][j]; wi[k][j] = t;
                t = vr[best][j]; vr[best][j] = vr[k][j]; vr[k][j] = t;
                t = vi[best][j]; vi[best][j] = vi[k][j]; vi[k][j] = t;
            }
            *detr = -*detr;
            *deti = -*deti;
        }

        double pr = wr[k][k], pi = wi[k][k], a, b;
        cmul(*detr, *deti, pr, pi, &a, &b);
        *detr = a;
        *deti = b;
        for (int j = 0 ; j < n ; j++) {
            cdiv(wr[k][j], wi[k][j], pr, pi, &a, &b); wr[k][j] = a; wi[k][j] = b;
            cdiv(vr[k][j], vi[k][j], pr, pi, &a, &b); vr[k][j] = a; vi[k][j] = b;
        }

        for (int i = 0 ; i < n ; i++) {
            if (i == k) continue;
            double fr = wr[i][k], fi = wi[i][k];
            for (int j = 0 ; j < n ; j++) {
                cmul(fr, fi, wr[k][j], wi[k][j], &a, &b); wr[i][j] -= a; wi[i][j] -= b;
                cmul(fr, fi, vr[k][j], vi[k][j], &a, &b); vr[i][j] -= a; vi[i][j] -= b;
            }
        }
    }
    return 1;
}

/* ---------- programme principal ---------- */

int main(void) {
    int n, m;
    double Ar[MAX][MAX], Ai[MAX][MAX], Br[MAX][MAX], Bi[MAX][MAX];
    double Rr[MAX][MAX], Ri[MAX][MAX];          /* resultat */
    double Wr[MAX][MAX], Wi[MAX][MAX];          /* copie de travail pour Gauss */
    double Vr[MAX][MAX], Vi[MAX][MAX];          /* inverse */

    scanf("%d %d", &n, &m);
    for (int i = 0 ; i < n ; i++) for (int j = 0 ; j < m ; j++) scanf("%lf", &Ar[i][j]);
    for (int i = 0 ; i < n ; i++) for (int j = 0 ; j < m ; j++) scanf("%lf", &Ai[i][j]);
    for (int i = 0 ; i < n ; i++) for (int j = 0 ; j < m ; j++) scanf("%lf", &Br[i][j]);
    for (int i = 0 ; i < n ; i++) for (int j = 0 ; j < m ; j++) scanf("%lf", &Bi[i][j]);

    char t1[16];
    while (scanf("%15s", t1) == 1) {
        if (strcmp(t1, "A") == 0 || strcmp(t1, "B") == 0) {
            /* question binaire : X op Y */
            char op[4], t2[4];
            scanf("%3s %3s", op, t2);
            double (*xr)[MAX] = (t1[0] == 'A') ? Ar : Br;
            double (*xi)[MAX] = (t1[0] == 'A') ? Ai : Bi;
            double (*yr)[MAX] = (t2[0] == 'A') ? Ar : Br;
            double (*yi)[MAX] = (t2[0] == 'A') ? Ai : Bi;
            printf("%s %s %s :\n", t1, op, t2);
            if (op[0] == '+') {
                add(n, m, xr, xi, yr, yi, Rr, Ri);
                print_matrix(n, m, Rr, Ri);
            } else if (op[0] == '-') {
                sub(n, m, xr, xi, yr, yi, Rr, Ri);
                print_matrix(n, m, Rr, Ri);
            } else if (op[0] == '*') {
                if (n != m) printf("IMPOSSIBLE\n");
                else { mul(n, xr, xi, yr, yi, Rr, Ri); print_matrix(n, n, Rr, Ri); }
            }
        } else {
            /* question unitaire : COMMANDE X */
            char t2[4];
            scanf("%3s", t2);
            double (*xr)[MAX] = (t2[0] == 'A') ? Ar : Br;
            double (*xi)[MAX] = (t2[0] == 'A') ? Ai : Bi;
            printf("%s %s :\n", t1, t2);
            if (strcmp(t1, "T") == 0 || strcmp(t1, "H") == 0) {
                transpose(n, m, xr, xi, Rr, Ri, t1[0] == 'H');
                print_matrix(m, n, Rr, Ri);
            } else if (strcmp(t1, "C") == 0) {
                conjugate(n, m, xr, xi, Rr, Ri);
                print_matrix(n, m, Rr, Ri);
            } else if (strcmp(t1, "MOD") == 0) {
                for (int i = 0 ; i < n ; i++) {
                    for (int j = 0 ; j < m ; j++) {
                        if (j > 0) printf("\t");
                        printf("%.4f", round4(hypot(xr[i][j], xi[i][j])));
                    }
                    printf("\n");
                }
            } else if (strcmp(t1, "TR") == 0) {
                if (n != m) printf("IMPOSSIBLE\n");
                else {
                    double sr = 0, si = 0;
                    for (int i = 0 ; i < n ; i++) { sr += xr[i][i]; si += xi[i][i]; }
                    print_complex(sr, si);
                    printf("\n");
                }
            } else if (strcmp(t1, "DET") == 0 || strcmp(t1, "INV") == 0) {
                if (n != m) printf("IMPOSSIBLE\n");
                else {
                    for (int i = 0 ; i < n ; i++)
                        for (int j = 0 ; j < n ; j++) { Wr[i][j] = xr[i][j]; Wi[i][j] = xi[i][j]; }
                    double dr, di;
                    int ok = gauss(n, Wr, Wi, Vr, Vi, &dr, &di);
                    if (strcmp(t1, "DET") == 0) {
                        print_complex(dr, di);
                        printf("\n");
                    } else if (!ok) {
                        printf("NO INVERSE\n");
                    } else {
                        print_matrix(n, n, Vr, Vi);
                    }
                }
            }
        }
    }
    return 0;
}
