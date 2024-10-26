#ifndef UTIL_LOG_H_
#define UTIL_LOG_H_

#include"../config/config.h.in"

#include<iostream>
#include"console.h"

#ifdef DEBUG
#define LOG(o, s) o << "[" << CONSOLE_GREEN << "LOG" << CONSOLE_WHITE << "]" << s << std::endl
#define LOGS(s) std::cout << "[" << CONSOLE_GREEN << "LOG" << CONSOLE_WHITE << "]" << s << std::endl
#define LOG_ERROR(s) std::cerr << "[" << CONSOLE_RED << "ERROR" << CONSOLE_WHITE << "]In " << __FILE__ << ":\n\tLine " << __LINE__ << ": " << s << std::endl
#endif // DEBUG
#ifndef DEBUG
#define LOG(o, s) do{}while(false)    //do nothing
#define LOG_ERROR(s) do{}while(false)
#endif // DEBUG

#endif // UTIL_LOG_H_