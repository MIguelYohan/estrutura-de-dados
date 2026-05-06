#include <stdio.h>
#include <math.h>

#define EPSILON 1e-7
#define MAX_ITER 1000

typedef double (*Func)(double);

double f1(double x) {
    return x * x * x - x - 2;
}

double f2(double x) {
    return cos(x) - x;
}

double f3(double x) {
    return exp(-x) - x;
}

double f4(double x) {
    return x * x - 4;
}

double f5(double x) {
    return log(x) + x - 2;
}

double bisseccao(Func f, double a, double b){
    double mid;
    for (int i = 0; i < MAX_ITER; i++){
        mid = (a + b) / 2.0;
        if (f(mid) == 0.0 || (b - a) / 2.0 < EPSILON)
            break;
        if (f(a) * f(mid) < 0)
            b = mid;
        else
            a = mid;
    }
    return mid;
}

void resolver_todas(double raizes[5]){
    raizes[0] = bisseccao(f1, 1.0, 2.0);
    raizes[1] = bisseccao(f2, 0.0, 1.0);
    raizes[2] = bisseccao(f3, 0.0, 1.0);
    raizes[3] = bisseccao(f4, 0.0, 3.0);
    raizes[4] = bisseccao(f5, 1.0, 2.0);
}

int main(void)
{
    double raizes[5];
    resolver_todas(raizes);
    for (int i = 0; i < 5; i++)
        printf("%.6f\n", raizes[i]);
    return 0;
}