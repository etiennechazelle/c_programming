/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#define MAT_SIZE 5

int find_index_min_r(int mat[][MAT_SIZE], int x, int start, int size) {
    int min = mat[x][start];
    int index_of_min = start;
    for (int i = start ; i < size ; i++) {
        if (mat[x][i] < min) {
            min = mat[x][i];
            index_of_min = i;
        }
    }
    return index_of_min;
}

int find_index_min_c(int mat[][MAT_SIZE], int y, int start, int size) {
    int min = mat[start][y];
    int index_of_min = start;
    for (int i = start ; i < size ; i++) {
        if (mat[i][y] < min) {
            min = mat[i][y];
            index_of_min = i;
        }
    }
    return index_of_min;
}

void swap_r(int mat[][MAT_SIZE], int a, int b, int size) {
    for (int i = 0 ; i < size ; i++) {
        int temp = mat[a][i];
        mat[a][i] = mat[b][i];
        mat[b][i] = temp;
    }
}

void swap_c(int mat[][MAT_SIZE], int a, int b, int size) {
    for (int i = 0 ; i < size ; i++) {
        int temp = mat[i][a];
        mat[i][a] = mat[i][b];
        mat[i][b] = temp;
    }
}

void order_r(int mat[][MAT_SIZE], int xy, int n) {
    for (int i = 0 ; i < n ; i++) {
        int min_index = find_index_min_r(mat, xy, i, n);
        swap_c(mat, min_index, i, n);
    }
}

void order_c(int mat[][MAT_SIZE], int xy, int n) {
    for (int i = 0 ; i < n ; i++) {
        int min_index = find_index_min_c(mat, xy, i, n);
        swap_r(mat, min_index, i, n);
    }
}

void print_matrix(int mat[][MAT_SIZE], int x_size, int y_size) {
    for (int i = 0 ; i < x_size ; i++) {
        for (int j = 0 ; j < y_size ; j++) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    // scan
    int xy;
    char rc_char;
    scanf("%d %c", &xy, &rc_char);
    
    // init
    int mat[5][5] = {
        {64, 94, 21, 19, 31},
        {38, 88, 30, 23, 92},
        {81, 55, 47, 17, 43},
        {53, 62, 23, 23, 18},
        {35, 59, 84, 44, 90}
    };
    
    if (rc_char == 'r') {
        order_r(mat, xy - 1, 5);
    } else if (rc_char == 'c') {
        order_c(mat, xy - 1, 5);
    }
    
    print_matrix(mat, 5, 5);
    
    return 0;
}