/**
 * @file unittest.h
 * @VisualGMQ
 * @brief 一个小的单元测试系统
 * @version 0.1
 * @date 2019-09-17
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef __UNITTEST_H__
#define __UNITTEST_H__
#include <stdio.h>
#include <string.h>

static unsigned int __unittest_success_num = 0;
static unsigned int __unittest_totle = 0;

/**
 * @brief 用于判断表达式exp与result是否相等
 * 
 */
#define ADD_TEST_TRUE(name, exp, result) \
__unittest_totle++;\
if(exp==result){    \
    printf("[%s]: expression 「%s==%s」    test success\t\t✔️\n", name, #exp, #result);    \
    __unittest_success_num++;   \
}else{  \
    printf("[%s]: expression 「%s==%s」    test failed\t\t❌\n", name, #exp, #result); \
}

/**
 * @brief 用于判断表达式exp和result是否不等
 * 
 */
#define ADD_TEST_FALSE(name, exp, result) \
__unittest_totle++;\
if(exp!=result){    \
    printf("[%s]: expression 「%s!=%s」    test success\t\t✔️️️️\n", name, #exp, result);    \
    __unittest_success_num++;   \
}else{  \
    printf("[%s]: expression 「%s!=%s」    test failed\t\t❌\n", name, #exp, result); \
}

/**
 * @brief 用于判断函数func的输出和result是否相等
 * 
 */
#define ADD_OUTPUT_TEST(name, func, result) \
{\
    int i = 0;\
    __unittest_totle++;\
    char buffer[1024] = {0};\
    setbuf(stdout, buffer);\
    func;\
    fflush(stdout);\
    setbuf(stdout, NULL);\
    for(i=0;i<strlen(buffer);i++)\
        putchar('\b');\
    if(strcmp(buffer, result) == 0){\
        printf("[%s]: output 「%s」    test success\t\t✔️\n", name, buffer);    \
        __unittest_success_num++;   \
    }else{\
        printf("[%s]: output 「%s」    test failed\t\t❌\n", name, buffer); \
    }\
    fflush(stdout);\
}

/**
 * @brief 用来显示最后测试结果的宏
 * 
 * @warn 这个宏最好放在main()函数的底部，在所有测试用例都编写完之后再使用
 * 
 */
#define TEST_SHOW_STATISTICS() printf("\n----------test result----------:\n\
totle num:     %d\n\
success num:   %d\n\
rate:          %.0f%%\n", __unittest_totle, __unittest_success_num, (float)__unittest_success_num/__unittest_totle*100);

#endif