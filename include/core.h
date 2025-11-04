#ifndef CORE_H
#define CORE_H

#include <stddef.h> 
#include "statdata.h"

StatError JoinDump(const StatData *first, size_t len_fitst, 
    const StatData *second, size_t len_seconmd,
    StatData **result, size_t *len_result);

StatError SortDump(StatData *data, size_t len_data);

#endif
