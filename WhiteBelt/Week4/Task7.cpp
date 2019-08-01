// Работа с сервером времени
// https://www.coursera.org/learn/c-plus-plus-white/programming/NXqA9/rabota-s-siervierom-vriemieni
#include <iostream>
#include <exception>

using namespace std;

string AskTimeServer();
// {
//   throw invalid_argument("");
//   throw system_error(error_code());
//   return "Oh HELLO THERE";
// }

class TimeServer
{
public:
  string GetCurrentTime()
  {
    try
    {
      LastFetchedTime = AskTimeServer();
      return LastFetchedTime;
    }
    catch (system_error &ex)
    {
      return LastFetchedTime;
    }
  }

private:
  string LastFetchedTime = "00:00:00";
};

int main()
{
  // TimeServer time_server;
  // cout << time_server.GetCurrentTime();
  return 0;
}
