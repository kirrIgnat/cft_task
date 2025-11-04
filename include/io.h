#ifndef IO_H
#define IO_H

#include <stddef.h> 
#include "statdata.h"

StatError LoadDump(const char *path, StatData **data_out, size_t *len_out);

StatError StoreDump(const char *path, const StatData *data, size_t len);

#endif
