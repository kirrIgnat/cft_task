#ifndef UTIL_H
#define UTIL_H

#include <stddef.h> 
#include "statdata.h"

void PrintTable(const StatData *data, size_t len);
static void format_mode_binary(unsigned int mode, char *buf, size_t bufsize);

#endif
