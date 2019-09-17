#include "log.h"

void log_info(const char* msg){
    if(__loglevel <= LOG_INFO)
        printf("[INFO]:%s\n", msg);
}

void log_warn(const char* msg){
    if(__loglevel <= LOG_WARN)
        printf("[WARN]:%s\n", msg);
}

void log_error(const char* msg){
    if(__loglevel <= LOG_ERROR){
        #ifdef MSGBOX_LOG
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "error", msg, NULL);
        #endif
        printf("[ERROR]:%s\n", msg);
    }
}

void log_debug(const char* msg){
    if(__loglevel <= LOG_DEBUG)
        printf("[DEBUG]:%s\n", msg);
}

void setLogLevel(log_level level){
    if(level!=LOG_WARN && level!=LOG_INFO && level!=LOG_DEBUG && level!=LOG_ERROR)
        printf("[LOG SYSTEM ERROR]: set log level error\n");
    else
        __loglevel = level;
}

log_level getLogLevel(){
    return __loglevel;
}