#include "read.h"

int put_main(theatre *a, const char *name, const char *show,
              const char *director, int min_price,
              int max_price, int type)
{
    if (strlen(name) >= 20)
        return 1;
    strcpy(a->name, name); // name
    if (strlen(show) >= 20)
        return 1;
    strcpy(a->show, show); // show
    if (strlen(director) >= 20)
        return 1;
    strcpy(a->director, director); // director
    if (min_price <= 0)
        return 1;
    a->min_ticket_price = min_price; // min_price
    if (max_price < min_price)
        return 1;
    a->max_ticket_price = max_price; // max_price
    switch (type) {
        case 1:
            a->show_kind = CHILD;
            break;
        case 2:
            a->show_kind = ADULT;
            break;
        case 3:
            a->show_kind = MUSICAL;
            break;
        default:
            return 1;
    }
    return 0;
}

int put_child(theatre *a, int age, int type)
{
    if (age <= 0)
        return 1;
    a->kind.child.min_age = age;
    switch (type) {
        case 1:
            a->kind.child.type = FAIRY_TAIL;
            break;
        case 2:
            a->kind.child.type = PLAY;
            break;
        default:
            return 1;
    }
    return 0;
}

int put_adult(theatre *a, int type)
{
    switch (type) {
        case 2:
            a->kind.adult.type = PLAY;
            break;
        case 3:
            a->kind.adult.type = DRAMA;
            break;
        case 4:
            a->kind.adult.type = COMEDY;
            break;
        default:
            return 1;
    }
    return 0;
}

int put_musical(theatre *a, const char *composer, const char *country,
                 int age, int duration)
{
    if (strlen(composer) >= 20)
        return 1;
    strcpy(a->kind.musical.composer, composer);
    if (strlen(country) >= 20)
        return 1;
    strcpy(a->kind.musical.country, country);
    if (age <= 0)
        return 1;
    a->kind.musical.min_age = age;
    if (duration <= 0)
        return 1;
    a->kind.musical.duration = duration;
    return 0;
}

int read_theatre(theatre *a, FILE *f)
{
    char s[1024];
    if (!fgets(s, sizeof(s), f) || s[0] == '\n')
        return 1;
    char *data[10];
    char *pword = strtok(s, " \n");
    int field = 0;
    while (pword)
    {
        data[field] = pword;
        field++;
        pword = strtok(NULL, " \n");
    }

    if (field < 6)
        return 1;

    int return_code = put_main(a, data[0], data[1], data[2], atoi(data[3]), atoi(data[4]), data[5][0] - '0');

    if (a->show_kind == CHILD)
    {
        if (field < 8)
            return 1;
        return_code += put_child(a, atoi(data[6]), data[7][0] - '0');

    }
    else if (a->show_kind == MUSICAL)
    {
        if (field < 10)
            return 1;
        return_code += put_musical(a, data[6], data[7], atoi(data[8]), atoi(data[9]));

    }
    else
    {
        if (field < 7)
            return 1;
        return_code += put_adult(a, data[6][0] - '0');

    }

    return return_code;
}

int read_theatre_stdin(theatre *a)
{
    char s[100];
    char cache[100];
    printf("Введите название театра не более 20 символов: ");
    if (scanf("%s", s) != 1 || strlen(s) > 20)
    {
        printf("Некорректный ввод\n");
        return -1;
    }
    strcpy(a->name, s);

    printf("Введите название спектакля не более 20 символов: ");
    if (scanf("%s", s) != 1 || strlen(s) > 20)
    {
        printf("Некорректный ввод\n");
        return -1;
    }
    strcpy(a->show, s);

    printf("Введите режиссера не более 20 символов: ");
    if (scanf("%s", s) != 1 || strlen(s) > 20)
    {
        printf("Некорректный ввод\n");
        return -1;
    }
    strcpy(a->director, s);

    int price;
    printf("Введите минимальную цену билета: ");
    if (scanf("%d", &price) != 1 || price < 0)
    {
        printf("Некорректный ввод\n");
        scanf("%s", cache);
        return -1;
    }
    a->min_ticket_price = price;

    printf("Введите максимальную цену билета: ");
    if (scanf("%d", &price) != 1 || price < 0)
    {
        printf("Некорректный ввод\n");
        scanf("%s", cache);
        return -1;
    }
    a->max_ticket_price = price;

    int buf;
    printf("Введите 1, если это детский спектакль, 2 - для взрослых, 3 - мюзикл: ");
    if (scanf("%d", &buf) != 1 || buf < 1 || buf > 3)
    {
        printf("Некорректный ввод\n");
        return -1;
    }
    switch (buf) {
        case 1:
            a->show_kind = CHILD;
            break;
        case 2:
            a->show_kind = ADULT;
            break;
        case 3:
            a->show_kind = MUSICAL;
            break;
    }

    if (buf == 1)
    {
        int age;
        printf("Введите минимальный возраст: ");
        if (scanf("%d", &age) != 1 || age < 0)
        {
            printf("Некорректный ввод\n");
            scanf("%s", cache);
            return -1;
        }
        a->kind.child.min_age = age;

        printf("Введите 1, если это сказка, 2 - пьеса: ");
        if (scanf("%d", &buf) != 1 || buf < 1 || buf > 2)
        {
            printf("Некорректный ввод\n");
            return -1;
        }
        switch (buf) {
            case 1:
                a->kind.child.type = FAIRY_TAIL;
                break;
            case 2:
                a->kind.child.type = PLAY;
                break;
        }
    }
    else if (buf == 2)
    {
        printf("Введите 1, если это пьеса, 2 - драма, 3 - комедия: ");
        if (scanf("%d", &buf) != 1 || buf < 1 || buf > 3)
        {
            printf("Некорректный ввод\n");
            return -1;
        }
        switch (buf) {
            case 1:
                a->kind.adult.type = PLAY;
                break;
            case 2:
                a->kind.adult.type = DRAMA;
                break;
            case 3:
                a->kind.adult.type = COMEDY;
                break;
        }
    }
    else
    {
        char s[100];
        printf("Введите композитора не более 20 символов: ");
        if (scanf("%s", s) != 1 || strlen(s) > 20)
        {
            printf("Некорректный ввод\n");
            return -1;
        }
        strcpy(a->kind.musical.composer, s);

        printf("Введите страну не более 20 символов: ");
        if (scanf("%s", s) != 1 || strlen(s) > 20)
        {
            printf("Некорректный ввод\n");
            return -1;
        }
        strcpy(a->kind.musical.country, s);

        int age;
        printf("Введите возраст: ");
        if (scanf("%d", &age) != 1 || age < 0)
        {
            printf("Некорректный ввод\n");
            scanf("%s", cache);
            return -1;
        }
        a->kind.musical.min_age = age;

        int duration;
        printf("Введите длительность: ");
        if (scanf("%d", &duration) != 1 || duration <= 0)
        {
            printf("Некорректный ввод\n");
            scanf("%s", cache);
            return -1;
        }
        a->kind.musical.duration = duration;
    }
    return 0;
}
