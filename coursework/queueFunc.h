#ifndef _QUEUE_FUNC
#define _QUEUE_FUNC
#include "functions.h"
#include <cstdio>

struct List{
    Record data;
    List* next;
};

struct Queue {
    List* head;
    List* tail;
    
    Queue(){
        head = nullptr;
        tail = nullptr;
    }

    void add(const Record& el) {
        List* p = new List;
        p->data = el;
        p->next = nullptr;
        if (!head) { // если очередь пустая
            head = tail = p;
        } else {
            tail->next = p;
            tail = p;
        }
    }

    void print() {
        for (List* i = head; i != nullptr; i = i->next) {
            printf("%s\n", cp1251_to_utf8(i->data.name).c_str());
        }
    }

    void clear() {
        while (head) {
            List* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
    }
};


#endif
