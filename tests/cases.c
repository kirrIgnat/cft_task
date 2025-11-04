#include "cases.h"

/*
 * tests/cases.s
 * 
 */


const StatData case_1_in_a[2] = {
    { .id = 90889, .count = 13,  .cost = 3.567f,   .primary = 0, .mode = 3 },
    { .id = 90089, .count = 1,   .cost = 88.90f,   .primary = 1, .mode = 0 }
};

const StatData case_1_in_b[2] = {
    { .id = 90089, .count = 13,   .cost = 0.011f,   .primary = 0, .mode = 2 },
    { .id = 90189, .count = 1000, .cost = 1.00003f, .primary = 1, .mode = 2 }
};

const StatData case_1_out[3] = {
    { .id = 90189, .count = 1000, .cost = 1.00003f, .primary = 1, .mode = 2 },
    { .id = 90889, .count = 13,   .cost = 3.567f,   .primary = 0, .mode = 3 },
    { .id = 90089, .count = 14,   .cost = 88.911f,  .primary = 0, .mode = 2 }
};

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

int test_save_load_case_1(void)
{
    const char *path = "tests/tmp_case1.bin";

    int fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("[LOAD SAVE 1] open for write");
        return 0;
    }

    StatError err = StoreDump(fd, case_1_in_a, 2);
    close(fd);

    if (err != STAT_OK) {
        fprintf(stderr, "[LOAD SAVE 1] StoreDump err: code %d\n", (int)err);
        return 0;
    }

    fd = open(path, O_RDONLY);
    if (fd < 0) {
        perror("[LOAD SAVE 1] open for read");
        return 0;
    }

    StatData *loaded = NULL;
    size_t len = 0;

    err = LoadDump(fd, &loaded, &len);
    close(fd);

    if (err != STAT_OK) {
        fprintf(stderr, "[LOAD SAVE 1]LoadDump err: code %d\n", (int)err);
        free(loaded);
        return 0;
    }

    int ok = 1;
    if (len != 2) {
        fprintf(stderr, "[LOAD SAVE 1] length err expected 2, heve %zu\n", len);
        ok = 0;
    } else if (!compare_arrays(case_1_in_a, loaded, len)) {
        fprintf(stderr, "[LOAD SAVE 1] data err in save/load test\n");
        ok = 0;
    }

    if (!ok) {
        fprintf(stderr, "[LOAD SAVE 1] expected:\n");
        PrintTable(case_1_in_a, 2);
        fprintf(stderr, "have:\n");
        PrintTable(loaded, len);
    }

    free(loaded);
    unlink(path);
    return ok;
}

int test_save_load_case_2(void)
{
    const char *path = "tests/tmp_case2_empty.bin";

    const StatData empty_arr[1] = { 0 };

    int fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("open for write");
        return 0;
    }

    StatError err = StoreDump(fd, empty_arr, 0);
    close(fd);

    if (err != STAT_OK) {
        fprintf(stderr, "StoreDump empty err: %d\n", (int)err);
        return 0;
    }

    fd = open(path, O_RDONLY);
    if (fd < 0) {
        perror("open for read");
        return 0;
    }

    StatData *loaded = NULL;
    size_t len = 123;

    err = LoadDump(fd, &loaded, &len);
    close(fd);

    if (err != STAT_OK) {
        fprintf(stderr, "LoadDump (empty) err: %d\n", (int)err);
        free(loaded);
        return 0;
    }

    int ok = (loaded == NULL && len == 0);

    if (!ok) {
        fprintf(stderr, "[SAVE/LOAD 2] expected len=0, have %zu\n", len);
    }

    free(loaded);
    unlink(path);
    return ok;
}


