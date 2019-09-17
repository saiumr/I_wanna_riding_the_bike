#include <stdio.h>
#include "unittest.h"
#include "log.h"

int main(){
    log_level level;
    setLogLevel(LOG_ERROR);
    getLogLevel();
    printf("%d\n", level);
    ADD_TEST_TRUE("setLogLevel", level, LOG_ERROR);
    ADD_OUTPUT_TEST("log_error", log_error("this is error"), "[ERROR]:this is error\n");
    ADD_OUTPUT_TEST("log_info", log_info("this is info"), "[INFO]:this is info\n");
    ADD_OUTPUT_TEST("log_debug", log_debug("this is debug"), "[DEBUG]:this is debug\n");
    ADD_OUTPUT_TEST("log_warn", log_warn("this is warn"), "[WARN]:this is warn\n");
    TEST_SHOW_STATISTICS();
    return 0;
}