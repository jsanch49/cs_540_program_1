#ifndef __Deque__
#define __Deque__

#include <string.h>

struct MyClass {
    int id;
    char name[10];   
};

#define Deque_DEFINE(type)                                                  \
    struct Deque_##type; \
    struct Deque_##type##_Iterator { \
        void (*inc)(Deque_##type##_Iterator *); \
        void (*dec)(Deque_##type##_Iterator *); \
        type & (*deref)(Deque_##type##_Iterator *); \
        type * container; \
        size_t capacity; \
        size_t idx; \
    }; \
    struct Deque_##type {                                                   \
        size_t (*size)(Deque_##type *);                                     \
        bool (*empty)(Deque_##type *);                                      \
        void (*push_back)(Deque_##type *, type);                            \
        void (*push_front)(Deque_##type *, type);                           \
        type & (*front)(Deque_##type *);                                    \
        type & (*back)(Deque_##type *);                                     \
        Deque_##type##_Iterator (*begin)(Deque_##type *); \
        Deque_##type##_Iterator (*end)(Deque_##type *); \
        void (*pop_front)(Deque_##type *);                                  \
        void (*pop_back)(Deque_##type *);                                   \
        void (*clear)(Deque_##type *);                                      \
        type & (*at)(Deque_##type *, size_t);                               \
        bool (*comp)(const type &, const type &); \
        void (*dtor)(Deque_##type *);                                       \
        char type_name[6+sizeof(#type)];                                    \
        type * deque;                                                       \
        size_t first;                                                       \
        size_t last;                                                        \
        size_t capacity;                                                    \
        bool is_empty;                                                      \
    };                                                                      \
    void Deque_##type##_Iterator_inc(Deque_##type##_Iterator * cl) { \
        if(cl->idx == cl->capacity - 1) cl->idx = 0; \
        else cl->idx++; \
    } \
    void Deque_##type##_Iterator_dec(Deque_##type##_Iterator * cl) { \
        if (cl->idx == 0) cl->idx = cl->capacity - 1; \
        else cl->idx--; \
    } \
    type & Deque_##type##_Iterator_deref(Deque_##type##_Iterator * cl) { \
        return cl->container[cl->idx]; \
    } \
    bool Deque_##type##_Iterator_equal(Deque_##type##_Iterator i1, Deque_##type##_Iterator i2) { \
        return (&i1.deref(&i1) == &i2.deref(&i2)); \
    } \
    void Deque_##type##_Iterator_ctor(Deque_##type##_Iterator * cl, type * container) { \
        cl->inc = Deque_##type##_Iterator_inc; \
        cl->dec = Deque_##type##_Iterator_dec; \
        cl->deref = Deque_##type##_Iterator_deref; \
        cl->container = container; \
    } \
    Deque_##type##_Iterator Deque_##type##_begin(Deque_##type * cl) { \
        Deque_##type##_Iterator itr; \
        Deque_##type##_Iterator_ctor(&itr, cl->deque);  \
        itr.idx = cl->first; \
        itr.capacity = cl->capacity; \
        return itr; \
    } \
    Deque_##type##_Iterator Deque_##type##_end(Deque_##type * cl) { \
        Deque_##type##_Iterator itr; \
        Deque_##type##_Iterator_ctor(&itr, cl->deque); \
        if (cl->last == cl->capacity -1) itr.idx = 0; \
        else itr.idx = cl->last + 1; \
        itr.capacity = cl->capacity; \
        return itr; \
    } \
    size_t Deque_##type##_size(Deque_##type * cl) {                         \
        if (cl->is_empty) return 0;                                         \
        if (cl->first == cl->last) return 1;                                \
        if (cl->first < cl->last) return cl->last - cl->first + 1;          \
        return (cl->capacity - cl->first) + cl->last + 1;                   \
    }                                                                       \
    bool Deque_##type##_empty(Deque_##type * cl) {                          \
        return cl->is_empty;                                                \
    }                                                                       \
    void Deque_##type##_push_back(Deque_##type * cl, type el) {             \
        if (cl->is_empty) {                                                 \
            cl->is_empty = false;                                           \
            cl->deque[cl->first] = el;                                      \
        } else {                                                            \
            if (cl->last + 1 == cl->first || cl->last - cl->first == cl->capacity - 1 ) {   \
                type * new_deque = (type *)malloc(sizeof(type) * cl->capacity * 2);\
                for (size_t i = 0; i < cl->capacity; i++) {                 \
                    size_t j = (cl->first+i)&(cl->capacity - 1);            \
                    new_deque[i] = cl->deque[j];                            \
                }                                                           \
                free(cl->deque);                                            \
                cl->deque = new_deque;                                      \
                cl->first = 0;                                              \
                cl->last = cl->capacity - 1;                                \
                cl->capacity = 2*cl->capacity;                              \
            }                                                               \
            if (cl->last == cl->capacity - 1)                               \
                cl->last = 0;                                               \
            else                                                            \
                cl->last++;                                                 \
            cl->deque[cl->last] = el;                                       \
        }                                                                   \
    }                                                                       \
    void Deque_##type##_push_front( Deque_##type * cl, type el) {           \
        if (cl->is_empty) {                                                 \
            cl->is_empty = false;                                           \
            cl->deque[cl->first] = el;                                      \
        } else {                                                            \
            if (cl->last + 1 == cl->first || cl->last - cl->first == cl->capacity - 1 ) {   \
                type * new_deque = (type *)malloc(sizeof(type) * cl->capacity * 2);\
                for (size_t i = 0; i < cl->capacity; i++) {                 \
                    size_t j = (cl->first+i)&(cl->capacity - 1);            \
                    new_deque[i] = cl->deque[j];                            \
                }                                                           \
                free(cl->deque);                                            \
                cl->deque = new_deque;                                      \
                cl->first = 0;                                              \
                cl->last = cl->capacity - 1;                                \
                cl->capacity = 2*cl->capacity;                              \
            }                                                               \
            if (cl->first == 0)                                             \
                cl->first = cl->capacity - 1;                               \
            else                                                            \
                cl->first--;                                                \
            cl->deque[cl->first] = el;                                      \
        }                                                                   \
    }                                                                       \
    type & Deque_##type##_front(Deque_##type * cl) {                        \
        return cl->deque[cl->first];                                        \
    }                                                                       \
    type & Deque_##type##_at(Deque_##type * cl, size_t idx) { \
        size_t i = (cl->first + idx) & (cl->capacity - 1); \
        return cl->deque[i];  \
    } \
    type & Deque_##type##_back(Deque_##type * cl) {                         \
        return cl->deque[cl->last];                                         \
    }                                                                       \
    void Deque_##type##_pop_back(Deque_##type * cl) {                       \
        if (cl->is_empty) return;                                           \
        if (cl->first == cl->last) {                                        \
            cl->is_empty = true;                                            \
            cl->first = 0;                                                  \
            cl->last = 0;                                                   \
        } else {                                                                  \
            if (cl->last == 0)                                                  \
                cl->last = cl->capacity - 1;                                    \
            else                                                                \
                cl->last--;                                                     \
        }                               \
    }                                                                       \
    void Deque_##type##_pop_front(Deque_##type * cl) {                      \
        if (cl->is_empty) return; \
        if (cl->first == cl->last) { \
            cl->is_empty = true; \
            cl->first = 0; \
            cl->last = 0; \
        } else { \
            if (cl->first == cl->capacity - 1) \
                cl->first = 0; \
            else \
                cl->first++; \
        } \
    } \
    void Deque_##type##_clear(Deque_##type * cl) { \
        cl->first = 0; \
        cl->last = 0; \
        cl->is_empty = true; \
    } \
    void Deque_##type##_dtor(Deque_##type * cl) { \
        free(cl->deque); \
    } \
    void Deque_##type##_ctor(Deque_##type * cl, bool (*comp)(const type &, const type &)) { \
        cl->capacity = 8; \
        cl->size = Deque_##type##_size; \
        cl->empty = Deque_##type##_empty; \
        cl->at = Deque_##type##_at; \
        cl->push_back = Deque_##type##_push_back; \
        cl->push_front = Deque_##type##_push_front; \
        cl->front = Deque_##type##_front;  \
        cl->back = Deque_##type##_back; \
        cl->pop_back = Deque_##type##_pop_back; \
        cl->pop_front = Deque_##type##_pop_front; \
        cl->dtor = Deque_##type##_dtor; \
        cl->clear = Deque_##type##_clear; \
        cl->begin = Deque_##type##_begin; \
        cl->end = Deque_##type##_end; \
        cl->comp = comp; \
        strcpy(cl->type_name, "Deque_" #type); \
        cl->deque = (type *) malloc(sizeof(type) * 8); \
        cl->first = 0; \
        cl->last = 0; \
        cl->is_empty = true; \
    } \
    bool Deque_##type##_equal(Deque_##type & o1, Deque_##type & o2) { \
        if (o1.size(&o1) != o2.size(&o2)) return false; \
        auto itr1 = o1.begin(&o1); \
        auto itr2 = o2.begin(&o2); \
        for (size_t i = 0; i < o1.size(&o1); i++) { \
            if (o1.comp(itr1.deref(&itr1), itr2.deref(&itr2)) || \
            o1.comp(itr2.deref(&itr2), itr1.deref(&itr1)) ) \
                return false; \
            itr1.inc(&itr1); \
            itr2.inc(&itr2); \
        } \
        return true; \
    } 
    
Deque_DEFINE(MyClass) 
#endif
