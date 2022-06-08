#include "avg_clc.hpp"

void Calc_average_5ms (  std::array<char, 5> &n)
{
  int average{0};
  int sum {0};
  for (int i = 0; i<5; i++)
  {
    sum+= n[i]; 
  }
  average = sum/5;
  std::cout<<"**********************"<<std::endl;
  std::cout<<"Average temp past 5 seconds= "<<average<<std::endl;
  std::cout<<"**********************"<<std::endl; 

}
