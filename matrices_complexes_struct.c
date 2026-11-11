MATRICES COMPLEXES : 
/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>

int n, m;

typedef struct {
    int re;
    int im;
} complex;

void add(complex A[][m], complex B[][m], complex C[][m], int row, int col) {
    for (int i = 0 ; i < row ; i++) {
        for (int j = 0 ; j < col ; j++) {
            C[i][j].re = A[i][j].re + B[i][j].re; 
            C[i][j].im = A[i][j].im + B[i][j].im; 
        }
    }
}

void sub(complex A[][m], complex B[][m], complex C[][m], int row, int col) {
    for (int i = 0 ; i < row ; i++) {
        for (int j = 0 ; j < col ; j++) {
            C[i][j].re = A[i][j].re - B[i][j].re; 
            C[i][j].im = A[i][j].im - B[i][j].im; 
        }
    }
}

void mul(complex A[][m], complex B[][m], complex C[][m], int row, int col) {
    for (int i = 0 ; i < row ; i++) {
        for (int j = 0 ; j < col ; j++) {
            C[i][j].re = 0;
            C[i][j].im = 0;
            for (int k = 0 ; k < col ; k++) {
                // (ac - bd) + (ad + bc)i
                int a = A[i][k].re;
                int b = A[i][k].im;
                int c = B[k][j].re;
                int d = B[k][j].im;
                C[i][j].re += a*c - b*d;
                C[i][j].im += a*d + b*c;
            }
        }
    }
}

void transpose(complex A[][m], complex At[][m], int row, int col) {
    for (int i = 0 ; i < row ; i++) {
        for (int j = 0 ; j < col ; j++) {
            At[i][j].re = A[j][i].re;
            At[i][j].im = A[j][i].im;
        }
    }
}

void print_complex(complex x) {
    if (x.re == 0 && x.im == 0) {
        printf("0");
        return;
    }
    
    if (x.re != 0) {
        printf("%d", x.re);
    }
    
    if (x.im == 0) {
        return;
    }
    
    if (x.re != 0) {
        printf(x.im < 0 ? " - " : " + ");
    } else if (x.im < 0) {
        printf("-");
    }
    
    int m = abs(x.im);
    if (m != 1) {
        printf("%d", m);
    }
    printf("i");
}

void print_matrix(complex A[][m], int row, int col) {
    for (int i = 0 ; i < row ; i++) {
        for (int j = 0 ; j < col ; j++) {
            print_complex(A[i][j]);
            if (j != col - 1) {
                printf("\t");
            }
        }
        printf("\n");
    }
}

int main()
{
    
    scanf("%d %d", &n, &m);
    
    complex A[n][m];
    for (int i = 0 ; i < n ; i++) {
        for (int j = 0 ; j < m ; j++) {
            scanf("%d", &A[i][j].re);
        }
    }
    for (int i = 0 ; i < n ; i++) {
        for (int j = 0 ; j < m ; j++) {
            scanf("%d", &A[i][j].im);
        }
    }
    
    complex B[n][m];
    for (int i = 0 ; i < n ; i++) {
        for (int j = 0 ; j < m ; j++) {
            scanf("%d", &B[i][j].re);
        }
    }
    for (int i = 0 ; i < n ; i++) {
        for (int j = 0 ; j < m ; j++) {
            scanf("%d", &B[i][j].im);
        }
    }
    
    printf("A + B :\n");
    complex AplusB[n][m];
    add(A, B, AplusB, n, m);
    print_matrix(AplusB, n, m);
    
    printf("A - B :\n");
    complex AminusB[n][m];
    sub(A, B, AminusB, n, m);
    print_matrix(AminusB, n, m);
    
    printf("A * B :\n");
    complex AmulbyB[n][m];
    mul(A, B, AmulbyB, n, m);
    print_matrix(AmulbyB, n, m);
    
    printf("A^T :\n");
    complex At[n][m];
    transpose(A, At, n, m);
    print_matrix(At, n, m);
    
    printf("B^T :\n");
    complex Bt[n][m];
    transpose(B, Bt, n, m);
    print_matrix(Bt, n, m);
    
    
    return 0;
}