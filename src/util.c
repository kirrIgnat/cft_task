#include "util.h"


/*
 * util.c 
 *  PrintTable печать первых n записей
 *  формировка поля mode в двоичном виде
 */

static void format_mode_binary(unsigned int mode, char *buf, size_t bufsize){
    char tmp[4];
    int pos = 0;
    int bit;

    for (bit = 2; bit >= 0; bit--) {
        if (mode & (1u << bit))
            tmp[pos++] = '1';
        else
            tmp[pos++] = '0';
    }

    int first = 0;
    while (first < pos - 1 && tmp[first] == '0')
        first++;

    int len = pos - first;
    if ((size_t)len >= bufsize)
        len = (int)bufsize - 1;

    for (int i = 0; i < len; i++)
        buf[i] = tmp[first + i];
    buf[len] = '\0';
}

void PrintTable(const StatData *data, size_t len) {
    if (!data || len == 0){
        printf("no data");
        return;
    }
    size_t limit = len;
    if (limit > 10)
        limit = 10;

    printf("\n-----------------STATDATA-----------------\n");
    printf("%-12s %-8s %-12s %-8s %-8s\n",
           "id(hex)", "count", "cost", "primary", "mode");

    for (size_t i = 0; i < limit; i++) {
        const StatData *note = &data[i];
        char mode_buf[8];
        char primary_ch = note->primary ? 'y' : 'n';
        format_mode_binary(note->mode, mode_buf, sizeof(mode_buf));

        printf("0x%08lx  %-8d %10.3e     %-8c %-8s\n",
               (unsigned long)note->id,
               note->count,
               (double)note->cost,
               primary_ch,
               mode_buf);
    }

    printf("-------------------------------------------\n");
}

