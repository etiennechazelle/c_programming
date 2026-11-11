/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>

int main()
{
    // scanf
    long long int N;
    scanf("%lld", &N);
    
    long long int primes[20];
    long long int powers[20];
    int c = 0;
    
    for (long long int i = 2 ; i*i <= N ; i++) {
        if (N % i == 0) {
            primes[c] = i;
            powers[c] = 0;
            while (N % i == 0) {
                N = N / i;
                powers[c] += 1;
            }
            c += 1;
        }
    }
    
    if (N > 1) {
        primes[c] = N;
        powers[c] = 1;
        c += 1;
    }
    
    for (int i = 0 ; i < c ; i++) {
        printf("%d", primes[i]);
        if (powers[i] > 1) {
            printf("^%lld", powers[i]);
        }
        if (i < c - 1) {
            printf(" * ");
        }
    }
    
    return 0;
}