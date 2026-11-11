/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>

int min(int a, int b, int c) {
    int m = a;
    if (b < m) m = b;
    if (c < m) m = c;
    return m;
}

int main()
{
    int L, C;
    scanf("%d %d", &L, &C);
    
    int mat[L][C];
    for (int i = 0 ; i < L ; i++) {
        for (int j = 0 ; j < C ; j++) {
            scanf("%d", &mat[i][j]);
        }
    }
    
    int carre[L][C];
    int max_side = 0;
    int bottom_right_x = 0, bottom_right_y = 0;
    for (int i = 0 ; i < L ; i++) {
        for (int j = 0 ; j < C ; j++) {
            if (mat[i][j] == 0) {
                carre[i][j] = 0;
            } else if (i == 0 || j == 0) {
                carre[i][j] = mat[i][j];
            } else {
                carre[i][j] = min(carre[i - 1][j], carre[i][j - 1], carre[i - 1][j - 1]) + 1;
            }
            
            if (carre[i][j] > max_side) {
                    max_side = carre[i][j];
                    bottom_right_x = i;
                    bottom_right_y = j;
                }
        }
    }
    
    printf("%d\n", max_side);
    if (max_side > 0) {
        printf("%d %d", bottom_right_x - max_side + 1, bottom_right_y - max_side + 1);
    }
    
    return 0;
}