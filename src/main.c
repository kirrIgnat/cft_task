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
    const StatData in_a[2] = {
        { .id = 1, .count = 13,  .cost = 3.567f,   .primary = 0, .mode = 3 },
        { .id = 2, .count = 1,   .cost = 88.90f,   .primary = 1, .mode = 4 }
    };

    const StatData in_b[2] = {
        { .id = 23, .count = 13,   .cost = 0.011f,   .primary = 0, .mode = 2 },
        { .id = 2, .count = 1000, .cost = 1.00003f, .primary = 1, .mode = 2 }
    };

    StatData *joined = NULL;
    size_t len_joined = 0;

    StatError err = JoinDump(in_a, 2, in_b, 2, &joined, &len_joined);
    if (err != STAT_OK) {
        fprintf(stderr, "JoinDump failed: code %d\n", (int)err);
        return 1;
    }

    printf("JoinDump() result — уникальные id после объединения:\n");
    SortDump(joined, len_joined);
    PrintTable(joined, len_joined);

    free(joined);
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
