#include "Ytest/Ytest.hpp"
#include <stdexcept>
#include <vector>

namespace
{
    double divide(double a, double b)
    {
        if (b == 0)
            throw std::invalid_argument("division by zero");
        return a / b;
    }

    void throwsSuccessful()
    {
        Y_THROWS(divide(1, 0), std::logic_error);
    }

    void throwsUnsuccessful()
    {
        Y_THROWS(divide(5, 2.5), std::logic_error);
    }

    void assertSuccessful()
    {
        std::vector<int> foo;
        Y_ASSERT(foo.empty());
    }

    void assertUnsuccessful()
    {
        std::vector<int> foo(2);
        Y_ASSERT(foo.empty());
    }

    void assertMsgSuccessful()
    {
        std::vector<int> foo;
        Y_ASSERT_MSG(foo.empty(), "Vector isn't empty!");
    }

    void assertMsgUnsuccessful()
    {
        std::vector<int> foo(2);
        Y_ASSERT_MSG(foo.empty(), "Vector isn't empty!");
    }

    void equalSuccessful()
    {
        Y_EQUAL(divide(10, 2), 5);
    }

    void equalUnsuccessful()
    {
        Y_EQUAL(divide(10, 3), 3.333);
    }

    void equivalentSuccessful()
    {
        Y_EQUIVALENT(divide(10, 3), 3.333, 0.001);
    }

    void equivalentUnsuccessful()
    {
        Y_EQUIVALENT(divide(10, 3), 3.333, 0.0001);
    }

    void notEqualSuccessful()
    {
        Y_NOT_EQUAL(divide(10, 2), 4.999);
    }

    void notEqualUnsuccessful()
    {
        Y_NOT_EQUAL(divide(10, 2), 5);
    }

    void equalRangesSuccessful()
    {
      std::vector<double> v;
      v.push_back(1); v.push_back(2); v.push_back(3); v.push_back(4);
      std::vector<int> u;
      u.push_back(1); u.push_back(2); u.push_back(3); u.push_back(4);
      Y_EQUAL_RANGES(v, u);
    }

    void equalRangesUnsuccessful_not_equal()
    {
      std::vector<double> v;
      v.push_back(1); v.push_back(2); v.push_back(3); v.push_back(4);
      std::vector<int> u;
      u.push_back(1); u.push_back(2); u.push_back(4);
      Y_EQUAL_RANGES(v, u);
    }

    void equalRangesUnsuccessful_longer_left()
    {
      std::vector<double> v;
      v.push_back(1); v.push_back(2); v.push_back(3); v.push_back(4);
      std::vector<int> u;
      u.push_back(1); u.push_back(2); u.push_back(3);
      Y_EQUAL_RANGES(v, u);
    }

    void equalRangesUnsuccessful_longer_right()
    {
      std::vector<double> v;
      v.push_back(1); v.push_back(2); v.push_back(3);
      std::vector<int> u;
      u.push_back(1); u.push_back(2); u.push_back(3); u.push_back(4);
      Y_EQUAL_RANGES(v, u);
    }

    void failure()
    {
        std::vector<int> v;
        for (int i = 0; i < 10; ++i)
            v.push_back(i * i);
        if (v.size() != 11)
            Y_FAILURE("Added 10 elements, should have been 11.");
    }

    void subtest(const std::string& s, char c, size_t count)
    {
        Y_ASSERT(!s.empty());
        size_t pos = 0;
        size_t actualCount = 0;
        while (true)
        {
            pos = s.find_first_of(c, pos);
            if (pos == std::string::npos)
                break;
            ++pos;
            ++actualCount;
        }
        Y_EQUAL(actualCount, count);
    }

    void subSuccessful()
    {
        Y_CALL(subtest("abcdabcdabcd", 'a', 3));
        Y_CALL(subtest("abcdabcdabcd", 'b', 3));
        Y_CALL(subtest("abcdabcdabcd", 'f', 0));
    }

    void subUnsuccessful()
    {
        Y_CALL(subtest("abcdabcdabcd", 'a', 3));
        Y_CALL(subtest("abcdabcdabcd", 'b', 3));
        Y_CALL(subtest("abcdabcdabcd", 'f', 3)); // This test fails
    }

    void stringTypes_u16()
    {
#if (!defined(_MSC_VER) || _MSC_VER >= 1900)
        std::u16string s(u"FooBar");
        Y_EQUAL(s, u"Foozball");
#endif
    }

    void stringTypes_u32()
    {
#if (!defined(_MSC_VER) || _MSC_VER >= 1900)
        std::u32string s(U"FooBar");
        Y_EQUAL(s, U"Foozball");
#endif
    }

    void stringTypes_w()
    {
        std::wstring s(L"FooBar");
        Y_EQUAL(s, L"Foozball");
    }

    void charTypes()
    {
        Y_EQUAL(wchar_t('F'), wchar_t('F'));
        Y_EQUAL(char8_t('F'), char8_t('F'));
        Y_EQUAL(char16_t('F'), char16_t('F'));
        Y_EQUAL(char32_t('F'), char32_t('F'));
    }

    void charRanges()
    {
        Y_EQUAL_RANGES(std::u16string_view(u"ABCD"), std::u16string(u"ABCW"));
    }

    Y_TEST(throwsSuccessful,
           throwsUnsuccessful,
           assertSuccessful,
           assertUnsuccessful,
           assertMsgSuccessful,
           assertMsgUnsuccessful,
           equalSuccessful,
           equalUnsuccessful,
           equivalentSuccessful,
           equivalentUnsuccessful,
           notEqualSuccessful,
           notEqualUnsuccessful,
           equalRangesSuccessful,
           equalRangesUnsuccessful_not_equal,
           equalRangesUnsuccessful_longer_left,
           equalRangesUnsuccessful_longer_right,
           failure,
           subSuccessful,
           subUnsuccessful,
           stringTypes_u16,
           stringTypes_u32,
           stringTypes_w,
           charTypes,
           charRanges);
}
