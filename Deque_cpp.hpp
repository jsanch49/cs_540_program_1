#ifndef __Deque__
#define __Deque__

#include <string.h>

#define Deque_DEFINE(e)

struct MyClass {
    int id;
    char name[10];   
};

//new
struct Deque_MyClass;
struct Deque_MyClass_Iterator {
    void (*inc)(Deque_MyClass_Iterator *);
    void (*dec)(Deque_MyClass_Iterator *);
    MyClass & (*deref)(Deque_MyClass_Iterator *);
    MyClass * container;
    size_t capacity;
    size_t idx;
};

struct Deque_MyClass {
    size_t (*size)(Deque_MyClass *);
    bool (*empty)(Deque_MyClass *);
    void (*push_back)(Deque_MyClass *, MyClass);
    void (*push_front)(Deque_MyClass *, MyClass);
    MyClass & (*front)(Deque_MyClass *);
    MyClass & (*back)(Deque_MyClass *);
    MyClass & (*at)(Deque_MyClass *, size_t);
    bool (*comp)(const MyClass &, const MyClass &);
    void (*pop_front)(Deque_MyClass *);
    void (*pop_back)(Deque_MyClass *);
    void (*clear)(Deque_MyClass *);
    void (*dtor)(Deque_MyClass *);
    Deque_MyClass_Iterator (*begin)(Deque_MyClass *);
    Deque_MyClass_Iterator (*end)(Deque_MyClass *);
    char type_name[14];
    MyClass * deque;
    size_t first;
    size_t last;
    size_t capacity;
    bool is_empty;
};

void Deque_MyClass_Iterator_inc(Deque_MyClass_Iterator * cl) {
    if(cl->idx == cl->capacity - 1) cl->idx = 0;
    else cl->idx++;
}

void Deque_MyClass_Iterator_dec(Deque_MyClass_Iterator * cl) {
    if (cl->idx == 0) cl->idx = cl->capacity - 1;
    else cl->idx--;
}

MyClass & Deque_MyClass_Iterator_deref(Deque_MyClass_Iterator * cl) {
    return cl->container[cl->idx];
}

bool Deque_MyClass_Iterator_equal(Deque_MyClass_Iterator i1, Deque_MyClass_Iterator i2) {
    return (&i1.deref(&i1) == &i2.deref(&i2));
}

void Deque_MyClass_Iterator_ctor(Deque_MyClass_Iterator * cl, MyClass * container) {
    cl->inc = Deque_MyClass_Iterator_inc;
    cl->dec = Deque_MyClass_Iterator_dec;
    cl->deref = Deque_MyClass_Iterator_deref;
    cl->container = container;
}
Deque_MyClass_Iterator Deque_MyClass_begin(Deque_MyClass * cl) {
    Deque_MyClass_Iterator itr;
    Deque_MyClass_Iterator_ctor(&itr, cl->deque);  
    itr.idx = cl->first;
    itr.capacity = cl->capacity;
    return itr;
}

Deque_MyClass_Iterator Deque_MyClass_end(Deque_MyClass * cl) {
    Deque_MyClass_Iterator itr;
    Deque_MyClass_Iterator_ctor(&itr, cl->deque);
    if (cl->last == cl->capacity -1) itr.idx = 0;
    else itr.idx = cl->last + 1;
    itr.capacity = cl->capacity;
    return itr;
}

size_t Deque_MyClass_size(Deque_MyClass * cl) {
    if (cl->is_empty) return 0;
    if (cl->first == cl->last) return 1;
    if (cl->first < cl->last) return cl->last - cl->first + 1;
    return (cl->capacity - cl->first) + cl->last + 1;
}

bool Deque_MyClass_empty(Deque_MyClass * cl) {
    return cl->is_empty;
}

