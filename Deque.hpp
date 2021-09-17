#ifndef __Deque__
#define __Deque__

#include <string.h>

struct MyClass {
    int id;
    char name[10];   
};

#define Deque_DEFINE(type)                                                  \
    struct Deque_##type {                                                   \
        size_t (*size)(Deque_##type *);                                     \
        bool (*empty)(Deque_##type *);                                      \
        void (*push_back)(Deque_##type *, type);                            \
        void (*push_front)(Deque_##type *, type);                           \
        type & (*front)(Deque_##type *);                                    \
        type & (*back)(Deque_##type *);                                     \
        void (*pop_front)(Deque_##type *);                                  \
        void (*pop_back)(Deque_##type *);                                   \
        void (*clear)(Deque_##type *);                                      \
        type & (*at)(Deque_##type *, size_t);                               \
        void (*dtor)(Deque_##type *);                                       \
        char type_name[6+sizeof(#type)];                                                 \
        type * deque;                                                       \
        size_t first;                                                       \
        size_t last;                                                        \
        size_t capacity;                                                    \
        bool is_empty;                                                      \
    };                                                                      \
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
        strcpy(cl->type_name, "Deque_" #type); \
        cl->deque = (type *) malloc(sizeof(type) * 8); \
        cl->first = 0; \
        cl->last = 0; \
        cl->is_empty = true; \
    }
    
    
Deque_DEFINE(MyClass) 




#endif
