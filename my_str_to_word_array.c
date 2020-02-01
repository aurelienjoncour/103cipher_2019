/*
** EPITECH PROJECT, 2019
** my_str_word_array
** File description:
** split a string into words
*/

#include <stdlib.h>
#include <string.h>

int my_char_is_alpha(char c)
{
    if (c >= '0' && c <= '9')
        return (1);
    if (c >= 'a' && c <= 'z')
        return (1);
    if (c >= 'A' && c <= 'Z')
        return (1);
    else
        return (0);
}

int my_wordlen(char const *str, int j)
{
    int wordlen = 0;

    while (my_char_is_alpha(str[j])) {
        j++;
        wordlen++;
    }
    return (wordlen);
}

char **my_str_to_word_array(char const *str)
{
    int nb_words = 0;
    char **tab_words;
    int j = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (my_char_is_alpha(str[i]) && !my_char_is_alpha(str[i + 1]))
            nb_words++;
    }
    tab_words = malloc(sizeof(char *) * (nb_words + 1));
    for (int i = 0; i < nb_words; i++) {
        while (!my_char_is_alpha(str[j]))
            j++;
        tab_words[i] = malloc(sizeof(char) * (my_wordlen(str, j) + 1));
        strncpy(tab_words[i], &str[j], my_wordlen(str, j));
        tab_words[i][my_wordlen(str, j)] = '\0';
        j += my_wordlen(str, j);
    }
    tab_words[nb_words] = 0;
    return (tab_words);
}
