#include <stdio.h>
#define MAX 20

int n, m;
int grid[MAX][MAX];
int seen[MAX][MAX];

/* parcours en profondeur : retourne la taille de l'ile contenant (i, j) */
int explore(int i, int j) {
    if (i < 0 || i >= n || j < 0 || j >= m) return 0;   /* hors de la grille */
    if (grid[i][j] == 0 || seen[i][j]) return 0;        /* eau, ou deja visitee */
    seen[i][j] = 1;
    return 1 + explore(i + 1, j) + explore(i - 1, j) + explore(i, j + 1) + explore(i, j - 1);
}

int main(void) {
    scanf("%d %d", &n, &m);
    for (int i = 0 ; i < n ; i++)
        for (int j = 0 ; j < m ; j++)
            scanf("%d", &grid[i][j]);

    int sizes[MAX * MAX];
    int count = 0;
    for (int i = 0 ; i < n ; i++)
        for (int j = 0 ; j < m ; j++)
            if (grid[i][j] == 1 && !seen[i][j])
                sizes[count++] = explore(i, j);

    /* tri decroissant */
    for (int i = 0 ; i < count - 1 ; i++)
        for (int j = i + 1 ; j < count ; j++)
            if (sizes[j] > sizes[i]) { int t = sizes[i]; sizes[i] = sizes[j]; sizes[j] = t; }

    printf("Islands : %d\n", count);
    printf("Largest : %d\n", count > 0 ? sizes[0] : 0);
    printf("Sizes :");
    if (count == 0) printf(" none");
    for (int i = 0 ; i < count ; i++) printf(" %d", sizes[i]);
    printf("\n");
    return 0;
}