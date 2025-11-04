#ifndef IO_H
#define IO_H

#include <stddef.h> 
#include <stdio.h>    
#include <stdint.h> 
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>

#include "statdata.h"


StatError StoreDump(int file_desc, const StatData *data, size_t len);

StatError LoadDump(int file_desc, StatData **data_result, size_t *len_result);



#endif
