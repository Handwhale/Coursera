#include "test_runner.h"
#include "http_request.h"
#include "stats.h"

#include <map>
#include <string_view>
using namespace std;

Stats::Stats()
{
  _method_stats = {
      {"GET", 0},
      {"PUT", 0},
      {"POST", 0},
      {"DELETE", 0},
      {"UNKNOWN", 0},
  };
  _uri_stats = {
      {"/", 0},
      {"/order", 0},
      {"/product", 0},
      {"/basket", 0},
      {"/help", 0},
      {"unknown", 0},
  };
}

void Stats::AddMethod(string_view method)
{
  if (_method_stats.find(method) != _method_stats.end())
  {
    ++_method_stats[method];
  }
  else
  {
    ++_method_stats["UNKNOWN"];
  }
}

void Stats::AddUri(string_view uri)
{
  if (_uri_stats.find(uri) != _uri_stats.end())
  {
    ++_uri_stats[uri];
  }
  else
  {
    ++_uri_stats["unknown"];
  }
}

HttpRequest ParseRequest(string_view line)
{
  vector<string_view> str_args;
  str_args.reserve(3);
  size_t pos = line.find_first_not_of(' ');
  while (true)
  {
    size_t space = line.find(' ', pos);

    if (space == line.npos)
    {
      str_args.push_back(line.substr(pos));
      break;
    }
    else
    {
      str_args.push_back(line.substr(pos, space - pos));
      pos = space + 1;
    }
  }

  return {str_args[0], str_args[1], str_args[2]};
}

Stats ServeRequests(istream &input)
{
  Stats result;
  for (string line; getline(input, line);)
  {
    const HttpRequest req = ParseRequest(line);
    result.AddUri(req.uri);
    result.AddMethod(req.method);
  }
  return result;
}

void TestBasic()
{
  const string input =
      R"(GET / HTTP/1.1
    POST /order HTTP/1.1
    POST /product HTTP/1.1
    POST /product HTTP/1.1
    POST /product HTTP/1.1
    GET /order HTTP/1.1
    PUT /product HTTP/1.1
    GET /basket HTTP/1.1
    DELETE /product HTTP/1.1
    GET / HTTP/1.1
    GET / HTTP/1.1
    GET /help HTTP/1.1
    GET /upyachka HTTP/1.1
    GET /unexpected HTTP/1.1
    HEAD / HTTP/1.1)";

  const map<string_view, int> expected_method_count = {
      {"GET", 8},
      {"PUT", 1},
      {"POST", 4},
      {"DELETE", 1},
      {"UNKNOWN", 1},
  };
  const map<string_view, int> expected_url_count = {
      {"/", 4},
      {"/order", 2},
      {"/product", 5},
      {"/basket", 1},
      {"/help", 1},
      {"unknown", 2},
  };

  istringstream is(input);
  const Stats stats = ServeRequests(is);

  ASSERT_EQUAL(stats.GetMethodStats(), expected_method_count);
  ASSERT_EQUAL(stats.GetUriStats(), expected_url_count);
}

void TestAbsentParts()
{
  // Методы GetMethodStats и GetUriStats должны возвращать словари
  // с полным набором ключей, даже если какой-то из них не встречался

  const map<string_view, int> expected_method_count = {
      {"GET", 0},
      {"PUT", 0},
      {"POST", 0},
      {"DELETE", 0},
      {"UNKNOWN", 0},
  };
  const map<string_view, int> expected_url_count = {
      {"/", 0},
      {"/order", 0},
      {"/product", 0},
      {"/basket", 0},
      {"/help", 0},
      {"unknown", 0},
  };
  const Stats default_constructed;

  ASSERT_EQUAL(default_constructed.GetMethodStats(), expected_method_count);
  ASSERT_EQUAL(default_constructed.GetUriStats(), expected_url_count);
}

int main()
{
  TestRunner tr;
  RUN_TEST(tr, TestBasic);
  RUN_TEST(tr, TestAbsentParts);
}
