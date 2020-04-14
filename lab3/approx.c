//#include <config.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_spline.h>
#include <gsl/gsl_interp.h>
#include <gsl/gsl_chebyshev.h>

#define ORDER 8 //if changed here, will break zad1.sh
#define STR(x) #x
#define NAME( n, order ) "output/fun" STR(n) "ord" STR( order ) ".txt"

static double fun1(double x, void* params)
{
  return exp(pow(x, 2));
}

static double fun2(double x, void* params)
{
  return fabs(x+pow(x,3));
}

static double fun3(double x, void* params)
{
  return (x > 0) - (x < 0);
}

int main (void)
{
  const double a = -1.0;
  const double b = 1.0;
  double xi, yi, ayi, aerr, absoluteErrorSum;
  int passes;
  gsl_function F[3];
  double meanAbsoluteErrors[3];
  F[0].function = fun1;
  F[1].function = fun2;
  F[2].function = fun3;

  FILE *output[3];
  output[0] = fopen(NAME( 1, ORDER ), "w");
  output[1] = fopen(NAME( 2, ORDER ), "w");
  output[2] = fopen(NAME( 3, ORDER ), "w");

  for(int fi = 0; fi < 3; fi++)
  {
    passes = 0;
    absoluteErrorSum = 0.0;
    gsl_cheb_series* cs = gsl_cheb_alloc(ORDER);
    gsl_cheb_init(cs, &F[fi], a, b);
    
    for (xi = a; xi <= b; xi += 0.01) {
        yi = F[fi].function(xi, NULL);
        gsl_cheb_eval_err(cs, xi, &ayi, &aerr);
        fprintf (output[fi],"%g %g %g %g\n", xi, yi, ayi, aerr);
        passes++;
        absoluteErrorSum += fabs(yi - ayi);
	  }
    meanAbsoluteErrors[fi] = absoluteErrorSum / (double)passes;
  }
  printf("%d %g %g %g\n", 
    ORDER, 
    meanAbsoluteErrors[0], 
    meanAbsoluteErrors[1], 
    meanAbsoluteErrors[2]
    );
  return 0;
}

