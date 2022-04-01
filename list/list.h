//
// Created by preya on 3/28/2022.
//

#ifndef LIST_H
#define LIST_H

#include <stddef.h>

typedef struct value {
    void* val;
    char type;
} Val;

typedef struct list {
    Val** value;
    size_t size;
    size_t cap;
} List;

List* l_init();
int isEmpty(List *l);
int l_add(List *l, void *v, char type);
int l_insert(List *l, void *v, int index, char type);
int l_remove_first(List *l);
int l_remove(List *l, int index);
int l_remove_last(List *l);
void* l_get_first(List *l);
void* l_get(List *l, int index);
void* l_get_last(List *l);
List* l_slice(List *l, int start, int end);
void l_invert(List *l);
int  l_extend_list(List *dest, List *add);
void l_print(List *l);
void l_destroy(List *l);


#endif //LIST_H
