#include <stdio.h>
#define MAX 20

/* prints `count` elements starting at `start`, `stride` positions apart */
static void print_strided(int *start, int count, int stride) {
    for (int t = 0 ; t < count ; t++) {
        if (t > 0) printf(" ");
        printf("%d", *(start + t * stride));
    }
    printf("\n");
}

int main(void) {
    int a[MAX * MAX];
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 0 ; i < n * m ; i++) scanf("%d", a + i);

    int small = n < m ? n : m;          /* length of both diagonals */
    char q;
    while (scanf(" %c", &q) == 1) {
        if (q == 'R') {
            int i; scanf("%d", &i);
            print_strided(a + (i - 1) * m, m, 1);
        } else if (q == 'C') {
            int j; scanf("%d", &j);
            print_strided(a + (j - 1), n, m);
        } else if (q == 'D') {
            print_strided(a, small, m + 1);
        } else if (q == 'A') {
            print_strided(a + (m - 1), small, m - 1);
        } else if (q == 'E') {
            int s; scanf("%d", &s);
            print_strided(a, (n * m + s - 1) / s, s);
        } else if (q == 'S') {
            int i, j, h, w, sum = 0;
            scanf("%d %d %d %d", &i, &j, &h, &w);
            int *p = a + (i - 1) * m + (j - 1);
            for (int r = 0 ; r < h ; r++)
                for (int c = 0 ; c < w ; c++)
                    sum += *(p + r * m + c);
            printf("%d\n", sum);
        }
    }
    return 0;
}