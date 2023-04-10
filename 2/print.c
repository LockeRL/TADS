#include "print.h"

void print_theatre(theatre *a);

void print_line(void)
{
    for (int i = 0; i < 125; i++)
        printf("-");
    printf("\n");
}

void print_table(theatre a[], int n)
{
    print_line();
    printf("|%-20s|%-20s|%-20s|%-10s|%-10s|%-7s|%-30s|\n", "Theatre", "Show", "Director", "Min price", "Max price", "Type", "Variative");
    print_line();
    print_line();

    for (int i = 0; i < n; i++)
    {
        print_theatre(&a[i]);
        print_line();
    }
}

void print_data_table(void)
{
    FILE *f = fopen("data.csv", "r");
    theatre arr[ARR_MAX_LEN];
    int n = 0;
    while (read_theatre(&arr[n], f) == 0)
        n++;
    fclose(f);

    print_table(arr, n);
}

void print_menu(void)
{
    printf("\nКоманды:\n"
           "1) Вывести исходную таблицу\n"
           "2) Добавить запись в конец таблицы\n"
           "3) Удалить запись по названию спектакля\n"
           "4) Вывести таблицу ключей\n"
           "5) Отсортировать по минимальной цене билета\n"
           "6) Вывести список музыкальных спектаклей для детей указанного возраста с продолжительностью меньше указанной\n"
           "7) Вывести сортируемую таблицу\n"
           "8) Сравнение эффективности при работе с исходной таблицей и с таблицей ключей\n"
           "9) Сравнение эффективности сортировок\n"
           "10) Вывод по таблице ключей\n"
           "11) Выйти\n");
}

void print_main(theatre *a)
{
    printf("|%-20s|%-20s|%-20s|%-10d|%-10d|", a->name, a->show, a->director,
           a->min_ticket_price, a->max_ticket_price);
    switch (a->show_kind) {
        case CHILD:
            printf("%-7s|", "CHILD");
            break;
        case ADULT:
            printf("%-7s|", "ADULT");
            break;
        case MUSICAL:
            printf("%-7s|", "MUSICAL");
            break;
    }
}

void print_adult(theatre *a)
{
    switch (a->kind.adult.type) {
        case PLAY:
            printf("%-30s|\n", "Type: PLAY");
            break;
        case DRAMA:
            printf("%-30s|\n", "Type: DRAMA");
            break;
        case COMEDY:
            printf("%-30s|\n", "Type: COMEDY");
            break;
    }
}

void print_child(theatre *a)
{
    printf("Min age: %-21d|\n", a->kind.child.min_age);
    switch (a->kind.child.type) {
        case FAIRY_TAIL:
            printf("|%-20s|%-20s|%-20s|%-10s|%-10s|%-7s|%-30s|\n", "", "", "", "", "", "", "Type: FAIRY_TAIL");
            break;
        case PLAY:
            printf("|%-20s|%-20s|%-20s|%-10s|%-10s|%-7s|%-30s|\n", "", "", "", "", "", "", "Type: PLAY");
            break;
    }
}

void print_musical(theatre *a)
{
    printf("Composer: %-20s|\n", a->kind.musical.composer);
    printf("|%-20s|%-20s|%-20s|%-10s|%-10s|%-7s|Country: %-21s|\n", "", "", "", "", "", "", a->kind.musical.country);
    printf("|%-20s|%-20s|%-20s|%-10s|%-10s|%-7s|Min age: %-21d|\n", "", "", "", "", "", "", a->kind.musical.min_age);
    printf("|%-20s|%-20s|%-20s|%-10s|%-10s|%-7s|Duration: %-20d|\n", "", "", "", "", "", "", a->kind.musical.duration);
}

void print_theatre(theatre *a)
{
    print_main(a);
    switch (a->show_kind) {
        case CHILD:
            print_child(a);
            break;
        case ADULT:
            print_adult(a);
            break;
        case MUSICAL:
            print_musical(a);
            break;
    }
}

void print_musical_by_age_duration(theatre arr[], int n, int age, int duration)
{
    print_line();
    printf("|%-20s|%-20s|%-20s|%-10s|%-10s|%-7s|%-30s|\n", "Theatre", "Show", "Director", "Min price", "Max price", "Type", "Variative");
    print_line();
    print_line();

    for (int i = 0; i < n; i++)
        if (arr[i].show_kind == MUSICAL && arr[i].kind.musical.min_age <= age && arr[i].kind.musical.duration <= duration)
        {
            print_theatre(&arr[i]);
            print_line();
        }
}

void print_key_table(key a[], int n)
{
    printf("------------------\n");
    printf("|%-5s|%-10s|\n", "Index", "Price");
    printf("------------------\n");
    printf("------------------\n");

    for (int i = 0; i < n; i++)
    {
        printf("|%-5d|%-10d|\n", a[i].index, a[i].price);
        printf("------------------\n");
    }
}

void print_by_key(key b[])
{
        print_line();
    printf("|%-20s|%-20s|%-20s|%-10s|%-10s|%-7s|%-30s|\n", "Theatre", "Show", "Director", "Min price", "Max price", "Type", "Variative");
    print_line();
    print_line();
    
        FILE *f = fopen("data.csv", "r");
    theatre arr[ARR_MAX_LEN];
    int n = 0;
    while (read_theatre(&arr[n], f) == 0)
        n++;
    fclose(f);

    for (int i = 0; i < n; i++)
    {
        print_theatre(&arr[b[i].index]);
        print_line();
    }
}
