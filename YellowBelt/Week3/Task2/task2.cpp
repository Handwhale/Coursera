#include "Week3/Task2/phone_number.h"
#include <iostream>

using namespace std;

void TryOkNumbers()
{
    PhoneNumber phoneNumber1("+7-495-111-22-33");
    PhoneNumber phoneNumber2("+7-495-1112233");
    PhoneNumber phoneNumber3("+323-22-460002");
    PhoneNumber phoneNumber4("+1-2-coursera-cpp");

    if (phoneNumber4.GetInternationalNumber() != "+1-2-coursera-cpp")
        throw invalid_argument("test error");
}

void TryInvalidNumbers()
{
    try
    {
        PhoneNumber phoneNumber1("1-2-333");
    }
    catch (invalid_argument &ex)
    {
    }
    try
    {
        PhoneNumber phoneNumber1("+7-1233");
    }
    catch (invalid_argument &ex)
    {
    }
}

void Tests()
{
    TryOkNumbers();
    TryInvalidNumbers();
}

int main()
{
    Tests();
    return 0;
}