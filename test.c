//
// Created by preya on 3/28/2022.
//

#include <stdio.h>
#include <stdlib.h>
#include "list/list.h"

int main(){

    List *l = l_init();

    char c[5] = "Hell\0";

    l_add(l, c, 's');
    char b[5] = "o Wo\0";
    l_add(l, b, 's');
    char a[5] = "rld!\0";
    l_insert(l, a, 1, 's');
    printf("First Look after Insert aty [1]:\t");
    l_print(l);

    List *slice = l_slice(l, -2, 0);
    printf("Slice[-2] (last two element):\t\t");
    l_print(slice);

    l_extend_list(l, slice);
    printf("Add slice to List l:\t\t\t");
    l_print(l);

    l_invert(l);
    printf("Invert the List:\t\t\t");
    l_print(l);

    l_destroy(l);
    l_destroy(slice);

    return 0;
}

