/*
** EPITECH PROJECT, 2019
** 103cipher_2019
** File description:
** error_handling
*/

#include <stdbool.h>
#include <string.h>

static bool my_str_isprintable(char *str)
{
    size_t i = 0;

    while (i < strlen(str)) {
        if (str[i] < 32 || str[i] > 126)
            return false;
        i++;
    }
    return true;
}

static bool one_or_zero(char *str)
{
    if (strlen(str) != 1)
        return false;
    if (str[0] != '1' && str[0] != '0')
        return false;
    return true;
}

bool error_handling(char **str)
{
    if (!my_str_isprintable(str[1]))
        return false;
    if (!my_str_isprintable(str[2]))
        return false;
    if (!one_or_zero(str[3]))
        return false;
    return true;
}