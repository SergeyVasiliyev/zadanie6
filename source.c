#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

double eps = 0.0001;

int num_of_iterations = 0;

double f1 (double x);

double f2 (double x);

double f3 (double x);

double f4(double x){
    return 2 * x;
}

double f5(double x){
    return 3 + x;
}

double f6(double x){
    return 1 - x*x;
}

double (*functions[6])(double) = {&f1, &f2, &f3, &f4, &f5, &f6};

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

void print_roots(void){
    double root1 = root(f1, f2, 0, 2, eps);
    double root2 = root(f1, f3, -3, 0, eps);
    double root3 = root(f2, f3, -1, 1, eps);
    printf("root f1, f2: %lf\nroot f1, f3: %lf\nroot f2, f3: %lf\n", root1, root2, root3);
}

void print_integrals(void){
    double root1 = root(f1, f2, 0, 2, eps);
    double root2 = root(f1, f3, -3, 0, eps);
    double root3 = root(f2, f3, -1, 1, eps);
    double I_f1 = integral(f1, root2, root1, eps);
    double I_f2 = integral(f2, root3, root1, eps);
    double I_f3 = integral(f3 ,root2, root3, eps);
    printf("integral f1: %lf\nintegral f2: %lf\nintegral f3: %lf\n", I_f1, I_f2, I_f3);
}

void print_answer(void){
    double root1 = root(f1, f2, 0, 2, eps);
    double root2 = root(f1, f3, -3, 0, eps);
    double root3 = root(f2, f3, -1, 1, eps);
    double I_f1 = integral(f1, root2, root1, eps);
    double I_f2 = integral(f2, root3, root1, eps);
    double I_f3 = integral(f3 ,root2, root3, eps);
    double ans = I_f1 - I_f2 - I_f3;
    printf("answer: %lf\n", ans);
}

void print_iters(int num_a, int num_b, double a, double b){
    num_of_iterations = 0;
    root(functions[num_a], functions[num_b], a, b, eps);
    printf("number of iterations: %d\n", num_of_iterations);
}

void test_roots(int num_a, int num_b, double a, double b){
    double cur_root = root(functions[num_a], functions[num_b], a, b, eps);
    printf("point of f%d and f%d on [%lf, %lf] segment: %lf \n", num_a + 1, num_b + 1, a, b, cur_root);
}

void test_integrals(int num, double a, double b){
    double cur_integral = integral(functions[num], a, b, eps);
    printf("integral of f%d on [%lf, %lf] segment: %lf \n", num + 1, a, b, cur_integral);
}

void print_help_info(void){
    printf("functions:\n");
    printf("f1: y = 0.35 * x * x - 0.95 * x + 2.7\n");
    printf("f2: y = 3 * x + 1\n");
    printf("f3: y = 1 / (x + 2)\n");
    printf("(test) f4: y = 2x\n");
    printf("(test) f5: y = x + 3\n");
    printf("(test) f6: y = 1 - x^2\n");
    printf("points: -roots\n");
    printf("intergals: -intergals\n");
    printf("answer: -answer\n");
    printf("help: -help\n");
    printf("iterarions: -iters <number of first func> <number of second func> <left border> <right border>\n");
    printf("borders:\n");
    printf("f1, f2: [0, 2] \n");
    printf("f1, f3: [-3, -0] \n");
    printf("f2, f3: [-1, 1] \n");
    printf("test points: -test-roots <number of first func> <number of second func> <left border> <right border>\n");
    printf("test integrals: -test-integrals <number of function> <left border> <right border>\n");
}

void print_error(void){
    printf("you have used incorrect argument.\n Please use -help to check list of commands\n ");
}

int main (int argc, char ** argv) {
    int num_of_commands = 7;
    char * commands[] = {"-roots", "-integrals", "-answer", "-help", "-iters", "-test-roots" ,"-test-integrals"};
    int  arg = 1;

    while (arg < argc){
        int cur = 0;
        for (int i = 0; i < num_of_commands; i++){
            if (strcmp(argv[arg], commands[i]) == 0){
                cur = i + 1;
            }
        }
        int f_a, f_b;
        double a, b;
        if (cur == 1){
            print_roots();
            break;
        } else if (cur == 2){
            print_integrals();
            break;
        } else if (cur == 3){
            print_answer();
            break;
        } else if (cur == 4){
            print_help_info();
            break;
        } else if (cur == 5){
            f_a = atoi(argv[arg + 1]);
            f_b = atoi(argv[arg + 2]);
            a = atof(argv[arg + 3]);
            b = atof(argv[arg + 4]);
            f_a--;
            f_b--;
            arg += 4;
            print_iters(f_a, f_b, a, b);
            break;
        } else if (cur == 6){
            f_a = atoi(argv[arg + 1]);
            f_b = atoi(argv[arg + 2]);
            a = atof(argv[arg + 3]);
            b = atof(argv[arg + 4]);
            f_a--;
            f_b--;
            arg += 4;
            test_roots(f_a, f_b, a, b);
            break;
        } else if (cur == 7){
            f_a = atoi(argv[arg + 1]);
            a = atof(argv[arg + 2]);
            b = atof(argv[arg + 3]);
            f_a--;
            arg += 3;
            test_integrals(f_a, a, b);
            break;
        } else {
        print_error();
            break;
        }
        arg++;
    }
    return 0;
}
