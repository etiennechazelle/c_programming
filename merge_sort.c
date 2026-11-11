#include <stdio.h>
#define MAX 1000

int tmp[MAX];

void merge(int a[], int left, int mid, int right) {
    int i = left;
    int j = mid + 1;
    int k = left;

    while (i <= mid && j <= right) {
        if (a[i] <= a[j]) tmp[k++] = a[i++];
        else              tmp[k++] = a[j++];
    }
    while (i <= mid)   tmp[k++] = a[i++];
    while (j <= right) tmp[k++] = a[j++];

    for (k = left ; k <= right ; k++) a[k] = tmp[k];
}

void merge_sort(int a[], int left, int right) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    merge_sort(a, left, mid);
    merge_sort(a, mid + 1, right);
    merge(a, left, mid, right);
}

int main(void) {
    int a[MAX];
    int n;

    scanf("%d", &n);
    for (int i = 0 ; i < n ; i++) scanf("%d", &a[i]);

    merge_sort(a, 0, n - 1);

    for (int i = 0 ; i < n ; i++) {
        if (i > 0) printf(" ");
        printf("%d", a[i]);
    }
    printf("\n");
    return 0;
}