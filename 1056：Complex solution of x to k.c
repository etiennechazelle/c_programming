
/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <math.h>

double a_first, b_first, c_first;
double intersection = 0;

void print_point(double x) {
    double y = a_first*x*x + b_first*x + c_first;
    printf("(%.4lf, %.4lf)\n", x, y);
    intersection = 1;
}

void print_roots(double a, double b, double c, double left, double right) {
    double delta = b*b - 4*a*c;
    if (delta == 0) {
        double x = -b / (2*a);
        if (x > left && x <= right) {
            print_point(x);
        }
    } else if (delta > 0) {
        double x1 = (-b - sqrt(delta)) / (2*a);
        double x2 = (-b + sqrt(delta)) / (2*a);
        if (x1 > x2) {
            double temp = x1;
            x1 = x2;
            x2 = temp;
        }
        if (x1 > left && x1 <= right) {
            print_point(x1);
        }
        if (x2 > left && x2 <= right) {
            print_point(x2);
        }
    }
}

int main()
{
    double d, e, L;
    scanf("%lf %lf %lf %lf %lf %lf", &a_first, &b_first, &c_first, &d, &e, &L);
    
    double left_limit = -(L * 10);
    double right_limit = L * 10;
    double interval = (L / 2);
    double L_mid = left_limit + interval;
    
    double a = a_first - d, b, c;
    
    while (left_limit <= right_limit) {
        b = b_first + (2 * d * L_mid);
        c = c_first - (d * (L_mid*L_mid) + e);
        // printf("a = %lf / b = %lf / c = %lf / left_limit = %lf / L_mid = %lf / left_limit + L = %lf\n", a, b, c, left_limit, L_mid, left_limit + L);
        print_roots(a, b, c, left_limit, left_limit + L);
        L_mid += L;
        left_limit += L;
    }
    
    if (!intersection) {
        printf("NO SOLUTION IS FOUND.");
    }
    return 0;
}