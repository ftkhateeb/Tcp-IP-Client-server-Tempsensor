#include <iostream>
#include "Base.hpp"
int main(void)
{
    std::cout << "Hello, I am Server\n";
    std::cout <<static_cast<int>(NetworkingEnum::two)<<std::endl;
}