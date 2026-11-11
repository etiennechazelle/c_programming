#include <stdio.h>
#define MAX 20

/* indice de la ligne qui a la plus petite valeur en colonne k, parmi start..n-1.
   Comparaison stricte (<) : en cas d'egalite, on garde la PREMIERE. */
int find_min_index(int **rows, int n, int k, int start) {
    int min_index = start;
    for (int i = start + 1 ; i < n ; i++) {
        if (*(*(rows + i) + k) < *(*(rows + min_index) + k)) {
            min_index = i;
        }
    }
    return min_index;
}

void sort_rows(int **rows, int n, int m, int k) {
    (void)m;
    for (int i = 0 ; i < n - 1 ; i++) {
        int idx = find_min_index(rows, n, k, i);
        int *min_row = *(rows + idx);
        for (int j = idx ; j > i ; j--) {      /* decale pour rester stable */
            *(rows + j) = *(rows + j - 1);
        }
        *(rows + i) = min_row;
    }
}

void print_rows(int **rows, int n, int m) {
    for (int i = 0 ; i < n ; i++) {
        for (int j = 0 ; j < m ; j++) {
            if (j > 0) printf(" ");
            printf("%d", *(*(rows + i) + j));
        }
        printf("\n");
    }
}
int main(void) {
    int data[MAX * MAX];
    int *rows[MAX];
    int n, m, k;
    scanf("%d %d", &n, &m);
    for (int i = 0 ; i < n * m ; i++) scanf("%d", data + i);
    for (int i = 0 ; i < n ; i++) rows[i] = data + i * m;

    printf("Original :\n");
    print_rows(rows, n, m);
    while (scanf("%d", &k) == 1) {
        sort_rows(rows, n, m, k - 1);
        printf("Sorted by column %d :\n", k);
        print_rows(rows, n, m);
    }
    printf("Memory :\n");
    for (int i = 0 ; i < n * m ; i++) {
        if (i > 0) printf(" ");
        printf("%d", *(data + i));
    }
    printf("\n");
    return 0;
}