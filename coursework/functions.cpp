#include "functions.h"

std::string cp1251_to_utf8(const char* cp1251_str)
{
    iconv_t cd = iconv_open("UTF-8", "IBM866");
    if (cd == (iconv_t)-1) {
        return cp1251_str; // fallback — если iconv не открылся
    }

    size_t in_bytes = strlen(cp1251_str);
    size_t out_bytes = in_bytes * 2 + 1; // UTF-8 может быть больше
    std::string utf8_str(out_bytes, '\0');

    char* in_buf = const_cast<char*>(cp1251_str);
    char* out_buf = utf8_str.data();

    iconv(cd, &in_buf, &in_bytes, &out_buf, &out_bytes);
    iconv_close(cd);

    // обрезаем по фактической длине
    utf8_str.resize(strlen(utf8_str.c_str()));
    return utf8_str;
}

int less(Record a, Record b){
    if (a.year < b.year){
        return 1;
    }
    else if (a.year > b.year) return 0;
    else{
        if (strcmp(a.name, b.name) <= 0){
            return 1;
        }
        return 0;
    }
}

void merge(Queue& a, int q, Queue& b, int r, Queue& c) {
    while (q > 0 && r > 0) {
        if (less(a.head->data, b.head->data)) {
            c.add(a.pop());
            q--;
        } else {
            c.add(b.pop());
            r--;
        }
    }
    
    while (q > 0) {
        c.add(a.pop());
        q--;
    }
    
    while (r > 0) {
        c.add(b.pop());
        r--;
    }
}

void split(Queue& S, Queue& a, Queue& b, int& n) {
    if (S.empty()) {
        n = 0;
        return;
    }
    
    a.add(S.pop());
    n = 1;
    
    if (S.empty()) {
        return;
    }
    
    b.add(S.pop());
    n = 2;
    
    List* k = a.head;
    List* p = b.head;
    
    while (!S.empty()) {
        k->next = S.head;
        k = S.head;
        n++;
        S.head = S.head->next;
        if (S.empty()) break;
        
        p->next = S.head;
        p = S.head;
        n++;
        S.head = S.head->next;
    }
    
    k->next = nullptr;
    p->next = nullptr;
    a.tail = k;
    b.tail = p;
}

void mergeSort(Queue& S) {
    int n;
    Queue a, b;
    split(S, a, b, n);
    
    if (n <= 1) {
        if (!a.empty()) S.add(a.pop());
        return;
    }
    
    int p = 1;
    while (p < n) {
        Queue c[2];
        int i = 0;
        int m = n;
        
        while (m > 0) {
            int q = (m >= p) ? p : m;
            m -= q;
            
            int r = (m >= p) ? p : m;
            m -= r;
            
            if (i == 0) {
                merge(a, q, b, r, c[0]);
            } else {
                merge(a, q, b, r, c[1]);
            }
            
            i = 1 - i;
        }
        
        a = c[0];
        b = c[1];
        p *= 2;
    }
    
    // Переносим отсортированные данные обратно в S
    while (!a.empty()) {
        S.add(a.pop());
    }
    while (!b.empty()) {
        S.add(b.pop());
    }
}
