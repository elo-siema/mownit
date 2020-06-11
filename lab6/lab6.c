#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_spline.h>
#include <gsl/gsl_interp.h>
#include <gsl/gsl_chebyshev.h>
#include <gsl/gsl_fit.h>
#include <gsl/gsl_integration.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_blas.h>

double* generate_matrix(int n) {
  double* matrix = (double*)malloc(n*n*sizeof(double));

  srand(2137);
  for(int i = 0; i < n; i++) {    
    for(int j = 0; j < n; j++) {
      //printf("x: %d, y: %d\n", i,j);
      matrix[i*n+j] = ((double)rand())/RAND_MAX;
    }
  }

  return matrix;
}

double* generate_vector(int n) {
  double* vector = malloc(n*sizeof(double));
  for(int i = 0; i < n; i++) {
    vector[i] = i+1;
  }

  return vector;
}

double* copyVector(double* src, int size)
{
    double* vec = calloc(sizeof(double), size);
    for (int i = 0; i < size; ++i){
        vec[i] = src[i];
    }
    return vec;
}

int compare_vectors(gsl_vector*a, gsl_vector*b) {
  if(a->size != b->size) return 0;

  const double eps = 0.005; 

  for(int i = 0; i < a->size; i++){
    if(fabs(gsl_vector_get(a,i)-gsl_vector_get(b,i)) > eps) {
      return 0;
    }
  }
  return 1;
}



int print_matrix(FILE *f, const gsl_matrix *m)
{
        int status, n = 0;

        for (size_t i = 0; i < m->size1; i++) {
                for (size_t j = 0; j < m->size2; j++) {
                        if ((status = fprintf(f, "%g, ", gsl_matrix_get(m, i, j))) < 0)
                                return -1;
                        n += status;
                }

                if ((status = fprintf(f, "\n")) < 0)
                        return -1;
                n += status;
        }

        return n;
}

int print_vector(const gsl_vector *v){
  for(int i = 0; i < v->size; i++){
    printf("%g, ", gsl_vector_get(v, i));
  }
  printf("\n");
}

int verify_correctness(int n, gsl_matrix *m, gsl_vector*b, gsl_vector *x) {
  
  gsl_vector *y = gsl_vector_alloc(n); 
  int err = gsl_blas_dgemv( CblasNoTrans, 1.0, m, x, 1.0, y );

  return compare_vectors(y, b);
}

double decomp(gsl_matrix *A, gsl_permutation* p, int *signum)
{
    clock_t start = clock();
    gsl_linalg_LU_decomp(A, p, signum);
    clock_t end = clock();

    double t = ((double) (end - start)) / CLOCKS_PER_SEC;
    return t;
}

double solve(const gsl_matrix* LU, const gsl_permutation* p, const gsl_vector* b, gsl_vector* x)
{
    clock_t start = clock();
    gsl_linalg_LU_solve(LU, p, b, x);
    clock_t end = clock();

    double t = ((double) (end - start)) / CLOCKS_PER_SEC;
    return t;
}

int calculate(int n){
  double* a_data = generate_matrix(n);
  double* a_copy = copyVector(a_data, n*n);

  double* b_data = generate_vector(n);

  gsl_matrix_view m
    = gsl_matrix_view_array (a_data, n, n);
  gsl_matrix_view m_copy
    = gsl_matrix_view_array (a_copy, n, n);

  gsl_vector_view b
    = gsl_vector_view_array (b_data, n);

  gsl_vector *x = gsl_vector_alloc (n);

  int s;

  gsl_permutation * p = gsl_permutation_alloc (n);

  double decomptime = decomp (&m.matrix, p, &s);

  double solvetime = solve (&m.matrix, p, &b.vector, x);

  printf("Size: %d, DTime: %.17f, STime: %.17f, Correct: %d\n",
    n,
    decomptime, 
    solvetime, 
    verify_correctness(n, &(m_copy.matrix), &(b.vector), x)
  );
  gsl_permutation_free (p);
  gsl_vector_free (x);
}


int main(int argc, char const *argv[])
{
  if(argc != 2) return -1;
  int n = atoi(argv[1]);

  calculate(n);

  return 0;
}
