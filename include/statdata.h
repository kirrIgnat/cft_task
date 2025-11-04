#ifndef STATDATA_H
#define STATDATA_H

/*
 * хедер StatData -->
 *   сериализация/десериализация StoreDump / LoadDump
 *   объединение массивов JoinDump
 *   сортировка по cost SortDump
 *   печать таблицы PrintTable
 *
 *  хедер в роли фасада юзеру  не нужно знать как работают модули core/io/util
 */

#include <stddef.h>



typedef struct StatData { 
   long  id; 
   int   count; 
   float cost; 
   unsigned int primary:1; 
   unsigned int mode:3; 
} StatData; 
/*
 *   STAT_OK все ок
 *   STAT_ERR_IO ошибка ввода вывода
 *   STAT_ERR_ALLOC ошибка выделения памяти
 *   STAT_ERR_FORMAT ошбка или повреждённый формат
 *   STAT_ERR_INVALID_ARG ошибка в аргументах
 *   STAT_ERR_INTERNAL
 */
typedef enum StatError {
    STAT_OK = 0,
    STAT_ERR_IO,
    STAT_ERR_ALLOC,
    STAT_ERR_FORMAT,
    STAT_ERR_INVALID_ARG,
    STAT_ERR_INTERNAL
} StatError;
#endif 
