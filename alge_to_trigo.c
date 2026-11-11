#include <stdio.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

int main() {
    double a, b;
    double r, theta_rad, theta_deg;

    // 1. Saisie de la partie réelle et imaginaire
    printf("Entrez la partie reelle (a) : ");
    scanf("%lf", &a);
    printf("Entrez la partie imaginaire (b) : ");
    scanf("%lf", &b);

    // Cas particulier du nombre complexe nul
    if (a == 0 && b == 0) {
        printf("Le complexe est nul (z = 0), l'argument n'est pas defini.\n");
        return 0;
    }

    // 2. Calcul du module et de l'argument
    r = hypot(a, b);           // Module : sqrt(a^2 + b^2)
    theta_rad = atan2(b, a);   // Argument en radians dans ]-pi, pi]
    theta_deg = theta_rad * (180.0 / M_PI); // Conversion optionnelle en degrés

    // 3. Affichage du résultat
    printf("\nForme algebrique : z = %.2f + %.2fi\n", a, b);
    printf("Module (r)       : %.4f\n", r);
    printf("Argument (theta) : %.4f rad (%.2f degres)\n", theta_rad, theta_deg);
    printf("Forme trigo      : z = %.2f * (cos(%.2f) + i*sin(%.2f))\n", r, theta_rad, theta_rad);

    return 0;
}
