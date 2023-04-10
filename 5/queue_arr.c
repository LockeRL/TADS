#include "queue_arr.h"

bool arr_is_empty(queue_arr *a)
{
    return a->len == 0;
}

bool arr_is_full(queue_arr *a)
{
    return a->len >= QUEUE_SIZE;
}

bool push_arr_new(queue_arr *a)
{
    if (arr_is_full(a))
        return 0;
    a->len++;
    a->in_num++;
    if (a->len == 1)
        return 1;
    a->head--;
    a->head = a->head < 0 ? QUEUE_SIZE - a->head : a->head;
    return 1;
}

void push_arr_old(queue_arr *a)
{
    if (a->len == 1)
        return;
    a->tail--;
    a->tail = a->tail < 0 ? QUEUE_SIZE - a->tail : a->tail;
    a->head--;
    a->head = a->head < 0 ? QUEUE_SIZE - a->head : a->head;
}

void pop_arr(queue_arr *a)
{
    a->len--;
    a->out_num++;
    if (arr_is_empty(a))
        return;
    a->tail--;
    a->tail = a->tail < 0 ? QUEUE_SIZE - a->tail : a->tail;
}

void print_arr_addresses(queue_arr *a)
{
    printf("In: %d Out: %d\n", a->in_num, a->out_num);
    printf("Addresses: ");
    for (int i = a->head; i < a->head + a->len; i++)
        printf("%p ", &a->arr[i % QUEUE_SIZE]);
    printf("\n");
}

void simulate_arr(data *data, int code, bool flag)
{
    queue_arr a;
    a.len = 0;
    a.head = 0;
    a.tail = 0;
    a.out_num = 0;
    a.in_num = 0;
    data->overflow = false;

    double time_in = 0.0, time_oa;
    double time_work = 0.0, time_stay = 0.0;
    int oa_count = 0;

    double queue_len = 0.0;

    bool print_flag = true;
    while (a.out_num < 1000)
    {
        if (flag && print_flag && a.out_num % 100 == 0 && a.out_num > 0)
        {
            printf("%d out:\n", a.out_num);
            printf("Queue len: %d\n", a.len);
            printf("Average len: %lf\n\n", queue_len / oa_count);
            print_flag = false;
        }

        if (!(time_in > 0.0))
        {
            if (arr_is_full(&a))
            {
                if (flag)
                    printf("The queue is overwlowed\n\n");
                data->overflow = true;
                break;
            }
            else
            {
                push_arr_new(&a);
                if (code && a.len < 10)
                    print_arr_addresses(&a);
                time_in += gen_time(IN_BEG, IN_END);
                if (a.in_num == 1)
                    time_stay += time_in;
            }
        }
        else
        {
            if (arr_is_empty(&a)) {
                time_stay += time_in;
                time_in = 0;
            } else {
                time_oa = gen_time(OA_BEG, OA_END);
                time_work += time_oa;
                int pass = rand() % 10;
                if (pass > 7) {
                    pop_arr(&a);
                    print_flag = true;
                    if (code && a.len < 10)
                        print_arr_addresses(&a);
                } else
                    push_arr_old(&a);
                time_in -= time_oa;
                oa_count++;
                queue_len += a.len;
            }
        }
    }

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
    data->max = QUEUE_SIZE;
}

void simulate_arr_and_print()
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
    simulate_arr(&a, code, true);

    printf("Data:\n");
    printf("Model time: %lf\nTime work: %lf\nStay time: %lf\n", a.time_work + a.time_stay, a.time_work, a.time_stay);
    printf("In: %d\nOut: %d\nOA_work: %d\n\n", a.in_num, a.out_num, a.oa_count);

    if (a.overflow)
        printf("There is no check data, array was overflowed\n");
    else
    {
        printf("Check:\n");
        int expect_oa = (OA_END + OA_BEG) * 2500;
        int expect_in = (IN_END - IN_BEG) * 500;
        printf("Expected work time: %d, factically work_time: %lf, error rate: %lf %%\n",
               expect_oa, a.time_work, fabs(expect_oa - a.time_work) * 100 / expect_oa);
        printf("Expected model time: %d, factically model time: %lf, error rate: %lf %%\n",
               expect_oa > expect_in ? expect_oa : expect_in, a.time_stay + a.time_work,
               fabs(a.time_stay + a.time_work - (expect_oa > expect_in ? expect_oa : expect_in)) * 100 / (expect_oa > expect_in ? expect_oa : expect_in));
    }
}
