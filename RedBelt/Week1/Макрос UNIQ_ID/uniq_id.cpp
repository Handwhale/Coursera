#include <string>
#include <vector>
using namespace std;

#define __PASTE_UNIQ_VAR1__(line_number)  __PASTE_UNIQ_VAR2__(line_number)
#define __PASTE_UNIQ_VAR2__(line_number)  uniq_var_id_##line_number
#define UNIQ_ID __PASTE_UNIQ_VAR1__(__LINE__)

int main()
{
    int UNIQ_ID = 0;
    string UNIQ_ID = "hello";
    vector<string> UNIQ_ID = {"hello", "world"};
    vector<int> UNIQ_ID = {1, 2, 3, 4};
}