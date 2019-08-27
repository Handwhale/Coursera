// Отправка уведомлений
// https://www.coursera.org/learn/c-plus-plus-yellow/programming/I3Sle/otpravka-uviedomlienii
#include <iostream>
#include <string>

using namespace std;

void SendSms(const string &number, const string &message)
{
    cout << "Send '" << message << "' to number " << number << endl;
}

void SendEmail(const string &email, const string &message)
{
    cout << "Send '" << message << "' to e-mail " << email << endl;
}

class INotifier
{
public:
    virtual void Notify(const string &message) = 0;

protected:
    string contact_data;
};

class SmsNotifier : public INotifier
{
public:
    SmsNotifier(string phone_number) { contact_data = phone_number; }
    void Notify(const string &message) override
    {
        SendSms(contact_data, message);
    }
};

class EmailNotifier : public INotifier
{
public:
    EmailNotifier(string email)
    {
        contact_data = email;
    }

    void Notify(const string &message) override
    {
        SendEmail(contact_data, message);
    }
};

void Notify(INotifier &notifier, const string &message)
{
    notifier.Notify(message);
}

int main()
{
    SmsNotifier sms{"+7-495-777-77-77"};
    EmailNotifier email{"na-derevnyu@dedushke.ru"};

    Notify(sms, "I have White belt in C++");
    Notify(email, "And want a Yellow one");
    return 0;
}