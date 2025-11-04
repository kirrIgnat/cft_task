#include "cases.h"

/*
 * tests/main.c 
 * тестирование
 */



int main(void)
{
    int passed = 0;
    int total = 0;

    struct timespec t0, t1;
    clock_gettime(CLOCK_MONOTONIC, &t0);

    RUN_TEST("test_save_load_case_1", test_save_load_case_1);
    RUN_TEST("test_save_load_case_2", test_save_load_case_2);
    RUN_TEST("test_join_case_1", test_join_case_1);
    RUN_TEST("test_join_case_2", test_join_case_2);
    RUN_TEST("test_sort_case_1", test_sort_case_1);
    RUN_TEST("test_sort_case_2", test_sort_case_2);
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