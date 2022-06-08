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

//Moving filter algorithm is used
int  Calc_average_overtime(int new_temp)
{
    static  int average {PRESET_TEMP};
    /* every new average is the (last average + new reading)/2 */
    int new_average = (average + new_temp) /2 ;
    average =  new_average;
    return average;
      /*
    if (avg_counter < 0 || avg_counter >= INT_MAX)//prevent overflow
    {
        std::cout<<"Average reset";
        avg_counter = 0;
    }
    else
    {
        sum = sum + x; 

    }
    */


}
void Calc_average_10minute(std::array<char, 600>&n)
{

}

