/**
 * @file unittest.h
 * @VisualGMQ
 * @brief a small unit test system
 * @version 0.1
 * @date 2019-09-17
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef __UNITTEST_H__
#define __UNITTEST_H__
#include <stdio.h>
#include <assert.h>
#include <string.h>

static unsigned int __unittest_success_num = 0;
static unsigned int __unittest_totle = 0;

#define ADD_TEST_TRUE(name, exp, result) \
__unittest_totle++;\
if(exp==result){    \
    printf("[%s]: expression 「%s==%s」    test success\t\t✔️\n", name, #exp, #result);    \
    __unittest_success_num++;   \
}else{  \
    printf("[%s]: expression 「%s==%s」    test failed\t\t❌\n", name, #exp, #result); \
}

#define ADD_TEST_FALSE(name, exp, result) \
__unittest_totle++;\
if(exp!=result){    \
    printf("[%s]: expression 「%s!=%s」    test success\t\t✔️️️️\n", name, #exp, result);    \
    __unittest_success_num++;   \
}else{  \
    printf("[%s]: expression 「%s!=%s」    test failed\t\t❌\n", name, #exp, result); \
}

#define ADD_OUTPUT_TEST(name, func, result) \
{\
    int i = 0;\
    __unittest_totle++;\
    char buffer[1024*1024] = {0};\
    setbuf(stdout, buffer);\
    func;\
    fflush(stdout);\
    setbuf(stdout, NULL);\
    for(i=0;buffer[i]!='\0';i++)\
        putchar('\b');\
    if(strcmp(buffer, result) == 0){\
        printf("[%s]: output 「%s」    test success\t\t✔️\n", name, buffer);    \
        __unittest_success_num++;   \
    }else{\
        printf("[%s]: output 「%s」    test failed\t\t❌\n", name, buffer); \
    }\
    fflush(stdout);\
}

#define TEST_SHOW_STATISTICS() printf("\n----------test result----------:\n\
totle num:     %d\n\
success num:   %d\n\
rate:          %.0f%%\n", __unittest_totle, __unittest_success_num, (float)__unittest_success_num/__unittest_totle*100);

#endif