void Deque_MyClass_push_back(Deque_MyClass * cl, MyClass el) {
    // if empty
    if (cl->is_empty) {
        cl->is_empty = false;
        cl->deque[cl->first] = el;
    } else {
        // if full then expand
        if (cl->last + 1 == cl->first || cl->last - cl->first == cl->capacity - 1 ) {
            MyClass * new_deque = (MyClass *)malloc(sizeof(MyClass) * cl->capacity * 2);
            for (size_t i = 0; i < cl->capacity; i++) {
                size_t j = (cl->first+i)&(cl->capacity - 1);
                new_deque[i] = cl->deque[j];
            } 
            free(cl->deque);
            cl->deque = new_deque;
            cl->first = 0;
            cl->last = cl->capacity - 1;
            cl->capacity = 2*cl->capacity;
        }        
        // push_back
        if (cl->last == cl->capacity - 1) 
            cl->last = 0;
        else
            cl->last++;
        cl->deque[cl->last] = el;
    }
}

void Deque_MyClass_push_front(Deque_MyClass * cl, MyClass el) {
    // if empty
    if (cl->is_empty) {
        cl->is_empty = false;
        cl->deque[cl->first] = el;
    } else {
        // if full then expand
        if (cl->last + 1 == cl->first || cl->last - cl->first == cl->capacity - 1 ) {
            MyClass * new_deque = (MyClass *)malloc(sizeof(MyClass) * cl->capacity * 2);
            for (size_t i = 0; i < cl->capacity; i++) {
                size_t j = (cl->first+i)&(cl->capacity - 1);
                new_deque[i] = cl->deque[j];
            } 
            free(cl->deque);
            cl->deque = new_deque;
            cl->first = 0;
            cl->last = cl->capacity - 1;
            cl->capacity = 2*cl->capacity;
        }        
        // push_front
        if (cl->first == 0)
            cl->first = cl->capacity - 1;
        else
            cl->first--;
        cl->deque[cl->first] = el;
    }
}

MyClass & Deque_MyClass_front(Deque_MyClass * cl) {
    return cl->deque[cl->first];
}

MyClass & Deque_MyClass_back(Deque_MyClass * cl) {
    return cl->deque[cl->last];
}

MyClass & Deque_MyClass_at(Deque_MyClass * cl, size_t idx) {
    size_t i = (cl->first + idx) & (cl->capacity - 1);
    return cl->deque[i];
}

void Deque_MyClass_pop_back(Deque_MyClass * cl) {
    // if empty
    if (cl->is_empty) return;
    // if 1 element (is nonempty)
    if (cl->first == cl->last) {
        cl->is_empty = true;
        cl->first = 0;
        cl->last = 0;
    } else {
        if (cl->last == 0)
            cl->last = cl->capacity - 1;
        else 
            cl->last--;
    }
}

void Deque_MyClass_pop_front(Deque_MyClass * cl) {
    // if empty
    if (cl->is_empty) return;
    // if 1 element (is nonempty)
    if (cl->first == cl->last) {
        cl->is_empty = true;
        cl->first = 0;
        cl->last = 0;
    } else {
        if (cl->first == cl->capacity - 1)
            cl->first = 0;
        else
            cl->first++;
    }
}

void Deque_MyClass_clear(Deque_MyClass * cl) {
    cl->first = 0;
    cl->last = 0;
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
    cl->at = Deque_MyClass_at;
    cl->pop_back = Deque_MyClass_pop_back;
    cl->pop_front = Deque_MyClass_pop_front;
    cl->dtor = Deque_MyClass_dtor;
    cl->clear = Deque_MyClass_clear;
    cl->comp = comp;
    cl->begin = Deque_MyClass_begin;
    cl->end = Deque_MyClass_end;
    strcpy(cl->type_name, "Deque_" "MyClass");
    cl->deque = (MyClass *) malloc(sizeof(MyClass) * 8);
    cl->first = 0;
    cl->last = 0;
    cl->is_empty = true;
}

bool Deque_MyClass_equal(Deque_MyClass & o1, Deque_MyClass & o2) {
    if (o1.size(&o1) != o2.size(&o2)) return false;
    auto itr1 = o1.begin(&o1);
    auto itr2 = o2.begin(&o2);
    for (size_t i = 0; i < o1.size(&o1); i++) {
        if (o1.comp(itr1.deref(&itr1), itr2.deref(&itr2)) || 
            o1.comp(itr2.deref(&itr2), itr1.deref(&itr1))) return false;
        itr1.inc(&itr1);
        itr2.inc(&itr2);
    }
    return true;
}

#endif
