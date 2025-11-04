#ifndef CASES_H
#define CASES_H

/*
 * tests/cases.h
 * 
 */

#include "../include/statdata.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>

#include "statdata.h"
#include "io.h"
#include "util.h"
#include "core.h"
#include "test.h"



extern const StatData case_1_in_a[2];
extern const StatData case_1_in_b[2];

extern const StatData case_1_out[3];


int test_save_load_case_1(void);
int test_save_load_case_2(void);
int test_sort_case_1(void);
int test_sort_case_2(void);
int test_join_case_1(void);
int test_join_case_2(void);


#endif 
