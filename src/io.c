 #include "io.h"
/*
 * io.c 
 * бинарная сериализация и десериализация
 * 
 */

static StatError read_full(int file_desc, void *buf, size_t bytes)
{
    char *b = (char *)buf;
    size_t remains = bytes;

    while (remains > 0) {
        ssize_t r = read(file_desc, b, remains);
        if (r < 0)
            return STAT_ERR_IO;
        if (r == 0)
            return STAT_ERR_FORMAT; 

        remains -= (size_t)r;
        b    += r;
    }

    return STAT_OK;
}


StatError StoreDump(int file_desc, const StatData *data, size_t len) {
    if (file_desc < 0 || (data == NULL && len > 0))
        return STAT_ERR_INVALID_ARG;

    uint64_t n = (uint64_t)len;

    ssize_t written = write(file_desc, &n, sizeof(n));
    if (written != (ssize_t)sizeof(n))
        return STAT_ERR_IO;

    if (len == 0)
        return STAT_OK;

    size_t total_bytes = len * sizeof(StatData);
    written = write(file_desc, data, total_bytes);
    if (written != (ssize_t)total_bytes)
        return STAT_ERR_IO;

    return STAT_OK;
}

StatError LoadDump(int file_desc, StatData **data_result, size_t *len_result) {
     if (file_desc < 0 || data_result == NULL || len_result == NULL)
        return STAT_ERR_INVALID_ARG;

    *data_result = NULL;
    *len_result  = 0;

    uint64_t n = 0;
    StatError err = read_full(file_desc, &n, sizeof(n));
    if (err != STAT_OK)
        return err;

    if (n == 0) 
        return STAT_OK;
    

    if (n > SIZE_MAX / sizeof(StatData))
        return STAT_ERR_FORMAT;

    size_t len = (size_t)n;
    StatData *buf = malloc(len * sizeof(StatData));
    if (buf == NULL)
        return STAT_ERR_ALLOC;

    err = read_full(file_desc, buf, len * sizeof(StatData));
    if (err != STAT_OK) {
        free(buf);
        return err;
    }

    *data_result = buf;
    *len_result  = len;
    return STAT_OK;
}
