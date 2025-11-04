#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>

#include "statdata.h"
#include "io.h"
#include "util.h"
#include "cases.h"
#include "test.h"

/*
 * tests/main.c 
 * тестирование
 */

static int compare_arrays(const StatData *a, const StatData *b, size_t len)
{
    const float EPS = 1e-5f;

    for (size_t i = 0; i < len; i++) {
        if (a[i].id != b[i].id)
            return 0;
        if (a[i].count != b[i].count)
            return 0;
        if (a[i].primary != b[i].primary)
            return 0;
        if (a[i].mode != b[i].mode)
            return 0;

        float diff = a[i].cost - b[i].cost;
        if (diff < 0)
            diff = -diff;
        if (diff > EPS)
            return 0;
    }
    return 1;
}

static int test_save_load_case_1(void)
{
    const char *path = "tmp_case1.bin";

    int fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("open for write");
        return 0;
    }

    StatError err = StoreDump(fd, case_1_in_a, 2);
    close(fd);

    if (err != STAT_OK) {
        fprintf(stderr, "StoreDump err: code %d\n", (int)err);
        return 0;
    }

    fd = open(path, O_RDONLY);
    if (fd < 0) {
        perror("open for read");
        return 0;
    }

    StatData *loaded = NULL;
    size_t len = 0;

    err = LoadDump(fd, &loaded, &len);
    close(fd);

    if (err != STAT_OK) {
        fprintf(stderr, "LoadDump err: code %d\n", (int)err);
        free(loaded);
        return 0;
    }

    int ok = 1;
    if (len != 2) {
        fprintf(stderr, "length err expected 2, heve %zu\n", len);
        ok = 0;
    } else if (!compare_arrays(case_1_in_a, loaded, len)) {
        fprintf(stderr, "data err in save/load test\n");
        ok = 0;
    }

    if (!ok) {
        fprintf(stderr, "expected:\n");
        PrintTable(case_1_in_a, 2);
        fprintf(stderr, "have:\n");
        PrintTable(loaded, len);
    }

    free(loaded);
    return ok;
}

int main(void)
{
    int passed = 0;
    int total = 0;

    struct timespec t0, t1;
    clock_gettime(CLOCK_MONOTONIC, &t0);

    RUN_TEST("test_save_load_case_1", test_save_load_case_1);
    /* позже:
       RUN_TEST("test_join_case_1", test_join_case_1);
       RUN_TEST("test_sort_case_1", test_sort_case_1);
    */

    clock_gettime(CLOCK_MONOTONIC, &t1);

    double elapsed = (t1.tv_sec - t0.tv_sec)
                   + (t1.tv_nsec - t0.tv_nsec) / 1e9;

    if (passed == total) {
        printf("\nall tests passed (%d/%d).\n", passed, total);
        printf("time: %.6f seconds\n", elapsed);
    } else {
        fprintf(stderr, "\nsome tests failed (%d/%d).\n", passed, total);
        fprintf(stderr, "time: %.6f seconds\n", elapsed);
    }

    return (passed == total) ? 0 : 1;
}
