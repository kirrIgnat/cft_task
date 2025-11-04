#include <stdio.h>

#include "statdata.h"
#include "util.h"


/*
 * util.c 
 *  PrintTable печать первых n записей
 *  формировка поля mode в двоичном виде
 */

//static void format_mode_binary() {}

void PrintTable(const StatData *data, size_t len) {
    if (!data || len == 0){
        printf("no data");
        return;
    }

    printf("----------STATDATA---------\n");
    printf(" id count cost primary mode\n");

    for (size_t i=0; i < len; i++){
        const StatData *note = &data[i];
        printf("%ld %4d %8.3f %u %6u\n", note->id, note->count, note->cost, note->primary, note->mode);
    }
}
