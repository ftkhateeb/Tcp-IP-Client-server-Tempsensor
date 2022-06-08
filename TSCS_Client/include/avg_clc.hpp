#pragma once 
#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <boost/circular_buffer.hpp>


#define PRESET_TEMP 40


void Calc_average_5ms (std::array<char, 5> &n);
void print_1ms(const boost::system::error_code& /*e*/,
    boost::asio::steady_timer* t, int* count);
void Calc_average_10minute(std::array<char, 600>&n);
