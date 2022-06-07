#pragma once
#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
enum class NetworkingEnum
{
    one, 
    two,
    three
};
void print(const boost::system::error_code& /*e*/,
    boost::asio::steady_timer* t, int* count);