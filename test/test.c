#include <stdio.h>
#include "cutest.h"
#include "../include/lib.h"

void test_hello_world(void)
{
    printf("Hello World");
    TEST_CHECK_((1 != 0 ),"1 should be equal to 0 !");
}


void test_multiply(void)
{
    int num = 2;
    int result = multiply_by_two(num);
    TEST_CHECK_((result == num*2),"ok");
}

TEST_LIST = {
        { "test_hello_world", test_hello_world },
        { "test_multiply", test_multiply},
        { 0 }
};
