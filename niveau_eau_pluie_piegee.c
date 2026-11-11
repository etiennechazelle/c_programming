/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>

int main()
{
    int n;
    scanf("%d", &n);
    
    int hauteurs[n];
    for (int i = 0 ; i < n ; i++) {
        scanf("%d", &hauteurs[i]);
    }
    
    // hauteur max des barres de 0 à i
    int gauche[n];
    int max_g = 0;
    for (int i = 0 ; i < n ; i++) {
        if (hauteurs[i] > max_g) {
            max_g = hauteurs[i];
        }
        gauche[i] = max_g;
    }
    
    int droite[n];
    int max_d = 0;
    for (int i = n - 1 ; i >= 0 ; i--) {
        if (hauteurs[i] > max_d) {
            max_d = hauteurs[i];
        }
        droite[i] = max_d;
    }
    
    int niveau[n];
    int eau[n];
    long long int total = 0;
    for (int i = 0 ; i < n ; i++) {
        niveau[i] = gauche[i] < droite[i] ? gauche[i] : droite[i];
        eau[i] = niveau[i] - hauteurs[i];
        total += eau[i];
    }
    
    for (int i = 0 ; i < n ; i++) {
        if (i > 0) printf(" ");
        printf("%d", eau[i]);
    }
    printf("\n%lld", total);
    return 0;
}