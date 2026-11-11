#include <stdio.h>
#define MAX 20

int main(void) {
    int n, m;
    int mat[MAX][MAX];
    scanf("%d %d", &n, &m);

    int top = 0, bottom = n - 1, left = 0, right = m - 1;
    int value = 1;
    while (top <= bottom && left <= right) {
        for (int j = left ; j <= right ; j++) mat[top][j] = value++;
        top++;
        for (int i = top ; i <= bottom ; i++) mat[i][right] = value++;
        right--;
        if (top <= bottom) {
            for (int j = right ; j >= left ; j--) mat[bottom][j] = value++;
            bottom--;
        }
        if (left <= right) {
            for (int i = bottom ; i >= top ; i--) mat[i][left] = value++;
            left++;
        }
    }

    int width = 0;
    for (int v = n * m ; v > 0 ; v /= 10) width++;

    int trace = 0;
    for (int i = 0 ; i < n ; i++) {
        for (int j = 0 ; j < m ; j++) {
            if (j > 0) printf(" ");
            printf("%*d", width, mat[i][j]);
            if (i == j) trace += mat[i][j];
        }
        printf("\n");
    }
    printf("Trace : %d\n", trace);
    return 0;
}