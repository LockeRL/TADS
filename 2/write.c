#include "write.h"

void file_write(theatre *a, int n)
{
    FILE *f = fopen("out.txt", "w");
    if (f == NULL)
        return;

    for (int i = 0; i < n; i++)
    {
        fprintf(f, "%s %s %s %d %d %d ", a[i].name, a[i].show, a[i].director, a[i].min_ticket_price, a[i].max_ticket_price, a[i].show_kind + 1);
        switch (a[i].show_kind) {
            case CHILD:
                fprintf(f, "%d %d\n", a[i].kind.child.min_age, a[i].kind.child.type + 1);
                break;
            case ADULT:
                fprintf(f, "%d\n", a[i].kind.adult.type + 1);
                break;
            case MUSICAL:
                fprintf(f, "%s %s %d %d\n", a[i].kind.musical.composer, a[i].kind.musical.country, a[i].kind.musical.min_age, a[i].kind.musical.duration);
        }
    }
}