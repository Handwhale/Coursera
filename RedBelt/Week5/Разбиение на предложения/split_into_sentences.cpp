#include "test_runner.h"
#include "profile.h"
// Почему первый способ быстрее?
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

// Объявляем Sentence<Token> для произвольного типа Token
// синонимом vector<Token>.
// Благодаря этому в качестве возвращаемого значения
// функции можно указать не малопонятный вектор векторов,
// а вектор предложений — vector<Sentence<Token>>.
template <typename Token>
using Sentence = vector<Token>;

// Класс Token имеет метод bool IsEndSentencePunctuation() const
template <typename Token>
vector<Sentence<Token>> SplitIntoSentences(vector<Token> tokens)
{
    vector<Sentence<Token>> result;

    auto sentence_start_it = tokens.begin();
    auto if_end_token_lambda = [](const Token &token) {
        return token.IsEndSentencePunctuation();
    };
    while (sentence_start_it != tokens.end())
    {
        // End sentence tokens begin    (for !!!! in the end)
        auto sentence_end_it_begin = find_if(sentence_start_it, tokens.end(),
                                             if_end_token_lambda);

        auto sentence_end_it = find_if_not(sentence_end_it_begin, tokens.end(),
                                           if_end_token_lambda);

        result.emplace_back(make_move_iterator(sentence_start_it), make_move_iterator(sentence_end_it));

        sentence_start_it = sentence_end_it;
    }
    return result;
}

struct TestToken
{
    string data;
    bool is_end_sentence_punctuation = false;

    bool IsEndSentencePunctuation() const
    {
        return is_end_sentence_punctuation;
    }
    bool operator==(const TestToken &other) const
    {
        return data == other.data && is_end_sentence_punctuation == other.is_end_sentence_punctuation;
    }
};

ostream &operator<<(ostream &stream, const TestToken &token)
{
    return stream << token.data;
}

// Тест содержит копирования объектов класса TestToken.
// Для проверки отсутствия копирований в функции SplitIntoSentences
// необходимо написать отдельный тест.
void TestSplitting()
{
    ASSERT_EQUAL(
        SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!"}})),
        vector<Sentence<TestToken>>({{{"Split"}, {"into"}, {"sentences"}, {"!"}}}));

    ASSERT_EQUAL(
        SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!", true}})),
        vector<Sentence<TestToken>>({{{"Split"}, {"into"}, {"sentences"}, {"!", true}}}));

    ASSERT_EQUAL(
        SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}, {"Without"}, {"copies"}, {".", true}})),
        vector<Sentence<TestToken>>({
            {{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}},
            {{"Without"}, {"copies"}, {".", true}},
        }));
}

struct NoncopyableToken
{
    string data;
    bool is_end_sentence_punctuation = false;

    bool IsEndSentencePunctuation() const
    {
        return is_end_sentence_punctuation;
    }
    bool operator==(const NoncopyableToken &other) const
    {
        return data == other.data && is_end_sentence_punctuation == other.is_end_sentence_punctuation;
    }
    NoncopyableToken(const NoncopyableToken &) = delete;
    NoncopyableToken &operator=(const NoncopyableToken &) = delete;

    NoncopyableToken(NoncopyableToken &&) = default;
    NoncopyableToken &operator=(NoncopyableToken &&) = default;
};

void TestNonCopyToken()
{

    vector<NoncopyableToken> data;
    data.push_back({"Split"});
    data.push_back({"into"});
    data.push_back({"sentences"});
    data.push_back({"!", true});
    data.push_back({"!", true});

    SplitIntoSentences(move(data));
}

void Benchmark()
{
    auto data = vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!", true}});
    {
        LOG_DURATION("Benchmark result");
        for (int i = 0; i < 1000000; i++)
            SplitIntoSentences(data);
    }
}
int main()
{
    // for (int i = 0; i < 5; i++)
    //     Benchmark();
    TestRunner tr;
    RUN_TEST(tr, TestSplitting);
    RUN_TEST(tr, TestNonCopyToken);
    return 0;
}
