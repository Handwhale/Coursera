#include <string>
#include <list>
#include "test_runner.h"
using namespace std;

class Editor
{
public:
    // Реализуйте конструктор по умолчанию и объявленные методы
    Editor()
    {
        _data = {};
        cursor = _data.begin();
    }
    void Left()
    {
        if (cursor != _data.begin())
        {
            --cursor;
        }
    }
    void Right()
    {
        if (cursor != _data.end())
        {
            ++cursor;
        }
    }
    void Insert(char token)
    {
        _data.insert(cursor, token);
    }
    void Cut(size_t tokens = 1)
    {
        auto end_it = cursor_next(cursor, tokens);
        _buffer = {cursor, end_it};

        _data.erase(cursor, end_it);
        cursor = end_it;
    }
    void Copy(size_t tokens = 1)
    {
        auto end_it = next(cursor, tokens);
        _buffer = {cursor, end_it};
    }
    void Paste()
    {
        _data.insert(cursor, _buffer.begin(), _buffer.end());
    }
    string GetText() const
    {
        return {_data.begin(), _data.end()};
    }

private:
    list<char> _data;
    list<char> _buffer;
    list<char>::iterator cursor;

    list<char>::iterator cursor_next(list<char>::iterator curs, size_t tokens)
    {
        while (tokens > 0)
        {
            if (curs == _data.end())
                return curs;
            ++curs;
            --tokens;
        }
        return curs;
    }
};

void TypeText(Editor &editor, const string &text)
{
    for (char c : text)
    {
        editor.Insert(c);
    }
}

void TestEditing()
{
    {
        Editor editor;

        const size_t text_len = 12;
        const size_t first_part_len = 7;
        TypeText(editor, "hello, world"); // "hello, world|"
        for (size_t i = 0; i < text_len; ++i)
        {
            editor.Left();
        }
        // "|hello, world"
        editor.Cut(first_part_len); // "|world"
        for (size_t i = 0; i < text_len - first_part_len; ++i)
        {
            editor.Right();
        }
        // world|
        TypeText(editor, ", "); // world, |
        editor.Paste();         // world, hello, |
        editor.Left();
        editor.Left();
        // world, hello|
        editor.Cut(3);

        ASSERT_EQUAL(editor.GetText(), "world, hello");
    }
    {
        Editor editor;

        TypeText(editor, "misprnit");
        editor.Left();
        editor.Left();
        editor.Left();
        editor.Cut(1);
        editor.Right();
        editor.Paste();

        ASSERT_EQUAL(editor.GetText(), "misprint");
    }
}

void TestReverse()
{
    Editor editor;

    const string text = "esreveR";
    for (char c : text)
    {
        editor.Insert(c);
        editor.Left();
    }

    ASSERT_EQUAL(editor.GetText(), "Reverse");
}

void TestNoText()
{
    Editor editor;
    ASSERT_EQUAL(editor.GetText(), "");

    editor.Left();
    editor.Left();
    editor.Right();
    editor.Right();
    editor.Copy(0);
    editor.Cut(0);
    editor.Paste();

    ASSERT_EQUAL(editor.GetText(), "");
}

void TestEmptyBuffer()
{
    Editor editor;

    editor.Paste();
    TypeText(editor, "example");
    editor.Left();
    editor.Left();
    editor.Paste();
    editor.Right();
    editor.Paste();
    editor.Copy(0);
    editor.Paste();
    editor.Left();
    editor.Cut(0);
    editor.Paste();

    ASSERT_EQUAL(editor.GetText(), "example");
}

int main()
{
    TestRunner tr;
    RUN_TEST(tr, TestEditing);
    RUN_TEST(tr, TestReverse);
    RUN_TEST(tr, TestNoText);
    RUN_TEST(tr, TestEmptyBuffer);
    return 0;
}