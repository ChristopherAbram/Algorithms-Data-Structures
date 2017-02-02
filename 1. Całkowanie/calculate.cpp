#define _USE_MATH_DEFINES 1

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "Integrals.h"

double f1(double x);
double f2(double x);
double f3(double x);
double f4(double x);
double f5(double x);

int main(int argc, char** argv){
	double a, b;

	printf( " Podaj przedzial calkowania:\n" );
	scanf( "%lf %lf", &a, &b );

	// Obliczamy ca³ki:
	printf( " Przedzial calkowania: [%.3lf, %.3lf]\n\n Wyniki:\n", a, b );
	printf( "\n Funkcja (1): f(x) = sqrt(e^x)\n" );
	printf(" -------------------------------------------------\n");
	printf(" Metoda malych prostokatow:   %20.10lf\n", int_rectangle( f1, a, b ) );
	printf(" Metoda malych trapezow:      %20.10lf\n", int_trapeze(f1, a, b));
	printf(" Metoda Monte-Carlo:          %20.10lf\n", int_mc(f1, a, b));

	printf("\n Funkcja (2): f(x) = x^2 + 2x\n");
	printf(" -------------------------------------------------\n");
	printf(" Metoda malych prostokatow:   %20.10lf\n", int_rectangle(f2, a, b));
	printf(" Metoda malych trapezow:      %20.10lf\n", int_trapeze(f2, a, b));
	printf(" Metoda Monte-Carlo:          %20.10lf\n", int_mc(f2, a, b));

	printf("\n Funkcja (3): f(x) = sqrt(x^2 + 1)/x\n");
	printf(" -------------------------------------------------\n");
	printf(" Metoda malych prostokatow:   %20.10lf\n", int_rectangle(f3, a, b));
	printf(" Metoda malych trapezow:      %20.10lf\n", int_trapeze(f3, a, b));
	printf(" Metoda Monte-Carlo:          %20.10lf\n", int_mc(f3, a, b));

	printf("\n Funkcja (4): f(x) = 1/sqrt(2x^2 - x + 5)\n");
	printf(" -------------------------------------------------\n");
	printf(" Metoda malych prostokatow:   %20.10lf\n", int_rectangle(f4, a, b));
	printf(" Metoda malych trapezow:      %20.10lf\n", int_trapeze(f4, a, b));
	printf(" Metoda Monte-Carlo:          %20.10lf\n", int_mc(f4, a, b));

	printf("\n Funkcja (5): f(x) = cosx/( sinx + 2 )\n");
	printf(" -------------------------------------------------\n");
	printf(" Metoda malych prostokatow:   %20.10lf\n", int_rectangle(f5, a, b));
	printf(" Metoda malych trapezow:      %20.10lf\n", int_trapeze(f5, a, b));
	printf(" Metoda Monte-Carlo:          %20.10lf\n", int_mc(f5, a, b));
	system( "pause" );
	return EXIT_SUCCESS;
}// end main

double f1(double x){
	return sqrt(exp(x)); // or sqrt(pow(M_E,x))
}// end f1

double f2(double x){
	return x*x + 2*x;
}// end f2

double f3(double x){
	return sqrt(x*x + 1) / x;
}// end f3

double f4(double x){
	return 1./sqrt( 2*x*x - x + 5 );
}// end f4

double f5(double x){
	return cos(x) / ( ( sin(x) + 2 ) );
}// end f5