#include <stdio.h>
#define MAXN 100000

int is_prime[MAXN + 1];
int primes[MAXN + 1];

int main(void) {
    int n;
    scanf("%d", &n);

    for (int i = 0 ; i <= n ; i++) {
        is_prime[i] = 1;
    }
    is_prime[0] = is_prime[1] = 0;

    for (int p = 2 ; p * p <= n ; p++) {
        if (is_prime[p]) {
            for (int i = p * p ; i <= n ; i += p) {
                is_prime[i] = 0;
            }
        }
    }

    int count = 0;
    for (int i = 0 ; i <= n ; i++) {
        if (is_prime[i]) {
            primes[count] = i;
            count += 1;
        }
    }

    /* Paire de premiers jumeaux : on part de la fin de la liste des premiers */
    int twin = -1;
    for (int i = count - 1 ; i > 0 ; i--) {
        if (primes[i] - primes[i - 1] == 2) {
            twin = primes[i - 1];
            break;
        }
    }

    printf("Primes : %d\n", count);
    if (twin != -1) {
        printf("Twin : (%d, %d)\n", twin, twin + 2);
    } else {
        printf("Twin : none\n");
    }

    /* Decomposition de Goldbach */
    if (n % 2 == 1) {
        printf("Goldbach : odd\n");
    } else {
        int nb = 0, first = -1;
        for (int i = 0 ; i < count && primes[i] <= n / 2 ; i++) {
            int p = primes[i];
            if (is_prime[n - p]) {
                nb += 1;
                if (first == -1) first = p;
            }
        }
        printf("Goldbach : %d decompositions, first %d + %d\n", nb, first, n - first);
    }
    return 0;
}