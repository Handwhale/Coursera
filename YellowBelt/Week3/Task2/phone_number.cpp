#include "phone_number.h"
#include <iostream>
#include <algorithm>

string GetRange(const string &str, char splitter) {
    auto find_result = str.find(splitter);
    if (find_result == -1)
        throw invalid_argument("Out of format");
    return str.substr(0, find_result);
}

/* Принимает строку в формате +XXX-YYY-ZZZZZZ
       Часть от '+' до первого '-' - это код страны.
       Часть между первым и вторым символами '-' - код города
       Всё, что идёт после второго символа '-' - местный номер.
       Код страны, код города и местный номер не должны быть пустыми.
       Если строка не соответствует этому формату, нужно выбросить исключение invalid_argument. Проверять, что номер содержит только цифры, не нужно.*/
PhoneNumber::PhoneNumber(const string &international_number) {
    string str = international_number;
    if (str[0] != '+')
        throw invalid_argument("Out of format");

    // Country code
    str = str.substr(1, str.size() - 1);
    country_code_ = GetRange(str, '-');

    // City code
    str = str.substr(country_code_.size() + 1, str.size() - 1);
    city_code_ = GetRange(str, '-');

    // Local code
    str = str.substr(country_code_.size() + 1, str.size() - 1);
    if (str.empty())
        throw invalid_argument("Out of format");
    local_number_ = str;
}

string PhoneNumber::GetCountryCode() const {
    return country_code_;
}

string PhoneNumber::GetCityCode() const {
    return city_code_;
}

string PhoneNumber::GetLocalNumber() const {
    return local_number_;
}

string PhoneNumber::GetInternationalNumber() const {
    return '+' + GetCountryCode() + '-' + GetCityCode() + '-' + GetLocalNumber();
}




