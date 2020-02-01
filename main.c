/*
** EPITECH PROJECT, 2019
** 103cipher_2019
** File description:
** main
*/

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "error_handling.h"
#include "encryption.h"
#include "decryption.h"

size_t usage(int exit_status)
{
    printf("USAGE\n");
    printf("    ./103cipher message key flag\n\n");
    printf("DESCRIPTION\n");
    printf("    message     a message, made of ASCII characters\n");
    printf("    key         the encryption key, made of ASCII characters\n");
    printf("    flag        0 for the message to be encrypted, 1 to be decrypted\n");
    return exit_status;
}

int main(int ac, char **av)
{
    if (ac < 2)
        return 84;
    if (av[1][0] == '-' && av[1][1] == 'h')
        return usage(0);
    if (ac != 4)
        return 84;
    if (!error_handling(av))
        return 84;
    if (av[3][0] == '0')
        encrypted(av[2], av[1]);
    if (av[3][0] == '1')
        decrypted(av[2], av[1]);
    return 0;
}