#include <stdio.h>

int main()
{
    int n;
    scanf("%d", &n);
    
    // get x values
    int x_values[n];
    for (int i = 0 ; i < n ; i++) {
        scanf("%d", &x_values[i]);
    }
    
    // get y values
    int y_values[n];
    for (int i = 0 ; i < n ; i++) {
        scanf("%d", &y_values[i]);
    }
    
    int values[n * 2];
    int indices[n * 2];
    int c = 0;
    for (int i = 0 ; i < n ; i++) {
        // start & end
        if (i == 0) {
            values[c] = y_values[i];
            indices[c] = x_values[i];
            c += 1;
            // CHANGE: guard so that n == 1 does not read out of bounds
            if (i + 1 < n && y_values[i + 1] > y_values[i]) {
                values[c] = y_values[i + 1];
                indices[c] = x_values[i];
                c += 1;
            }
        } else if (i == n - 1) {
            if (y_values[i - 1] > y_values[i]) {
                values[c] = y_values[i - 1];
                indices[c] = x_values[i];
                c += 1;
            }
            values[c] = y_values[i];
            indices[c] = x_values[i];
            c += 1;
        } else {
            // peak
            if (y_values[i + 1] < y_values[i] && y_values[i - 1] < y_values[i]) {
                values[c] = y_values[i];
                indices[c] = x_values[i];
                c += 1;
            } else {
                // others
                // CHANGE: value on the left and on the right of the sample point
                int left = y_values[i - 1] > y_values[i] ? y_values[i - 1] : y_values[i];
                int right = y_values[i + 1] > y_values[i] ? y_values[i + 1] : y_values[i];
                
                values[c] = left;
                indices[c] = x_values[i];
                c += 1;
                
                // only add a second point if there is a vertical jump
                if (right != left) {
                    values[c] = right;
                    indices[c] = x_values[i];
                    c += 1;
                }
            }
        }
    }
    
    // prints
    for (int i = 0 ; i < c ; i++) {
        printf("%d", indices[i]);
        if (i != c - 1) {
            printf(" ");
        } else {
            printf("\n");
        }
    }
    for (int i = 0 ; i < c ; i++) {
        printf("%d", values[i]);
        if (i != c - 1) {
            printf(" ");
        }
    }

    return 0;
}