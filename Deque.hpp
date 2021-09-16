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
    char type_name[14];
    MyClass * deque;
    size_t start;
    size_t end;
    size_t capacity;
    bool is_empty;
};

size_t Deque_MyClass_size(Deque_MyClass * cl) {
    if (cl->is_empty) return 0;
    if (cl->start == cl->end) return 1;
    if (cl->start < cl->end) return cl->end - cl->start + 1;
    return (cl->capacity - cl->start) + cl->end + 1;
}

bool Deque_MyClass_empty(Deque_MyClass * cl) {
    return cl->is_empty;
}

void Deque_MyClass_push_back(Deque_MyClass * cl, MyClass el) {
    // if empty
    if (cl->is_empty) {
        cl->is_empty = false;
        cl->deque[cl->start] = el;
    } else {
        // if full then expand
        
        // push_back
        if (cl->end == cl->capacity - 1) 
            cl->end = 0;
        else
            cl->end++;
        cl->deque[cl->end] = el;
    }
}

void Deque_MyClass_push_front(Deque_MyClass * cl, MyClass el) {
    // if empty
    if (cl->is_empty) {
        cl->is_empty = false;
        cl->deque[cl->start] = el;
    } else {
        // if full then expand
        
        // push_front
        if (cl->start == 0)
            cl->start = cl->capacity - 1;
        else
            cl->start--;
        cl->deque[cl->start] = el;
    }
}

MyClass & Deque_MyClass_front(Deque_MyClass * cl) {
    return cl->deque[cl->start];
}

MyClass & Deque_MyClass_back(Deque_MyClass * cl) {
    return cl->deque[cl->end];
}

void Deque_MyClass_pop_back(Deque_MyClass * cl) {
    // if empty
    if (cl->is_empty) return;
    // if 1 element (is nonempty)
    if (cl->start == cl->end) {
        cl->is_empty = true;
        cl->start = 0;
        cl->end = 0;
    }
    if (cl->end == 0)
        cl->end = cl->capacity - 1;
    else 
        cl->end--;
}

void Deque_MyClass_pop_front(Deque_MyClass * cl) {
    // if empty
    if (cl->is_empty) return;
    // if 1 element (is nonempty)
    if (cl->start == cl->end) {
        cl->is_empty = true;
        cl->start = 0;
        cl->end = 0;
    }
    if (cl->start == cl->capacity - 1)
        cl->start = 0;
    else
        cl->start++;
}

void Deque_MyClass_clear(Deque_MyClass * cl) {
    cl->start = 0;
    cl->end = 0;
    cl->is_empty = true;
}

void Deque_MyClass_dtor(Deque_MyClass * cl) {
    free(cl->deque);
}

void Deque_MyClass_ctor(Deque_MyClass * cl, bool (*comp)(const MyClass &, const MyClass &)) {
    cl->capacity = 8;
    cl->size = Deque_MyClass_size;
    cl->empty = Deque_MyClass_empty;
    cl->push_back = Deque_MyClass_push_back;
    cl->push_front = Deque_MyClass_push_front;
    cl->front = Deque_MyClass_front; 
    cl->back = Deque_MyClass_back;
    cl->pop_back = Deque_MyClass_pop_back;
    cl->pop_front = Deque_MyClass_pop_front;
    cl->dtor = Deque_MyClass_dtor;
    cl->clear = Deque_MyClass_clear;
    strcpy(cl->type_name, "Deque_" "MyClass");
    cl->deque = (MyClass *) malloc(sizeof(MyClass) * 8);
    cl->start = 0;
    cl->end = 0;
    cl->is_empty = true;
}


#endif
