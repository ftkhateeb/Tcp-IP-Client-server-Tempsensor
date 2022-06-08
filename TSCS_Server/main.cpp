#include <ctime>
#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <random>
#include <string>
#define TEMP_MAX 100
#define TEMP_MIN 5
using boost::asio::ip::tcp;

std::string make_daytime_string()
{
  using namespace std; // For time_t, time and ctime;
  time_t now = time(0);
  return ctime(&now);
}
std::string TempSensor_Output (void)
{
  return std::to_string (((double) rand() / (RAND_MAX+1)) * (TEMP_MAX-TEMP_MIN+1) + TEMP_MIN); 
}
int main()
{
  try
  {
    boost::asio::io_context io_context;

    tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 1337));

    for (;;)
    {
      std::cout<<"Accepting connections on PORT 1337\n";
      tcp::socket socket(io_context);
      acceptor.accept(socket);
      std::cout<<"Connetion accepted\n";
      //std::string message_time = make_daytime_string();
      std::string message_temp = TempSensor_Output();
      boost::system::error_code ignored_error;
      //boost::asio::write(socket, boost::asio::buffer(message_time), ignored_error);
      boost::asio::write(socket, boost::asio::buffer(message_temp), ignored_error);

    }
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}