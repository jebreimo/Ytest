#include "../../Ytest.hpp"

static void testFatalError()
{
    char* foo = nullptr;
    Y_NOT_EQUAL_FATAL(foo, (char*)nullptr);
}

Y_PRIORITIZED_TEST(-1, testFatalError);
