#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_spline.h>
#include <gsl/gsl_interp.h>
#include <gsl/gsl_chebyshev.h>
#include <gsl/gsl_fit.h>
#include <gsl/gsl_integration.h>

double f1(double x, void* params)
{
    return x*x;
}

double f2(double x, void* params)
{
    return 1 / sqrt(x);
}

double integrateRect(float a, float b, long long int n, double (*fun)(double, void*))
{
  double y;
  double sum = 0;
  double increment = (b - a) / (double)n;
  for (double i = a + increment/2.0; i < b; i += increment)
  {
    y = fun(i, NULL);
    sum += y * (b-a) / (double)n;
  }
  return sum;
}

double integrateGSL(float a, float b, double acc, int nmax, double (*fun)(double, void*), int* n)
{
  gsl_function F;
  F.function = fun;

  gsl_integration_workspace * ws = gsl_integration_workspace_alloc(nmax);
  double result;
  double abserr;

  int res = gsl_integration_qag(
    &F, 
    a, 
    b, 
    0, 
    acc, 
    nmax, 
    GSL_INTEG_GAUSS15, 
    ws, 
    &result, 
    &abserr
    );

  *n = ws->size;
  gsl_integration_workspace_free(ws); 
  return result;
}

int main(int argc, char const *argv[])
{
  const double a = 0;
  const double b = 1;
  int n;
  double desired;
  double (*fun)(double, void*) = f1;
  int resultingN;

  //select function by parameter:
  //-f1: y = x*x
  //-f2: y = 1 / sqrt(x)
  //if(argc != 2) return -1;
  if(!strcmp(argv[1], "-f1")) 
  {
    fun = f1;
    desired = 1.0/3.0;
  }
  else if(!strcmp(argv[1], "-f2")) 
  {
    fun = f2;
    desired = 2.0;
  } 

  //select desired iterations
  scanf("%d", &n);

  double resultRect = integrateRect(a, b, n, fun);

  double errRel = fabs((desired - resultRect) / desired);

  double resultGSL = integrateGSL(a, b, errRel, 1000, fun, &resultingN);

  //printf("ResultRect, ResultGsl, ResultingN, ErrRel\n");
  printf(
    "%d %lg %lg %d %lg, %d, %d, %d, %d\n", 
    n,
    resultRect, 
    resultGSL, 
    resultingN, 
    errRel, 
    errRel <= 1e-3, 
    errRel <= 1e-4, 
    errRel <= 1e-5, 
    errRel <= 1e-6
    );
  /* code */
  return 0;
}
