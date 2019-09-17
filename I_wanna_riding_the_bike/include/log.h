/**
 * @file log.h
 * @VisualGMQ
 * @brief a small log system
 * @version 0.1
 * @date 2019-09-17
 * 
 * @copyright Copyright (c) 2019
 * 
 * if defined MSGBOX_LOG, then the error log will show by messagebox
 * the priority is: INFO>WARN>DEBUG>ERROR
 * if you set LOG_OFF, it will not show any log
 */
#ifndef __LOG_H__
#define __LOG_H__
#include <stdio.h>
#include <time.h>
#define LOG_ERROR   1001
#define LOG_DEBUG   1002
#define LOG_WARN    1003
#define LOG_INFO    1004
#define LOG_OFF     1005
typedef unsigned int log_level;

static log_level __loglevel = LOG_INFO;

void log_info(const char* msg);
void log_warn(const char* msg);
void log_debug(const char* msg);
void log_error(const char* msg);

void setLogLevel(log_level level);
log_level getLogLevel();

#endif