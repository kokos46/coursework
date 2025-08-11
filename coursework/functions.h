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

#include "queueFunc.h"

void merge(Queue& a, int q, Queue& b, int r, Queue& c);
void split(Queue& S, Queue& a, Queue& b, int& n);
void mergeSort(Queue& S);

#endif
