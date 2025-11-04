#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>


#include "statdata.h"
#include "io.h"
#include "util.h"
#include "core.h"

/*
 * main.c
 *  точка входа
 *
 */

static void print_error() {}

int main(int argc, char **argv) {
    StatData arr[3] = {
        { .id = 2, .count = 1, .cost = 10.0f, .primary = 1, .mode = 0 },
        { .id = 3, .count = 1, .cost =  5.0f, .primary = 1, .mode = 0 },
        { .id = 1, .count = 1, .cost =  5.0f, .primary = 1, .mode = 0 },
    };

    SortDump(arr, 3);


    PrintTable(arr,3);
    return 0;

    /*
    
    
    StatData *arr = NULL;
    size_t len = 0;

    int fd = open("dump_fd.bin", O_RDONLY);
    if (fd < 0)
        return 1;

    StatError err = LoadDump(fd, &arr, &len);
    close(fd);

    if (err != STAT_OK)
        return 1;

    PrintTable(arr, len);
    free(arr);

    return 0;
    */
}
