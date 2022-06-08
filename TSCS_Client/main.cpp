#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <boost/circular_buffer.hpp>
#include <ctime>

using boost::asio::ip::tcp;
std::array<char, 5> C_buf;
int C_buf_itertor = 0;

std::string make_daytime_string()
{
  using namespace std; // For time_t, time and ctime;
  time_t now = time(0);
  return ctime(&now);
}

void Calc_average_5ms (  std::array<char, 5> &n)
{
  int average{0};
  int sum {0};
  for (int i = 0; i<5; i++)
  {
    sum+= n[i]; 
  }
  average = sum/5;
  std::cout<<"**********************"<<endl;
  std::cout<<"Average temp past 5 seconds= "<<average<<std::endl;
  std::cout<<"**********************"<<endl; 

}

void print_1ms(const boost::system::error_code& /*e*/,
    boost::asio::steady_timer* t, int* count)
{
    boost::asio::io_context io_Context;
    tcp::resolver resolver(io_Context);
    tcp::resolver::results_type endpoints = resolver.resolve("192.168.56.1","1337");
    tcp::socket socket(io_Context);
    boost::asio::connect(socket, endpoints);
    for (;;)
    {
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
        /*C_buffer[C_buf_itertor] = *buf.data;*/
       // std::cout<<"buffer = ";
       // std::cout<<C_buffer[C_buf_itertor];
       
     
      
        C_buf[C_buf_itertor] = *buf.data();
        C_buf_itertor++;
        if (C_buf_itertor >4)
        {
          C_buf_itertor = 0;
          Calc_average_5ms(C_buf);
        }
        std::cout<<"recieved temprature at:"<<make_daytime_string()<<"=";
        std::cout.write(buf.data(), len);
   
    }

    if (*count < 25)
    {
      ++(*count);

      t->expires_at(t->expiry() + boost::asio::chrono::seconds(1));
      t->async_wait(boost::bind(print_1ms,
            boost::asio::placeholders::error, t, count));
    }
}

int main(int argc, char* argv[])
{
  boost::asio::io_context io;

  int count = 0;
  boost::asio::steady_timer t(io, boost::asio::chrono::seconds(1));
  t.async_wait(boost::bind(print_1ms,
        boost::asio::placeholders::error, &t, &count));

  io.run();

  std::cout << "Final count is " << count << std::endl;

  return 0;
  
}

