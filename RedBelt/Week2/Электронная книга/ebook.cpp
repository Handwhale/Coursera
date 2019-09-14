#include <iomanip>
#include <iostream>
#include <vector>
#include <map>
#include <utility>

using namespace std;


struct Page
{
  double rating;
  int users_count;
};

class ReadingManager
{
public:
  ReadingManager() : pages(MAX_PAGE_COUNT_), total_users_count(0) {}

  void Read(int user_id, int page_count)
  {
    if (user_to_page.count(user_id) == 0)
    {
      total_users_count++;
      user_to_page[user_id] = page_count;
      pages[page_count - 1].users_count++;
    }
    else
    {
      int old_page_count = user_to_page[user_id];
      user_to_page[user_id] = page_count;

      pages[old_page_count - 1].users_count--;
      pages[page_count - 1].users_count++;
    }

    RecalculatePageRating();
  }

  double Cheer(int user_id) const
  {
    if (user_to_page.count(user_id) == 0)
      return 0;

    if(total_users_count == 1)
      return 1;

    return pages[user_to_page.at(user_id) - 1].rating;
  }

private:
  map<int, int> user_to_page;
  vector<Page> pages;
  int total_users_count;
  static const int MAX_USER_COUNT_ = 100'000;
  static const int MAX_PAGE_COUNT_ = 1000;

  void RecalculatePageRating()
  {
    if(total_users_count < 2)
      return;
    int current_users_count = 0;
    for (auto &item : pages)
    {
      item.rating = current_users_count * 1.0 / (total_users_count - 1);
      current_users_count += item.users_count;
    }
  }
};


int main() {
  // Для ускорения чтения данных отключается синхронизация
  // cin и cout с stdio,
  // а также выполняется отвязка cin от cout
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  ReadingManager manager;

  int query_count;
  cin >> query_count;

  for (int query_id = 0; query_id < query_count; ++query_id) {
    string query_type;
    cin >> query_type;
    int user_id;
    cin >> user_id;

    if (query_type == "READ") {
      int page_count;
      cin >> page_count;
      manager.Read(user_id, page_count);
    } else if (query_type == "CHEER") {
      cout << setprecision(6) << manager.Cheer(user_id) << "\n";
    }
  }

  return 0;
}