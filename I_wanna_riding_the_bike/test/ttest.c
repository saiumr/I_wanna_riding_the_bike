#include "unittest.h"
#include <string.h>

void say(){
    printf("this is a output");
}

int main(){
    ADD_TEST_TRUE("test1", 1, 2)
    ADD_TEST_TRUE("test2", 1, 1)
    ADD_TEST_TRUE("test3", strcmp("asd", "asd"), 0)
    ADD_OUTPUT_TEST("test say", say(), "this is a output")
    ADD_OUTPUT_TEST("test say", say(), "this is not a output")
    TEST_SHOW_STATISTICS()
    return 0;
}