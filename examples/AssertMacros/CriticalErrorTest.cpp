#include "Ytest/Ytest.hpp"

static void testCriticalError()
{
    char* foo = nullptr;
    Y_NOT_EQUAL_CRITICAL(foo, static_cast<char*>(nullptr));
}

Y_TEST(testCriticalError);
