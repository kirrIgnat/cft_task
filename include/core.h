#ifndef CORE_H
#define CORE_H

#include <stddef.h> 
#include "statdata.h"

StatError JoinDump(const StatData *first, size_t len_first, 
    const StatData *second, size_t len_second,
    StatData **result, size_t *len_result);

StatError SortDump(StatData *data, size_t len_data);

#endif
