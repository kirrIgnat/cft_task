#include "core.h"


/*
 * core.c 
 *  JoinDump объединение двух массивов StatData
 *  SortDump сортировка по полю cost
 *
 */

static int statdata_cmp_cost(const StatData *first, const StatData *second)
{
    if (first->cost < second->cost)
        return -1;
    if (first->cost > second->cost)
        return 1;

    if (first->id < second->id)
        return -1;
    if (first->id > second->id)
        return 1;

    return 0;
}

static void statdata_swap(StatData *first, StatData *second)
{
    StatData tmp = *first;
    *first = *second;
    *second = tmp;
}

static void statdata_quicksort(StatData *arr, long lo, long hi)
{
    while (lo < hi) {
        long i = lo;
        long j = hi;
        StatData pivot = arr[(lo + hi) / 2];

        while (i <= j) {
            while (statdata_cmp_cost(&arr[i], &pivot) < 0)
                i++;
            while (statdata_cmp_cost(&arr[j], &pivot) > 0)
                j--;

            if (i <= j) {
                statdata_swap(&arr[i], &arr[j]);
                i++;
                j--;
            }
        }

        if (j - lo < hi - i) {
            if (lo < j)
                statdata_quicksort(arr, lo, j);
            lo = i;
        } else {
            if (i < hi)
                statdata_quicksort(arr, i, hi);
            hi = j;
        }
    }
}

static void merge_or_add(StatData *result, size_t *len_result, const StatData *src)
{
    for (size_t i = 0; i < *len_result; i++) {
        if (result[i].id == src->id) {
            result[i].count += src->count;
            result[i].cost  += src->cost;
            if (src->primary == 0)
                result[i].primary = 0;
            if (src->mode > result[i].mode)
                result[i].mode = src->mode;
            return;
        }
    }
    result[*len_result] = *src;
    (*len_result)++;
}


StatError JoinDump(const StatData *first,  size_t len_first,
                   const StatData *second, size_t len_second,
                   StatData **result,      size_t *len_result)
{
    if (result == NULL || len_result == NULL)
        return STAT_ERR_INVALID_ARG;

    if ((first == NULL && len_first > 0) ||
        (second == NULL && len_second > 0))
        return STAT_ERR_INVALID_ARG;

    size_t total_len = len_first + len_second;
    if (total_len == 0) {
        *result = NULL;
        *len_result = 0;
        return STAT_OK;
    }

    StatData *out = malloc(total_len * sizeof(StatData));
    if (out == NULL)
        return STAT_ERR_ALLOC;

    size_t out_len = 0;

    for (size_t i = 0; i < len_first; i++)
        merge_or_add(out, &out_len, &first[i]);

    for (size_t i = 0; i < len_second; i++)
        merge_or_add(out, &out_len, &second[i]);

    *result = out;
    *len_result = out_len;
    return STAT_OK;
}

StatError SortDump(StatData *data, size_t len_data) {
    if(data==NULL && len_data > 0)
        return STAT_ERR_INVALID_ARG;

    statdata_quicksort(data, 0, (long)len_data - 1);
    return STAT_OK;
}