int test_sort_case_1(void)
{
    StatData arr[4] = {
        { .id = 3, .count = 1, .cost = 5.0f,  .primary = 1, .mode = 0 }, 
        { .id = 1, .count = 1, .cost = 5.0f,  .primary = 1, .mode = 0 }, 
        { .id = 2, .count = 1, .cost = 1.0f,  .primary = 1, .mode = 0 }, 
        { .id = 4, .count = 1, .cost = 10.0f, .primary = 1, .mode = 0 }  
    };

    const StatData expected[4] = {
        { .id = 2, .count = 1, .cost = 1.0f,  .primary = 1, .mode = 0 },
        { .id = 1, .count = 1, .cost = 5.0f,  .primary = 1, .mode = 0 },
        { .id = 3, .count = 1, .cost = 5.0f,  .primary = 1, .mode = 0 },
        { .id = 4, .count = 1, .cost = 10.0f, .primary = 1, .mode = 0 }
    };

    SortDump(arr, 4);

    int ok = 1;
    if (!compare_arrays(arr, expected, 4)) {
        fprintf(stderr, "[SORT 1]sort data mismatch\n");
        ok = 0;
    }

    if (!ok) {
        fprintf(stderr, "[SORT 1] ok\n");
        PrintTable(expected, 4);
        fprintf(stderr, "have\n");
        PrintTable(arr, 4);
    }

    return ok;
}
int test_sort_case_2(void)
{
    StatData arr[5] = {
        { .id = 5, .count = 1, .cost = 2.0f, .primary = 1, .mode = 0 },
        { .id = 3, .count = 1, .cost = 2.0f, .primary = 1, .mode = 0 },
        { .id = 1, .count = 1, .cost = 1.0f, .primary = 1, .mode = 0 },
        { .id = 4, .count = 1, .cost = 5.0f, .primary = 1, .mode = 0 },
        { .id = 2, .count = 1, .cost = 2.0f, .primary = 1, .mode = 0 }
    };

    const StatData expected[5] = {
        { .id = 1, .count = 1, .cost = 1.0f, .primary = 1, .mode = 0 },
        { .id = 2, .count = 1, .cost = 2.0f, .primary = 1, .mode = 0 },
        { .id = 3, .count = 1, .cost = 2.0f, .primary = 1, .mode = 0 },
        { .id = 5, .count = 1, .cost = 2.0f, .primary = 1, .mode = 0 },
        { .id = 4, .count = 1, .cost = 5.0f, .primary = 1, .mode = 0 }
    };

    SortDump(arr, 5);

    int ok = 1;
    if (!compare_arrays(arr, expected, 5)) {
        fprintf(stderr, "[SORT 2] sort tie-break mismatch\n");
        ok = 0;
    }

    if (!ok) {
        fprintf(stderr, "[SORT 2] expected:\n");
        PrintTable(expected, 5);
        fprintf(stderr, "have\n");
        PrintTable(arr, 5);
    }

    return ok;
}


int test_join_case_1(void)
{
    const StatData in_a[2] = {
        { .id = 10, .count = 1, .cost = 1.0f, .primary = 1, .mode = 1 },
        { .id = 10, .count = 2, .cost = 2.0f, .primary = 1, .mode = 3 }
    };

    const StatData in_b[1] = {
        { .id = 20, .count = 5, .cost = 5.0f, .primary = 0, .mode = 2 }
    };

    const StatData expected[2] = {
        { .id = 10, .count = 3, .cost = 3.0f, .primary = 1, .mode = 3 },
        { .id = 20, .count = 5, .cost = 5.0f, .primary = 0, .mode = 2 }
    };

    StatData *joined = NULL;
    size_t len_joined = 0;

    StatError err = JoinDump(in_a, 2,
                             in_b, 1,
                             &joined, &len_joined);
    if (err != STAT_OK) {
        fprintf(stderr, "[JOIN 1]JoinDump err in: code %d\n", (int)err);
        return 0;
    }

    int ok = 1;

    if (len_joined != 2) {
        fprintf(stderr, "[JOIN 1] join length err: expected 2 but have %zu\n", len_joined);
        ok = 0;
    } else if (!compare_arrays(joined, expected, 2)) {
        fprintf(stderr, "[JOIN 1] join data err\n");
        ok = 0;
    }

    if (!ok) {
        fprintf(stderr, "[JOIN 1] expected:\n");
        PrintTable(expected, 2);
        fprintf(stderr, "have:\n");
        PrintTable(joined, len_joined);
    }
    free(joined);
    return ok;
}
int test_join_case_2(void)
{
    const StatData in_a[2] = {
        { .id = 1, .count = 5, .cost = 1.0f, .primary = 1, .mode = 2 },
        { .id = 2, .count = 7, .cost = 7.0f, .primary = 0, .mode = 1 }
    };

    const StatData in_b[2] = {
        { .id = 1, .count = 3, .cost = 2.0f, .primary = 0, .mode = 5 }, /* пересечение id=1 */
        { .id = 3, .count = 9, .cost = 9.0f, .primary = 1, .mode = 7 }
    };

    const StatData expected[3] = {
        { .id = 1, .count = 8, .cost = 3.0f, .primary = 0, .mode = 5 },
        { .id = 2, .count = 7, .cost = 7.0f, .primary = 0, .mode = 1 },
        { .id = 3, .count = 9, .cost = 9.0f, .primary = 1, .mode = 7 }
    };

    StatData *joined = NULL;
    size_t len_joined = 0;

    StatError err = JoinDump(in_a, 2, in_b, 2, &joined, &len_joined);
    if (err != STAT_OK) {
        fprintf(stderr, "[JOIN 2] JoinDump failed: %d\n", (int)err);
        return 0;
    }

    int ok = 1;
    if (len_joined != 3) {
        fprintf(stderr, "[JOIN 2] expected len=3, have %zu\n", len_joined);
        ok = 0;
    } else if (!compare_arrays(joined, expected, 3)) {
        fprintf(stderr, "[JOIN 2] data mismatch\n");
        ok = 0;
    }

    if (!ok) {
        fprintf(stderr, "[JOIN 2] expected:\n");
        PrintTable(expected, 3);
        fprintf(stderr, "have\n");
        PrintTable(joined, len_joined);
    }

    free(joined);
    return ok;
}
