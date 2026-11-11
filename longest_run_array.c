#include <stdio.h>

#define MAX 1000

int *longest_run(int *first, int *last, int *length) {
    int *best_start = first;
    int best_len = 1;
    int *run_start = first;

    for (int *p = first + 1 ; p < last ; p++) {
        if (*p <= *(p - 1)) {
            run_start = p;
        }
        int run_len = p - run_start + 1;
        if (run_len > best_len) {
            best_len = run_len;
            best_start = run_start;
        }
    }

    *length = best_len;
    return best_start;
}

int main()
{
    int n;
    scanf("%d", &n);

    int arr[MAX];
    for (int i = 0 ; i < n ; i++) {
        scanf("%d", &arr[i]);
    }

    int length;
    int *start = longest_run(arr, arr + n, &length);

    printf("%d %d\n", (int)(start - arr), length);

    return 0;
}