#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>


#include "statdata.h"
#include "io.h"
#include "util.h"

/*
 * main.c
 *  точка входа
 *
 */

static void print_error() {}

int main(int argc, char **argv) {
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
}
