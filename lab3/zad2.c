#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_spline.h>
#include <gsl/gsl_interp.h>
#include <gsl/gsl_chebyshev.h>
#include <gsl/gsl_fit.h>

static double fun1(double x, void* params)
{
  return pow(0.5, pow(x,2.0) + 2.0*x);
}

void compareFit()
{
    FILE *output = fopen("output2/comparison.txt", "w");
  //setup linear fit
    const int stepsCount = 1000;
    double xArray[stepsCount * 2];
    double yArray[stepsCount * 2];

    for (int i = -stepsCount; i <= stepsCount; i++)
    {
        double x = (double)i / (double)stepsCount;
        double y = fun1(x, NULL);

        xArray[i + stepsCount] = x;
        yArray[i + stepsCount] = y;
    }

    double c0 = 0;
    double c1 = 0;
    double cov00 = 0;
    double cov01 = 0;
    double cov11 = 0;
    double sumsq = 0;
    gsl_fit_linear(
      xArray, 
      1, 
      yArray, 
      1, 
      stepsCount * 2, 
      &c0, 
      &c1, 
      &cov00, 
      &cov01, 
      &cov11, 
      &sumsq
      );

    //setup Chebyshev approx
    const double a = -1.0;
    const double b = 1.0;
    gsl_function F;
    F.function = fun1;
    
    gsl_cheb_series* cs5 = gsl_cheb_alloc(5);
    gsl_cheb_series* cs50 = gsl_cheb_alloc(50);
    
    gsl_cheb_init(cs5, &F, a, b);
    gsl_cheb_init(cs50, &F, a, b);
    //end setup

    //error calculating setup
    int passes = 0;
    double absoluteErrorSumLin = 0.0;
    double absoluteErrorSumCheb5 = 0.0;
    double absoluteErrorSumCheb50 = 0.0;
    double meanAbsoluteErrorLin = 0.0;
    double meanAbsoluteErrorCheb5 = 0.0;
    double meanAbsoluteErrorCheb50 = 0.0;
    //end setup

    for (int i = -stepsCount; i <= stepsCount; i++)
    {
        double x = (double)i / (double)stepsCount;
        double y = fun1(x, NULL);
        double linY = c0 + c1 * x;
        double chebY5 = gsl_cheb_eval(cs5, x);
        double chebY50 = gsl_cheb_eval(cs50, x);        
        
        passes++;
        absoluteErrorSumLin += fabs(y - linY);
        absoluteErrorSumCheb5 += fabs(y - chebY5);
        absoluteErrorSumCheb50 += fabs(y - chebY50);

        fprintf (output,"%g %g %g %g %g\n", x, y, linY, chebY5, chebY50);
    }
    
    meanAbsoluteErrorLin    = absoluteErrorSumLin    / (double)passes;
    meanAbsoluteErrorCheb5  = absoluteErrorSumCheb5  / (double)passes;
    meanAbsoluteErrorCheb50 = absoluteErrorSumCheb50 / (double)passes; 

    printf ("meanAbsErrLin, meanAbsErrCheb5, meanAbsErrCheb50\n");
    printf (
      "%g %g %g\n",
      meanAbsoluteErrorLin, 
      meanAbsoluteErrorCheb5, 
      meanAbsoluteErrorCheb50
    );

    gsl_cheb_free(cs5);
    gsl_cheb_free(cs50);
}

int main (void)
{
  compareFit();
  return 0;
}

