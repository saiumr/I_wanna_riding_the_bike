#include <stdio.h>
#include "unittest.h"
#include "log.h"

int main(int argc, char** argv){
    log_level level;
    setLogLevel(LOG_ERROR);
    level = getLogLevel();
    ADD_TEST_TRUE("setLogLevel", level, LOG_ERROR);
    setLogLevel(LOG_INFO);
    ADD_OUTPUT_TEST("log_error", log_error("this is error"), "[ERROR]:this is error\n");
    ADD_OUTPUT_TEST("log_info", log_info("this is info"), "[INFO]:this is info\n");
    ADD_OUTPUT_TEST("log_debug", log_debug("this is debug"), "[DEBUG]:this is debug\n");
    ADD_OUTPUT_TEST("log_warn", log_warn("this is warn"), "[WARN]:this is warn\n");
    setLogLevel(LOG_ERROR);
    ADD_OUTPUT_TEST("log_error", log_error("this is error"), "[ERROR]:this is error\n");
    ADD_OUTPUT_TEST("log_info", log_info("this is info"), "");
    ADD_OUTPUT_TEST("log_debug", log_debug("this is debug"), "");
    ADD_OUTPUT_TEST("log_warn", log_warn("this is warn"), "");
    setLogLevel(LOG_DEBUG);
    ADD_OUTPUT_TEST("log_error", log_error("this is error"), "[ERROR]:this is error\n");
    ADD_OUTPUT_TEST("log_info", log_info("this is info"), "");
    ADD_OUTPUT_TEST("log_debug", log_debug("this is debug"), "[DEBUG]:this is debug\n");
    ADD_OUTPUT_TEST("log_warn", log_warn("this is warn"), "");
    setLogLevel(LOG_WARN);
    ADD_OUTPUT_TEST("log_error", log_error("this is error"), "[ERROR]:this is error\n");
    ADD_OUTPUT_TEST("log_info", log_info("this is info"), "");
    ADD_OUTPUT_TEST("log_debug", log_debug("this is debug"), "[DEBUG]:this is debug\n");
    ADD_OUTPUT_TEST("log_warn", log_warn("this is warn"), "[WARN]:this is warn\n");
    setLogLevel(LOG_OFF);
    ADD_OUTPUT_TEST("log_error", log_error("this is error"), "");
    ADD_OUTPUT_TEST("log_info", log_info("this is info"), "");
    ADD_OUTPUT_TEST("log_debug", log_debug("this is debug"), "");
    ADD_OUTPUT_TEST("log_warn", log_warn("this is warn"), "");

    /*
    setLogLevel(LOG_DEBUG);
    log_error("this will show an error messagebox");
    */
    //show messagebox must define MSGBOX_LOG in log.h

    TEST_SHOW_STATISTICS()
    TEST_PAUSE_CONSOLE()
    return 0;
}