#include <iostream>
#include "Base.hpp"
int main(void)
{
    std::cout << "Hello, I am Server\n";
    std::cout <<static_cast<int>(NetworkingEnum::two)<<std::endl;

    boost::asio::io_context io;

    int count = 0;
    boost::asio::steady_timer t(io, boost::asio::chrono::seconds(1));
    t.async_wait(boost::bind(print,
            boost::asio::placeholders::error, &t, &count));

    io.run();

    std::cout << "Final count is " << count << std::endl;

    return 0;
}