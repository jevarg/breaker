#pragma once

#ifdef NDEBUG
    #define LOG(...)
#else
    #define LOG(...) printf(__VA_ARGS__)
#endif

void print_error(const char *str);