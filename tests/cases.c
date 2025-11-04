#include "cases.h"

/*
 * tests/cases.s
 * набор константных тестовых данных
 * для тестирования 
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
