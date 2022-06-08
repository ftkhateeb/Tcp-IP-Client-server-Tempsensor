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
int Calc_average_overtime(int new_temp);
int Calc_accumulation_overtime(int new_temp);
