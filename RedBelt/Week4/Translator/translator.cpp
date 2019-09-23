#include "test_runner.h"
#include <string>
#include <deque>
#include <string_view>
#include <map>
#include <algorithm>

using namespace std;

class Translator
{
public:
    void Add(string_view source, string_view target)
    {
        string_view saved_source = FromViewToString(source);
        string_view saved_target = FromViewToString(target);
        source_to_target[saved_source] = saved_target;
        target_to_source[saved_target] = saved_source;
    }
    string_view TranslateForward(string_view source) const
    {
        return Translate(source_to_target, source);
    }
    string_view TranslateBackward(string_view target) const
    {
        return Translate(target_to_source, target);
    }

private:
    map<string_view, string_view> source_to_target;
    map<string_view, string_view> target_to_source;
    deque<string> _str_data;

    string_view FromViewToString(string_view sv)
    {
        // initializer_list can simplify existence check
        auto it = source_to_target.find(sv);
        if (it != source_to_target.end())
        {
            return it->first;
        }

        it = target_to_source.find(sv);
        if (it != target_to_source.end())
        {
            return it->first;
        }

        string str;
        for (int i = 0; i < sv.size(); i++)
        {
            str.push_back(sv[i]);
        }
        _str_data.push_back(str);
        return _str_data.back();
    }

    string_view Translate(const map<string_view, string_view> &container, string_view sv) const
    {
        if (container.count(sv) == 0)
            return "";
        return container.at(sv);
    }
};

void TestSimple()
{
    Translator translator;

    translator.Add(string("okno"), string("window"));
    translator.Add(string("stol"), string("table"));

    ASSERT_EQUAL(translator.TranslateForward("okno"), "window");
    ASSERT_EQUAL(translator.TranslateBackward("table"), "stol");
    ASSERT_EQUAL(translator.TranslateBackward("stol"), "");
}

int main()
{
    TestRunner tr;
    RUN_TEST(tr, TestSimple);
    return 0;
}
