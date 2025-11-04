#include "statdata.h"
#include <stdlib.h>

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

StatError JoinDump(const StatData *first, size_t len_first, const StatData *second, size_t len_second, StatData **result, size_t *len_result){

}

StatError SortDump(StatData *data, size_t len_data) {
    if(data==NULL || len_data < 2)
        return STAT_ERR_INVALID_ARG;

    statdata_quicksort(data, 0, (long)len_data - 1);

}

