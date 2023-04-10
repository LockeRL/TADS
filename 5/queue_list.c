#include "queue_list.h"

bool list_is_empty(queue_list *a)
{
    return a->len == 0;
}

bool push_list_new(queue_list *a)
{
    queue_cell *buf = malloc(sizeof(queue_cell));
    buf->prev = NULL;
    if (list_is_empty(a))
    {
        a->tail = buf;
        a->head = buf;
    }
    else
        a->head->prev = buf;
    a->head = buf;
    a->in_num++;
    a->len++;
    return 1;
}

void pop_list(queue_list *a)
{
    a->len--;
    a->out_num++;
    if (list_is_empty(a))
    {
        free(a->tail);
        a->tail = NULL;
        a->head = NULL;
        return;
    }
    queue_cell *tmp = a->tail->prev;
    free(a->tail);
    a->tail = tmp;
}

void push_list_old(queue_list *a)
{
    if (a->tail == a->head)
        return;
    if (a->len == 2)
    {
        a->tail->prev = NULL;
        a->head->prev = a->tail;
        a->tail = a->head;
        a->head = a->head->prev;
    }
    else
    {
        a->head->prev = a->tail;
        a->head = a->tail;
        a->tail = a->tail->prev;
        a->head->prev = NULL;
        
    }
}

void free_list(queue_list *a)
{
    queue_cell *tmp = NULL;
    for (; a->tail; a->tail = tmp)
    {
        tmp = a->tail->prev;
        free(a->tail);
    }
}

void print_list_addresses(queue_list *a)
{
    printf("In: %d Out: %d\n", a->in_num, a->out_num);
    printf("Addresses: ");
    queue_cell *tmp = a->tail;
    for (; tmp; tmp = tmp->prev)
        printf("%p ", (void*)tmp);
    printf("\n");
}

void simulate_list(data *data, int code, bool flag)
{
    queue_list a;
    a.len = 0;
    a.head = NULL;
    a.tail = NULL;
    a.out_num = 0;
    a.in_num = 0;
    a.max_len = 0;

    double time_in = 0.0, time_oa;
    double time_work = 0.0, time_stay = 0.0;
    int oa_count = 0;

    double queue_len = 0.0;

    bool print_flag = true;
    while (a.out_num < 1000)
    {
        a.max_len = a.len > a.max_len ? a.len : a.max_len;
        
        if (flag && print_flag && a.out_num % 100 == 0 && a.out_num > 0)
        {
            printf("%d out:\n", a.out_num);
            printf("Queue len: %d\n", a.len);
            printf("Average len: %lf\n\n", queue_len / oa_count);
            print_flag = false;
        }

        if (!(time_in > 0.0)) // time_in <= 0
        {
            push_list_new(&a);
            if (code && a.len < 10)
                print_list_addresses(&a);
            time_in += gen_time(IN_BEG, IN_END);
            if (a.in_num == 1)
                time_stay += time_in;
        }
        else
        {
            if (list_is_empty(&a)) {
                time_stay += time_in;
                time_in = 0;
            }
            else
            {
                time_oa = gen_time(OA_BEG, OA_END);
                time_work += time_oa;
                int pass = rand() % 10;
                if (pass > 7) {
                    pop_list(&a);
                    print_flag = true;
                    if (code && a.len < 10)
                        print_list_addresses(&a);
                } else
                    push_list_old(&a);
                time_in -= time_oa;
                oa_count++;
                queue_len += a.len;
            }
        }
    }
    free_list(&a);
    
    
    if (flag && print_flag && a.out_num % 100 == 0 && a.out_num > 0)
    {
        printf("%d out:\n", a.out_num);
        printf("Queue len: %d\n", a.len);
        printf("Average len: %lf\n\n", queue_len / oa_count);
    }
    

    data->in_num = a.in_num;
    data->out_num = a.out_num;
    data->oa_count = oa_count;
    data->time_work = time_work;
    data->time_stay = time_stay;
    data->max = a.max_len;
}

void simulate_list_and_print()
{
    int code;
    printf("На экран будут выводиться адреса, пока длина очереди <10\n");
    while (1)
    {
        printf("Введите 1, если хотите посмотреть адреса элементов очереди или 0 в противном случае: ");
        if (scanf("%d", &code) != 1 || code < 0 || code > 1)
        {
            printf("Некорректный ввод!\n");
            char cache[100];
            scanf("%s", cache);
        }
        else
            break;
    }
    char b;
    b = getchar();

    data a;
    simulate_list(&a, code, true);

    printf("Data:\n");
    printf("Model time: %lf\nTime work: %lf\nStay time: %lf\n", a.time_work + a.time_stay, a.time_work, a.time_stay);
    printf("In: %d\nOut: %d\nOA_work: %d\n\n", a.in_num, a.out_num, a.oa_count);
    printf("Check:\n");
    int expect_oa = (OA_END + OA_BEG) * 2500;
    int expect_in = (IN_END - IN_BEG) * 500;
    printf("Expected work time: %d, factically work_time: %lf, error rate: %lf %%\n",
           expect_oa, a.time_work, fabs(expect_oa - a.time_work) * 100 / expect_oa);
    printf("Expected model time: %d, factically model time: %lf, error rate: %lf %%\n",
           expect_oa > expect_in ? expect_oa : expect_in, a.time_stay + a.time_work,
           fabs(a.time_stay + a.time_work - (expect_oa > expect_in ? expect_oa : expect_in)) * 100 / (expect_oa > expect_in ? expect_oa : expect_in));
}
