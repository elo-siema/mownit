#include <iostream>
#include <iomanip>
#include <cstring>
#include <limits>


template<typename T>
void findEpsilon()
{
  T reflimit = std::numeric_limits<T>::epsilon();
  std::cout << std::setprecision(16) << "Reference epsilon is: " << reflimit << std::endl;
  T epsilon = (T)0.0;
  T cur = (T)1.0;

  while ((T)1.0 + cur > (T)1.0) {
    cur /= (T)2.0;
  }

  epsilon = cur*(T)2.0;
  std::cout << std::setprecision(16) << "Calculated epsilon is: " << epsilon << std::endl;
}

int main (int argc, char* argv[])
{
  if(argc != 2) return -1;
  if(!strcmp(argv[1], "--single")) findEpsilon<float>();
  else if(!strcmp(argv[1], "--double")) findEpsilon<double>();
  else std::cout << "Invalid argument" << std::endl;
  return 0;
}

