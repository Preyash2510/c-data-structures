//
// Created by preya on 3/28/2022.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "list.h"

List* l_init(){
    List *l = (List *) malloc(sizeof(List));
    l -> value = NULL;
    l -> size = 0;
    l -> cap = 0;

    return l;
}

int isEmpty(List *l){
    return (int) l -> size;
}

void increaseSize(List *l){
    if(isEmpty(l) == 0){
        Val **ptr = (Val**) malloc(sizeof(Val*) * (l -> size + 1));
        if(ptr == NULL) {
            fprintf(stderr, "*** Error: No memory!");
            exit(-1);
        }
        l -> value = ptr;
    } else {
        Val **ptr = (Val**) realloc(l -> value, sizeof(Val*) * (l -> size + 1));
        if(ptr == NULL) {
            fprintf(stderr, "*** Error: No memory!");
            exit(-1);
        }
        l -> value = ptr;
    }
    ++l -> cap;
}

Val* add_new_val(void *v, char type){
    Val *ptr = (Val*) malloc(sizeof(Val));
    if(ptr == NULL) {
        return ptr;
    }

    size_t size;
    switch(type){
        case 'i': { ptr -> val = malloc(sizeof(int)); size = sizeof(int); } break;
        case 'l': { ptr -> val = malloc(sizeof(long)); size = sizeof(long); } break;
        case 'f': { ptr -> val = malloc(sizeof(float)); size = sizeof(float); } break;
        case 'd': { ptr -> val = malloc(sizeof(double)); size = sizeof(double); } break;
        case 'c': { ptr -> val = malloc(sizeof(char)); size = sizeof(char); } break;
        case 's': { ptr -> val = malloc(sizeof(char) * (strlen(v) + 1)); size = sizeof(char) * (strlen(v) + 1); } break;
        case 'L': { ptr -> val = malloc(sizeof(List)); size = sizeof(List); } break;
        default: return NULL;
    }

    if(ptr -> val == NULL){
        return ptr -> val;
    }
    memcpy(ptr -> val, v, size);
    ptr -> type = type;

    return ptr;
}

int l_add(List *l, void *v, char type){
    increaseSize(l);

    Val *ptr = add_new_val(v, type);
    if(ptr == NULL) {
        fprintf(stderr, "*** Error: No memory!");
        exit(-1);
        return -1;
    }
    l -> value[l -> size] = ptr;

    ++l -> size;

    return 0;
}

int l_insert(List *l, void *v, int index, char type) {
    increaseSize(l);

    Val *ptr = add_new_val(v, type);
    if(ptr == NULL) {
        fprintf(stderr, "*** Error: No memory!");
        exit(-1);
        return -1;
    }

    for(int i = (int) l -> size; i > index; --i) {
        l -> value[i] = l -> value[i - 1];
    }

    l -> value[index] = ptr;

    ++l -> size;

    return 0;
}

int l_remove(List *l, int index) {
    if(index < 0) {
        return -1;
    }

    if ((l -> size - 1) == 0) {
        if(l -> value[0] -> type == 'L'){
            l_destroy(l -> value[0] -> val);
        } else {
            free(l -> value[0] -> val);
        }
        free(l -> value[0]);
        free(l -> value);
        l -> value = NULL;
    } else {
        Val** ptr = (Val**) malloc(sizeof(Val*) * (l -> size - 1));
        if(ptr == NULL) {
            fprintf(stderr, "*** Error: No memory!");
            exit(-1);
            return -1;
        }

        for(int i = 0; i < l -> size; ++i) {
            if(i != index) {
                if(i > index) {
                    ptr[i - 1] = l -> value[i];
                } else {
                    ptr[i] = l -> value[i];
                }
            }
        }

        if(l -> value[index] -> type == 'L'){
            l_destroy(l -> value[index] -> val);
        } else {
            free(l -> value[index] -> val);
        }
        free(l -> value[index]);
        free(l -> value);
        l -> value = ptr;
    }

    --l -> size;

    return 0;
}

int l_remove_first(List *l) {
    return l_remove(l, 0);
}

int l_remove_last(List *l) {
    return l_remove(l, (int) l -> size - 1);
}

void* l_get(List *l, int index) {
    return l -> value[index] -> val;
}

void* l_get_first(List *l) {
    return l_get(l, 0);
}

void* l_get_last(List *l) {
    return l_get(l, (int) l -> size - 1);
}

List* l_slice(List *l, int start, int end) {
    List* slice = l_init();

    if(start < 0 && end == 0) {
        for(int i = (int) l -> size - 1; i >= l -> size + start; --i) {
            l_add(slice, l -> value[i] -> val, l -> value[i] -> type);
        }
    } else {
        for(int i = start; i < end; ++i) {
            l_add(slice, l -> value[i] -> val, l -> value[i] -> type);
        }
    }

    return slice;
}

int  l_extend_list(List *dest, List *add) {
    for(int i = 0; i < add -> size; ++i){
        if(l_add(dest, add -> value[i] -> val, add -> value[i] -> type) != 0){
            return -1;
        }
    }

    return 0;
}

void l_invert(List *l) {

    for(int i = 0, j = (int) l -> size -1; i < j; ++i, --j) {
        Val* temp = l -> value[i];
        l -> value[i] = l -> value[j];
        l -> value[j] = temp;
    }
}

void l_print(List *l){
    printf("[");
    for (int i = 0; i < l -> size; ++i){
        switch (l -> value[i]->type) {
            case 'i': printf("%d, ", *((int*) l -> value[i]->val)); break;
            case 'l': printf("%ld, ", *((long*) l -> value[i]->val)); break;
            case 'f': printf("%f, ", *((float*) l -> value[i]->val)); break;
            case 'd': printf("%lf, ", *((double*) l -> value[i]->val)); break;
            case 'c': printf("%c, ", *((char*) l -> value[i]->val)); break;
            case 's': printf("\'%s\', ", ((char*) l -> value[i]->val)); break;
            case 'L': l_print((List *) l -> value[i]->val); printf(",\n"); break;
            default: printf("Unknown Type, "); break;
        }
    }
    printf("\b\b]\n");
}

void l_destroy(List *l){
    for(int i = 0; i < l -> size; ++i){
        if(l -> value[i] -> type == 'L'){
            l_destroy(l -> value[i] -> val);
        } else {
            free(l -> value[i] -> val);
        }
        free(l -> value[i]);
    }
    free(l -> value);

    free(l);
}