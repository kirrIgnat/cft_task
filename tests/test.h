#ifndef TEST_H
#define TEST_H

#include <stdio.h>

/*
 *
 * макрос для запуска  теста
 *
 */
#define RUN_TEST(NAME, FUNC)                         \
    do {                                             \
        total++;                                     \
        if ((FUNC)()) {                              \
            printf("[ok]  %s\n", (NAME));            \
            passed++;                                \
        } else {                                     \
            fprintf(stderr, "[err] %s\n", (NAME));   \
        }                                            \
    } while (0)

#endif 
