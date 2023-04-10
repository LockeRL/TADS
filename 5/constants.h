#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <stdbool.h>

#define QUEUE_SIZE 1000

#define OA_BEG 0
#define OA_END 12

#define IN_BEG 0
#define IN_END 1

typedef struct
{
    double time_work;
    double time_stay;
    int in_num;
    int out_num;
    int oa_count;
    int max;
    bool overflow;
} data;

#endif // CONSTANTS_H
