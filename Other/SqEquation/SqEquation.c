#define _USE_MATH_DEFINES
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int SqEquation(double a, double b, double c, double *x1, double *x2);
int LinEquation(double b, double c, double *x1);
int IfEqualZero(double num);

int main()
{
	printf("#SqEquation v. 1.3.0 (c)inedostoev, 2017\n"
	       "#ax^2 + bx + c = 0\n"
	       "#If you would like to solve the linear equation, write a = 0\n"
	       "#Enter a b c :\n");
	const double infinity = tan(M_PI / 2);
    double a = infinity, b = infinity, c = infinity;
	scanf("%lg%lg%lg", &a, &b, &c);
	if(a == infinity || b == infinity || c == infinity) {
        printf("Can't read coefficients\n");
        exit(1);
    }
    double x1 = infinity, x2 = infinity;
	int nRoots = SqEquation(a, b, c, &x1, &x2);
    switch (nRoots) {
	case 2: printf("x1 = %lg\n"
		           "x2 = %lg\n",x1, x2);
		break;
	case 1: printf("x1 = %lg\n", x1);
		break;
	case 0: printf("No roots\n");
		break;
	case 3: printf("Infinitely many roots\n");
		break;
	default: printf("Something went wrong\n");
		break;
	}
	return 0;
}

int SqEquation(double a, double b, double c, double *x1, double *x2)
{
	if (IfEqualZero(a) && IfEqualZero(b) && IfEqualZero(c)) {
	    const double infinity = tan(M_PI / 2);
	    *x1 = infinity;
        *x2 = infinity;
        return 3;
    }
	if (!IfEqualZero(a) && IfEqualZero(b) && IfEqualZero(c)) {
		*x1 = 0;
        *x2 = 0;
        return 1;
	}
	if (IfEqualZero(a)) {
		int q = LinEquation(b, c, x1);
		return q;
	}
	double d = 0;
	d = b * b - 4 * a * c;
	if (d > 0) {
		*x1 = (-b - sqrt(d)) / (2 * a);
		*x2 = (-b + sqrt(d)) / (2 * a);
		return 2;
	}
	if (d < 0) {
		return 0;
	}
	if (IfEqualZero(d)) {
		*x1 = (-b) / (2 * a);
		return 1;
	}
}

int LinEquation(double b, double c, double *x1)
{
    if (!IfEqualZero(b) && IfEqualZero(c)) {
		*x1 = 0;
		return 1;
	}
    if (IfEqualZero(b) && !IfEqualZero(c)) {
        return 0;
    }
	if (!IfEqualZero(b) && !IfEqualZero(c)) {
		*x1 = (((-1)*c) / b);
		return 1;
	}
}

int IfEqualZero(double num) {
    const double epsilon = 0.0001;
    if(abs(num)< epsilon) { 
        return 1;
    }
    else {
        return 0;
    }
}
