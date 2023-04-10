#include "file_work.h"

static_arr read_words(FILE *f)
{
    static_arr a;
    a.arr = NULL;
    a.len = 0;
    char word[30];
    while (fscanf(f, "%s", word) == 1)
    {
        a.len++;
        a.arr = realloc(a.arr, a.len * sizeof(a.arr[0]));
        a.arr[a.len - 1] = strdup(word);
    }
    return a;
}