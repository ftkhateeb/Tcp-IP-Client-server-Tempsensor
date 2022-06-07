#include <iostream>
#include "Base.hpp"
int main(void)
{
    std::cout << "Hello, I am client\n";
    std::cout <<static_cast<int>(NetworkingEnum::one)<<std::endl;
}