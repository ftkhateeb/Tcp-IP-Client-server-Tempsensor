#include <iostream>
#include <string>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <boost/circular_buffer.hpp>
#include <ctime>
#include "avg_clc.hpp"
#include "time_clc.hpp"


using boost::asio::ip::tcp;
int Scheduler = 0; //Scheduler variable to manage when to log AVG and ACC
std::string var;//temporary variable that will be converted to int
int int_var = 0;
static int AVG = 0;//variable to hold the AVG over time
static int ACC = 0;//variable to hold the AVG over time

/*Function that gets called every one sec using ASIO_Asyncwait*/
void print_1s(const boost::system::error_code& /*e*/,
    boost::asio::steady_timer* t, int* count)
{
    Scheduler ++;
    //ASIO's Io_context : abstraction for all IO finctionalities
    boost::asio::io_context 
    io_Context;
    tcp::resolver resolver(io_Context);
    //create endpoints to communicate with
    tcp::resolver::results_type endpoints = resolver.resolve("192.168.56.1","1337");
    //create a file discriptor (socket)
    tcp::socket socket(io_Context);
    //try to connect to server with previously mentioned address
    boost::asio::connect(socket, endpoints);
    //loop till connect
    for (;;)
    {
      //Buffer to contain the reveived message from server
        std::array<char, 128> buf;
        boost::system::error_code error;
        size_t len = socket.read_some(boost::asio::buffer(buf), error);

        if (error == boost::asio::error::eof)
        {         
           break; // Connection closed cleanly by peer.
        }

        else if (error)
        {
          throw boost::system::system_error(error); // Some other error.
        }
        std::cout<<std::endl;
        //Buf.data returns string
        var = buf.data();
        //Convert received string from Server to an Int
        int_var = std::stoi(var);
        //Every second peroform Average and ACC calculations
        ACC = Calc_accumulation_overtime(int_var);
        AVG = Calc_average_overtime(int_var);
        //Every 5 seconds perform logging of AVG and ACC
        if(Scheduler%5 == 0)
        {
          std::cout<<"Avg Overtime: "<<AVG<<std::endl;
          std::cout<<"Acc Overtime: "<<ACC<<std::endl;
        }
        std::cout<<"recieved temprature at:"<<make_daytime_string()<<"=";
        std::cout.write(buf.data(), len);
   
    }

    if (*count < 25)
    {
      ++(*count);

      t->expires_at(t->expiry() + boost::asio::chrono::seconds(1));
      t->async_wait(boost::bind(print_1s,
            boost::asio::placeholders::error, t, count));
    }
}

int main(int argc, char* argv[])
{
  boost::asio::io_context io;

  int count = 0;
  boost::asio::steady_timer t(io, boost::asio::chrono::seconds(1));
  t.async_wait(boost::bind(print_1s,
        boost::asio::placeholders::error, &t, &count));

  io.run();

  std::cout << "Final count is " << count << std::endl;

  return 0;
  
}

