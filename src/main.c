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
 */

static void print_usage(const char *prog)
{
    fprintf(stderr,
            "Usage: %s <in_a> <in_b> <out>\n"
            "in_a is the path to the first input file (StatData dump)\n"
            "in_b is the path to the second input file (StatData dump)\n"
            "out path to the output file (resulting dump)\n",
            prog);
}

static void print_stat_error(const char *where, StatError err)
{
    fprintf(stderr, "%s: error %d\n", where, (int)err);
}

int main(int argc, char **argv)
{
    if (argc != 4) {
        print_usage(argv[0]);
        return 1;
    }

    const char *path_a   = argv[1];
    const char *path_b   = argv[2];
    const char *path_out = argv[3];

    StatData *a = NULL;
    StatData *b = NULL;
    StatData *joined = NULL;
    size_t len_a = 0;
    size_t len_b = 0;
    size_t len_joined = 0;
    StatError err = STAT_OK;

    /* 1. read 1 file */
    int file_desc_a = open(path_a, O_RDONLY);
    if (file_desc_a < 0) {
        perror("open in_a");
        return 1;
    }

    err = LoadDump(file_desc_a, &a, &len_a);
    close(file_desc_a);

    if (err != STAT_OK) {
        print_stat_error("LoadDump(in_a)", err);
        free(a);
        return 1;
    }

    /* 2. read 2 file */
    int file_desc_b = open(path_b, O_RDONLY);
    if (file_desc_b < 0) {
        perror("open in_b");
        free(a);
        return 1;
    }

    err = LoadDump(file_desc_b, &b, &len_b);
    close(file_desc_b);

    if (err != STAT_OK) {
        print_stat_error("LoadDump(in_b)", err);
        free(a);
        free(b);
        return 1;
    }

    /* 3. join */
    err = JoinDump(a, len_a, b, len_b, &joined, &len_joined);
    free(a);
    free(b);

    if (err != STAT_OK) {
        print_stat_error("JoinDump", err);
        free(joined);
        return 1;
    }

    /* 4. sort */
    
    err = SortDump(joined, len_joined);
    if (err != STAT_OK) {
        print_stat_error("SortDump", err);
        free(joined);
        return 1;
    }

    /* 5. print */
    size_t to_print;
    if (len_joined < 10)
        to_print = len_joined;
    else 
        to_print = 10;


    if (to_print > 0)
        PrintTable(joined, to_print);
    else 
        printf("(no data)\n");
    

    /* 6. save */
    int file_desc_out = open(path_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (file_desc_out < 0) {
        perror("open out");
        free(joined);
        return 1;
    }

    err = StoreDump(file_desc_out, joined, len_joined);
    close(file_desc_out);

    if (err != STAT_OK) {
        print_stat_error("StoreDump(out)", err);
        free(joined);
        return 1;
    }

    free(joined);
    return 0;
}