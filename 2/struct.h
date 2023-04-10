#ifndef STRUCT_H
#define STRUCT_H

#define ARR_MAX_LEN 1024

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef enum {CHILD, ADULT, MUSICAL} show_kind; // 1 2 3
typedef enum {FAIRY_TAIL, PLAY, DRAMA, COMEDY} type; // 1 2 3 4

typedef struct
{
    int min_age;
    type type;
} child;

typedef struct
{
    type type;
} adult;

typedef struct
{
    char composer[21];
    char country[21];
    int min_age;
    int duration;
} musical;

// name show director 10 20 [1-3] ...
typedef struct
{
    char name[21];
    char show[21];
    char director[21];
    int min_ticket_price;
    int max_ticket_price;
    show_kind show_kind;
    union
    {
        child child; // 1
        adult adult; // 2
        musical musical; // 3
    } kind;
} theatre;

typedef struct
{
    int index;
    int price;
} key;

#endif // STRUCT_H