# MOwNiT Lab2 - sprawozdanie
## Autor: Michał Flak 

## Zadania - GSL
### Zadanie 1
_Proszę skompilować i uruchomić program interpolacja.c. Korzystając z programu gnuplot narysować wykres._

Pobrano i skompilowano program `interpolacja.c` używając załączonego makefile. Przygotowano wykres poleceniami gnuplot:

```
set output "zad1.png"
set terminal png
plot "inter_polynomial.txt" title 'polynomial' with lines, \
     "wartosci.txt" title 'wartosci'
```

Uzyskany plik `zad1.png`:
![zad1]

### Zadanie 2
_Narysować na jednym wykresie krzywe otrzymane różnymi metodami interpolacji (w przykładzie ustawione jest gsl_interp_polynomial)._

Zmodyfikowano 'interpolacja.c' zmieniając w linii 39 metodę interpolacji na `gsl_interp_steffen`, `gsl_interp_cspline` i `gsl_interp_polynomial`, zapisano wyniki w plikach `inter_steffen.txt`, `inter_cspline.txt`, i `inter_polynomial.txt`. Przygotowano wykres poleceniami gnuplot:

```
set output "zad2.png"
set terminal png
plot "inter_cspline.txt" title 'cspline' with lines, \
     "inter_polynomial.txt" title 'polynomial' with lines, \
     "inter_steffen.txt" title 'steffen' with lines, \
     "wartosci.txt" title 'wartosci'
```

Uzyskany plik `zad2.png`:
![zad2]
## Zadania - Gnuplot
### Zadanie 3
_Przy pomocy gnuplot prosze narysowac dane zgromadzone w pliku dane1.dat. Aby wykres byl czytelny, jedna z osi musi miec skale logarytmiczna. Prosze ustalic, ktora to os i narysowac wykres._

Oś o skali logarytmicznej to X. Przygotowano wykres poleceniami gnuplot:

```
set output "zad3.png"
set terminal png
set logscale x 
plot "dane1.dat" with lines
```

Uzyskany plik `zad3.png`:
![zad3]
### Zadanie 4
_Prosze narysowac wykres funkcji dwywymiarowej, ktorej punkty znajduja sie w pliku dane2.dat. Prosze przegladnac plik i sprobowac znalezc w nim maksimum. Potem prosze zlokalizowac maksimum wizualnie na wykresie. Prosze na wykresie zaznaczyc maksimum strzałką_

Pobrano i zapisano plik dane2.dat. Odnaleziono maksimum poleceniem `sort -k3 dane2.dat -g` - jest to punkt (4,3,1). Przygotowano wykres poleceniami gnuplot:

```
set output "zad4.png"
set terminal png
set arrow from 4,3,1.2 to 4, 3, 1
show arrow
splot "dane2.dat" with lines
```

Uzyskany plik `zad4.png`:
![zad4]
### Zadanie 5
_Prosze odtworzyc wykres znajdujacy sie na rysunku_

Przygotowano plik `fun1.txt` z wartościami odczytanymi wizualnie z `testowy.png`. Przygotowano wykres poleceniami gnuplot:

```
set output "zad5.png"
set terminal png font "Script, 8"
set grid
set xrange [-3:3]
set key left top box 3 Left
set bmargin 4.1

set title "Wykres testowy" 
set ylabel "Amplituda" 
set label at -3.4,-5 "-0.365088, 4.84084" 

set style line 1 lt rgb "red" lw 2 pt 1
set style line 2 lt rgb "green" lw 2 pt 1
set style line 3 lt rgb "blue" lw 1 pt 1

plot "fun1.txt" title 'Dane z pliku fun1.txt' with errorbars ls 1, \
     sin(x**5) title 'funkcja2: sinus(x^5)' with lines ls 2, \
     2*cos(x*sin(x)) title 'funkcja1: 2*cos(x*sin(x))' with boxes ls 3, \
     3*sin(x) title 'funkcja3: 3*sin(x)' with lines ls 1
```

Uzyskany plik `zad5.png`:
![zad5]
Oczekiwany plik `testowy.png`:
![testowy]

[zad1]: zad1.png
[zad2]: zad2.png
[zad3]: zad3.png
[zad4]: zad4.png
[zad5]: zad5.png
[testowy]: testowy.png