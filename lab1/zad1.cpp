#include <iostream>
#include <cstring>

static const int MAX_N = 40;

template<typename T>
void printSeries()
{
  T n = 0, xn = 0.01, xnplus1;
  for(n; n<MAX_N; n++){
    xnplus1 = xn + (T)3.0 * xn * ((T)1.0 - xn);
    std::cout << n << ", " << xnplus1 << std::endl;
    xn=xnplus1;
  }
}

int main (int argc, char* argv[])
{
  if(argc != 2) return -1;
  if(!strcmp(argv[1], "--single")) printSeries<float>();
  else if(!strcmp(argv[1], "--double")) printSeries<double>();
  else std::cout << "Invalid argument" << std::endl;
  return 0;
}

