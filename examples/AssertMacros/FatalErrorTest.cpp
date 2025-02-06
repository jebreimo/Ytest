#include "Ytest/Ytest.hpp"

static void testFatalError()
{
    char* foo = nullptr;
    Y_NOT_EQUAL_FATAL(foo, static_cast<char*>(nullptr));
}

Y_PRIORITIZED_TEST(-1, testFatalError);
