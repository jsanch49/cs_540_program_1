#ifndef __Deque__
#define __Deque__

#include <string.h>

#define Deque_DEFINE(e)

struct MyClass {
    int id;
    char name[10];   
};

struct Deque_MyClass {
    size_t (*size)(Deque_MyClass *);
    bool (*empty)(Deque_MyClass *);
    void (*push_back)(Deque_MyClass *, MyClass);
    void (*push_front)(Deque_MyClass *, MyClass);
    MyClass & (*front)(Deque_MyClass *);
    MyClass & (*back)(Deque_MyClass *);
    void (*pop_front)(Deque_MyClass *);
    void (*pop_back)(Deque_MyClass *);
    void (*clear)(Deque_MyClass *);
    void (*dtor)(Deque_MyClass *);
    char * type_name;
    MyClass * deque;
    size_t start;
    size_t end;
    size_t m_size;
};

size_t Deque_MyClass_size(Deque_MyClass * cl) {
    return cl->m_size;
}

bool Deque_MyClass_empty(Deque_MyClass * cl) {
    return cl->m_size == 0;
}

void Deque_MyClass_push_back(Deque_MyClass * cl, MyClass el) {
    return;
}

void Deque_MyClass_push_front(Deque_MyClass * cl, MyClass el) {
    return;
}

MyClass & Deque_MyClass_front(Deque_MyClass * cl) {
    return cl->deque[cl->start];
}

MyClass & Deque_MyClass_back(Deque_MyClass * cl) {
    return cl->deque[cl->end];
}

void Deque_MyClass_pop_back(Deque_MyClass * cl) {
    return;
}

void Deque_MyClass_pop_front(Deque_MyClass * cl) {
    return;
}

void Deque_MyClass_clear(Deque_MyClass * cl) {
    cl->start = 0;
    cl->end = 0;
}

void Deque_MyClass_dtor(Deque_MyClass * cl) {
    free(cl->type_name);
}

void Deque_MyClass_ctor(Deque_MyClass * cl, bool (*comp)(const MyClass &, const MyClass &)) {
    cl->m_size = 0;
    cl->size = Deque_MyClass_size;
    cl->empty = Deque_MyClass_empty;
    cl->push_back = Deque_MyClass_push_back;
    cl->push_front = Deque_MyClass_push_front;
    cl->front = Deque_MyClass_front; 
    cl->back = Deque_MyClass_back;
    cl->pop_back = Deque_MyClass_pop_back;
    cl->pop_front = Deque_MyClass_pop_front;
    cl->dtor = Deque_MyClass_dtor;
    cl->type_name = (char *)malloc(sizeof("MyClass")+6);
    cl->clear = Deque_MyClass_clear;
    strcpy(cl->type_name, "Deque_" "MyClass");
    cl->start = 1;
    cl->end = 1;
}


#endif
