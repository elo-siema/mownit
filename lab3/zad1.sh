#usage: ./zad1.sh 5
#where 5 is the order of the polynomial - change at will
mkdir -p output
mkdir -p images
sed 's/ORDER 8/ORDER '$1'/g' approx.c | gcc -xc -o approx - -L/usr/local/include/gsl/lib -lgsl -lgslcblas -lm 
./approx
sed 's/{{ORDER}}/'$1'/g' gp_zad1 | gnuplot