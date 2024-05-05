#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

double eps = 0.001;

double f1 (double x);

double f2 (double x);

double f3 (double x);

double root(double (*f)(double), double (*g)(double), double a, double b, double eps){
    double s = (a + b) / 2;
    if (f(a) * f(s) < 0){
        if ((b - a) > 2 * eps){
            return root(f, g, a, s, eps);
        } else{
            return s;
        }
    }
    if (f(b) * f(s) < 0){
        if ((b - a) > 2 * eps){
            return root(f, g, s, b, eps);
        } else{
            return s;
        }
    } else{
        return s;
    }
}

double integral(double (*f)(double), double a, double b, double eps){
    double s = 0, fl = a;
    while (fl < b){
        s += f(fl) * eps;
        fl += eps;
    }
    return s;
}

int main (int argc, char ** argv) {
    return 0;
}
