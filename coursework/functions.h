#ifndef _FUNCTIONS
#define _FUNCTIONS
#include <iconv.h>
#include <string>

struct Record {
    char name[12];
    char header[32];
    char publisher[16];
    short year;
    short page_count;
};

std::string cp1251_to_utf8(const char* cp1251_str);

#endif
