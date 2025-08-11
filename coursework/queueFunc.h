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

    bool empty() const {
        return head == nullptr;
    }
    
    Record pop() {
        if (!head) throw "Queue is empty";
        List* temp = head;
        Record val = head->data;
        head = head->next;
        if (!head) tail = nullptr;
        delete temp;
        return val;
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
        printf("+------------+--------------------------------+----------------+-----+-----+\n");
        printf("|    Имя     |            Заглавие            |  Издательство  | Год | Стр |\n");
        printf("+------------+--------------------------------+----------------+-----+-----+\n");
        for (List* i = head; i != nullptr; i = i->next) {
            printf("| %12s", cp1251_to_utf8(i->data.name).c_str());
            printf("|  %32s", cp1251_to_utf8(i->data.header).c_str());
            printf("| %16s", cp1251_to_utf8(i->data.publisher).c_str());
            printf("|%5d", i->data.year);
            printf("|%5d|\n", i->data.page_count);
        }
        printf("+------------+--------------------------------+----------------+-----+-----+\n");
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
