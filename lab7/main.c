#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_monte.h>
#include <gsl/gsl_monte_plain.h>
#include <gsl/gsl_monte_miser.h>
#include <gsl/gsl_monte_vegas.h>

const double MIN = 0.0;
const double MAX = 1.0;

double drand(double lo, double hi) {
    return ((double)rand() * (hi-lo))/(double)RAND_MAX+lo;
}

typedef struct {
    double val;
    double err;
} IntegrationResult;

typedef enum {
    PLAIN,
    MISER,
    VEGAS
} GslIntegrationType;

double fun1 (double x){
    return x*x;
}

double fun2 (double x) {
    return 1.0/sqrt(x);
}

double fun1wrapped (
    double x[], 
    size_t dim, 
    void * p
    ) 
{
   return  fun1(x[0]);
}

double fun2wrapped (
    double x[], 
    size_t dim, 
    void * p
    ) 
{
   return  fun2(x[0]);
}

IntegrationResult integrateHitAndMiss(
    long sampleCount, 
    double maxY, 
    double (*fun)(double x), 
    double expected
    ) 
{
    IntegrationResult result;

    

    int correctSamples = 0;
    for (long i = 0; i < sampleCount; ++i){
        double x = drand(MIN, MAX);
        double y = drand(0, maxY);

        if (y <= fun(x)){
            correctSamples++;
        }
    }

    result.val = ((double)correctSamples / (double) sampleCount)*maxY;
    result.err = fabs(result.val - expected)/result.val;
    return result;
}


IntegrationResult integrateGSL(
    long sampleCount, 
    double (*fun)(double x[], size_t dim, void * p), 
    double expected,
    GslIntegrationType type
    ) 
{
    
    IntegrationResult result;

    double res = 0.0;
    double err = 0.0;
    double xl[1] = {MIN};
    double xu[1] = {MAX};

    const gsl_rng_type *T;
    gsl_rng *r;

    const size_t dim = 1;

    gsl_monte_function G;
    G.dim = dim;
    G.f = fun;
    G.params = 0;

    gsl_rng_env_setup();

    T = gsl_rng_default;
    r = gsl_rng_alloc(T);

    switch(type){
        case PLAIN:
        {
            gsl_monte_plain_state *sp = gsl_monte_plain_alloc(dim);

            gsl_monte_plain_integrate(&G, xl, xu, dim, sampleCount, r, sp, &res, &err);
            gsl_monte_plain_free(sp);
            break;
        }
        case MISER:
        {
            gsl_monte_miser_state* sm = gsl_monte_miser_alloc(dim);

            gsl_monte_miser_integrate(&G, xl, xu, dim, sampleCount, r, sm, &res, &err);
            gsl_monte_miser_free(sm);
            break;
        }
        case VEGAS:
        {
            gsl_monte_vegas_state* sv = gsl_monte_vegas_alloc(dim);

            gsl_monte_vegas_integrate(&G, xl, xu, dim, sampleCount, r, sv, &res, &err);
            gsl_monte_vegas_free(sv);
            break;    
        }
    }
    gsl_rng_free(r);

    result.val = res;
    result.err = fabs(result.val - expected)/res;
    return result;
}

int main(int argc, char** argv)
{
    if(argc != 2) return -1;
    srand(2139);

    int fchoice = atoi(argv[1]);
    IntegrationResult ihm, ip, im, iv;
    double expected;
    printf("n, hm, ehm, p, ep, m, em, v, ev\n");

    for(long sampleCount = 10; sampleCount<10000000; sampleCount*=2){
        switch (fchoice) {
            case 1:
            {
                expected = 1.0/3.0;
                ihm = integrateHitAndMiss(sampleCount, 1, fun1, expected);
                ip = integrateGSL(sampleCount, fun1wrapped, expected, PLAIN);
                im = integrateGSL(sampleCount, fun1wrapped, expected, MISER);
                iv = integrateGSL(sampleCount, fun1wrapped, expected, VEGAS);
                break;
            }
            case 2:
            {
                expected = 2;
                ihm = integrateHitAndMiss(sampleCount, 1000, fun2, expected);
                ip = integrateGSL(sampleCount, fun2wrapped, expected, PLAIN);
                im = integrateGSL(sampleCount, fun2wrapped, expected, MISER);
                iv = integrateGSL(sampleCount, fun2wrapped, expected, VEGAS);
                break;
            }
        }
        printf("%ld, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf\n", 
            sampleCount,
            ihm.val, ihm.err,
            ip.val, ip.err,
            im.val, im.err,
            iv.val, iv.err
            );
    }
    return 0;
}