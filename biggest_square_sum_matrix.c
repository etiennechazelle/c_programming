/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>

int main()
{
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);
    
    int mat[n][m];
    for (int i = 0 ; i < n ; i++) {
        for (int j = 0 ; j < m ; j++) {
            scanf("%d", &mat[i][j]);
        }
    }
    
    int max_sum = -100000000, ms_i = k - 1, ms_j = k - 1;
    int count = 0;
    for (int i = k - 1 ; i < n ; i++) {
        for (int j = k - 1 ; j < m ; j++) {
            // coin bas droite, on remonte en haut à gauche
            int sum = 0;
            for (int c = i - k + 1; c <= i ; c++) {
                for (int d = j - k + 1 ; d <= j ; d++) {
                    sum += mat[c][d];
                }
            }
            
            if (sum > max_sum) {
                max_sum = sum;
                ms_i = (i - k) + 1;
                ms_j = (j - k) + 1;
            }
        }
    }
    
    printf("%d %d %d", ms_i, ms_j, max_sum);
    
    return 0;
}