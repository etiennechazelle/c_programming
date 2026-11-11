/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <math.h>

typedef struct {
    double x;
    double y;
} point;


double compute_distance(point a, point b) {
    return sqrt((b.x - a.x)*(b.x - a.x) + (b.y - a.y)*(b.y - a.y));
}


int main()
{
    
    // scanf
    int n;
    scanf("%d", &n);
    
    point points[n];
    for (int i = 0 ; i < n ; i++) {
        scanf("%lf", &points[i].x);
    }
    for (int i = 0 ; i < n ; i++) {
        scanf("%lf", &points[i].y);
    }
    
    
    // init dij
    int nb_dij = n * (n - 1) / 2;
    double dij[nb_dij];
    
    int min = floor(compute_distance(points[0], points[1]));
    int max = ceil(compute_distance(points[0], points[1]));
    
    int index = 0;
    for (int i = 0 ; i < n ; i++) {
        for (int j = 0 ; j < n ; j++) {
            if (i == j) {
                break;
            }
            double distance = compute_distance(points[i], points[j]);
            if (floor(distance) < min) {
                min = floor(distance);
            }
            if (ceil(distance) > max) {
                max = ceil(distance);
            }
            dij[index++] = distance;
        }
    }
    
    // bins
    int bins[20];
    for (int i = 0; i < 20 ; i++) {
        bins[i] = 0;
    }
    double edge_split = (max - min) / 20.0;
    for (int i = 0 ; i < nb_dij ; i++) {
        int bin_index = (dij[i] - min) / edge_split;
        if (bin_index > 20) bin_index = 20;
        bins[bin_index] += 1;;
    }
    
    for (int i = 0 ; i < 20 ; i++) {
        printf("%d ", bins[i]);
    }
    
    return 0;
}












SECOND VERSION /////////////////////////////



/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <math.h>

typedef struct {
    double x;
    double y;
} point;

double compute_distance(point a, point b) {
    return sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
}

int main()
{
    // init
    int n;
    scanf("%d", &n);
    
    point points[n];
    for (int i = 0 ; i < n ; i++) {
        scanf("%lf", &points[i].x);
    }
    for (int i = 0 ; i < n ; i++) {
        scanf("%lf", &points[i].y);
    }
    
    // compute
    int nb_distances = (n * (n - 1)) / 2, count = 0, max = ceil(compute_distance(points[0], points[1])), min = floor(compute_distance(points[0], points[1]));
    double distances[nb_distances];
    for (int i = 0 ; i < n ; i++) {
        for (int j = i + 1 ; j < n ; j++) {
            if (i != j) {
                distances[count] = compute_distance(points[i], points[j]);
                if (floor(distances[count]) < min) {
                    min = floor(distances[count]);
                }
                if (ceil(distances[count]) > max) {
                    max = ceil(distances[count]);
                }
                count += 1;
            }
        }
    }
    
    double interval = (max - min) / 20.0;
    int bins[20] = {0};
    
    for (int i = 0 ; i < nb_distances ; i++) {
        int bin_index = (distances[i] - min) / interval;
        if (bin_index >= 20) bin_index = 19;
        bins[bin_index] += 1;
    } 
    
    for (int i = 0 ; i < 20 ; i++) {
        printf("%d ", bins[i]);
    } 
    
    return 0;
}