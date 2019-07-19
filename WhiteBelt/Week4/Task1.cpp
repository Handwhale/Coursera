// Структура LectureTitle
// https://www.coursera.org/learn/c-plus-plus-white/programming/PnvtW/struktura-lecturetitle
#include <string>

using namespace std;

struct Specialization
{
    string value;

    explicit Specialization(string input)
    {
        value = input;
    }
};

struct Course
{
    string value;

    explicit Course(string input)
    {
        value = input;
    }
};

struct Week
{
    string value;

    explicit Week(string input)
    {
        value = input;
    }
};

struct LectureTitle
{
    string specialization;
    string course;
    string week;

    LectureTitle(Specialization specialization_input, Course course_input, Week week_input)
    {
        specialization = specialization_input.value;
        course = course_input.value;
        week = week_input.value;
    }
};

int main()
{
    LectureTitle title(
        Specialization("C++"),
        Course("White belt"),
        Week("4th"));
    return 0;
}