#include "struct.h"

int check_double_mantissa(my_double *a, int *add_power, const char *s)
{
    size_t dot_pos = 0;
    int dot_count = 0;
    size_t end_pos = 0;
    for (size_t i = 1; s[i] != 'E' || s[i] != '\0'; i++)
    {
        if (s[i] == '.')
        {
            dot_pos = i;
            dot_count++;
            continue;
        }
        if (s[i] == ' ')
        {
            end_pos = i;
            break;
        }

        if (s[i] > '9' || s[i] < '0')
            return -1;
    }

    if (dot_count > 1 || end_pos == 0 || end_pos > 32)
        return -1;

    if (dot_pos == 0)
        dot_pos = end_pos;

    // get add power
    int is_dot = 0;
    bool not_zeros = false;

    for (size_t i = 1; i < end_pos; i++)
    {
        if (i == dot_pos)
        {
            is_dot = 1;
            continue;
        }
        *add_power = dot_pos - i + is_dot;
        if (s[i] != '0')
        {
            not_zeros = true;
            break;
        }
    }

    if (!not_zeros)
        return 1;

    unsigned short mantissa_len = end_pos - dot_pos + *add_power - dot_count;

    if (mantissa_len > ARR_LEN)
        return -1;

    a->mantissa_len = mantissa_len;

    size_t j = end_pos - 1;
    for (int i = ARR_LEN - 1; i >= 0; i--)
    {
        if (i < ARR_LEN - mantissa_len)
            a->mantissa[i] = 0;
        else
        {
            if (s[j] == '.')
                j--;

            if (s[j] >= '0' && s[j] <= '9')
            {
                a->mantissa[i] = s[j] - '0';
                j--;
            }
            else
                return -1;
        }
    }

    return 0;
}

int check_int_mantissa(my_int *a, const char *s)
{
    int mantissa_len = strlen(s) - 1;
    if (mantissa_len > ARR_LEN)
        return -1;

    a->mantissa_len = mantissa_len;

    size_t j = mantissa_len;
    bool only_zeros = true;
    for (int i = ARR_LEN - 1; i >= 0; i--)
    {
        if (i < ARR_LEN - mantissa_len)
            a->mantissa[i] = 0;
        else
        {
            if (s[j] >= '0' && s[j] <= '9')
            {
                if (s[j] != '0')
                    only_zeros = false;
                a->mantissa[i] = s[j] - '0';
                j--;
            }
            else
                return -1;
        }
    }

    if (only_zeros)
        return 1;

    return 0;
}

bool check_double_power(my_double *a, const char *s, int add_power)
{
    int sign;
    size_t e_pos = 0;
    size_t power_len = strlen(s);
    for (size_t i = 0; s[i] != '\0'; i++)
    {
        if (s[i] == 'E')
        {
            e_pos = i;
            break;
        }
    }

    if (e_pos == 0)
        return false;

    if (power_len - e_pos - 3 <= 0 || power_len - e_pos - 3 >= 6)
        return false;

    if (s[e_pos + 1] != ' ')
        return false;

    if (s[e_pos + 2] == '-')
        sign = -1;
    else if (s[e_pos + 2] == '+')
        sign = 1;
    else
        return false;

    int power = 0;
    for (size_t i = e_pos + 3; s[i] != '\0'; i++)
    {
        if (s[i] >= '0' && s[i] <= '9')
            power = power * 10 + (s[i] - '0');
        else
            return false;
    }

    power *= sign;
    power += add_power;

    a->power = power;

    return true;
}

bool check_double_sign(my_double *a, const char *s)
{
    if (s[0] == '+')
    {
        a->sign = plus;
        return true;
    }
    if (s[0] == '-')
    {
        a->sign = minus;
        return true;
    }
    return false;
}

bool check_int_sign(my_int *a, const char *s)
{
    if (s[0] == '+')
    {
        a->sign = plus;
        return true;
    }
    if (s[0] == '-')
    {
        a->sign = minus;
        return true;
    }
    return false;
}

int get_double(my_double *a, const char *s)
{
    int add_power = 0;
    if (!check_double_sign(a, s))
        return -1;
    int code = check_double_mantissa(a,&add_power, s);
    if (code == -1)
        return -1;
    if (!check_double_power(a, s, add_power))
        return -1;
    return code;
}

int get_int(my_int *a, const char *s)
{
    if (!check_int_sign(a, s))
        return -1;
    int code = check_int_mantissa(a, s);
    if (code == -1)
        return -1;
    return code;
}

void count(const my_double *a, const my_int *b, my_double *answer)
{
    unsigned short ans[2 * ARR_LEN];
    for (size_t i = 0; i < 2 * ARR_LEN; i++)
        ans[i] = 0;

    int prod;
    int cur;
    for (size_t i = 0; i < b->mantissa_len; i++)
        for (size_t j = 0; j < a->mantissa_len; j++)
        {
            prod = b->mantissa[ARR_LEN - 1 - i] * a->mantissa[ARR_LEN - 1 - j];
            cur = ans[2 * ARR_LEN - 1 - i - j] + prod;
            ans[2 * ARR_LEN - 1 - i - j] = cur % 10;
            ans[2 * ARR_LEN - 1 - i - j - 1] += cur / 10;
        }

    // sign
    if (a->sign == b->sign)
        answer->sign = plus;
    else
        answer->sign = minus;

    // power
    size_t start = 0;
    for (size_t i = 0; i < 2 * ARR_LEN; i++)
        if (ans[i] != 0)
        {
            start = i;
            break;
        }
    int new_len = 2 * ARR_LEN - start;
    answer->power = a->power + new_len - a->mantissa_len;

    // mantissa
    // округление
    if (start < 30)
    {
        if (ans[start + ARR_LEN] >= 5)
            ans[start + ARR_LEN - 1]++;
        for (size_t i = 0; i < ARR_LEN; i++)
            if (ans[start + ARR_LEN - i - 1] == 10)
            {
                ans[start + ARR_LEN - i - 1] = 0;
                ans[start + ARR_LEN - i - 2]++;
            }
    }
    answer->mantissa_len = 0;
    for (size_t i = 0; i < ARR_LEN; i++)
    {
        if (start + i < 2 * ARR_LEN)
        {
            answer->mantissa[i] = ans[start + i];
            answer->mantissa_len++;
        }
    }

    new_len = answer->mantissa_len;
    for (size_t i = new_len - 1; answer->mantissa[i] == 0; i--)
        answer->mantissa_len--;

}

bool print_new_double(const my_double *a)
{
    if (a->power >= 100000 || a->power <= -100000)
        return false;
    printf("Произведение: ");
    if (a->sign == 1)
        printf("+");
    else
        printf("-");

    printf("0.");
    for (size_t i = 0; i < a->mantissa_len; i++)
        printf("%hu", a->mantissa[i]);

    printf(" E ");
    if (a->power >= 0)
        printf("+");
    printf("%d\n", a->power);

    return true;
}

