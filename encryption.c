/*
** EPITECH PROJECT, 2019
** 103cipher_2019
** File description:
** encryption
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int **get_key_matrix(char *key, int *dim_matrix)
{
    int nb_char = strlen(key);
    int **key_matrix;
    int i = 0;
    int t = 0;

    for (i = 1; i * i < nb_char; i++);
    key_matrix = malloc(sizeof(int *) * i);
    for (int j = 0; j < i; j++) {
        key_matrix[j] = malloc(sizeof(int) * i);
        key_matrix[j][0] = 0;
        key_matrix[j][1] = 0;
        key_matrix[j][2] = 0;
    }
    for (int y = 0; y < i; y++) {
        for (int x = 0; x < i; x++) {
            if (t < nb_char)
                key_matrix[y][x] = key[t];
            else
                key_matrix[y][x] = 0;
            t++;
        }
    }
    *dim_matrix = i;
    return key_matrix;
}

static void display_key_matrix(int **key_matrix, int dim_matrix)
{
    printf("Key matrix:\n");
    for (int i = 0; i < dim_matrix; i++) {
        for (int j = 0; j < dim_matrix; j++) {
            if (j == dim_matrix - 1)
                printf("%d", key_matrix[i][j]);
            else
                printf("%d\t", key_matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int **get_msg_matrix(char *message, int dim_matrix)
{
    int nb_line = strlen(message) / dim_matrix + strlen(message) % dim_matrix;
    int **msg_matrix = malloc(sizeof(int *) * nb_line);
    size_t t = 0;

    for (int i = 0; i < nb_line; i++)
        msg_matrix[i] = malloc(sizeof(int) * dim_matrix);
    for (int y = 0; y < nb_line; y++) {
        for (int x = 0; x < dim_matrix; x++) {
            if (t < strlen(message)) {
                msg_matrix[y][x] = message[t];
            }
            else
                msg_matrix[y][x] = 0;
            t++;
        }
    }
    return msg_matrix;
}

static void get_encrypted_matrix(char *message, int dim_matrix, int **key_matrix, int **msg_matrix)
{
    int nb_line = strlen(message) / dim_matrix + strlen(message) % dim_matrix;
    int **cpt_matrix = malloc(sizeof(int *) * nb_line);
    int len_msg = 0;

    for (int i = 0; i < nb_line; i++)
        cpt_matrix[i] = malloc(sizeof(int) * dim_matrix);
    for (int i = 0; i < nb_line; i++) {
        for (int j = 0; j < dim_matrix; j++) {
            for (int k = 0; k < dim_matrix; k++) {
                cpt_matrix[i][j] += key_matrix[k][j] * msg_matrix[i][k];
            }
        }
    }
    printf("Encrypted message:\n");
    for (int i = 0; i < nb_line; i++) {
        for (int j = 0; j < dim_matrix; j++) {
            if (cpt_matrix[i][j] != 0)
                len_msg++;
        }
    }
    for (int i = 0; i < nb_line; i++) {
        for (int j = 0; j < dim_matrix; j++) {
            if (len_msg > 1)
                printf("%d ", cpt_matrix[i][j]);
            else if (cpt_matrix[i][j] != 0)
                printf("%d", cpt_matrix[i][j]);
            len_msg--;
        }
    }
    printf("\n");
    for (int i = 0; i < nb_line; i++)
        free(cpt_matrix[i]);
    free(cpt_matrix);
    for (int i = 0; i < dim_matrix; i++) 
        free(key_matrix[i]);
    free(key_matrix);
}

void encrypted(char *key, char *message)
{
    int **key_matrix;
    int **msg_matrix;
    int dim_matrix = 0;

    key_matrix = get_key_matrix(key, &dim_matrix);
    display_key_matrix(key_matrix, dim_matrix);
    msg_matrix = get_msg_matrix(message, dim_matrix);
    get_encrypted_matrix(message, dim_matrix, key_matrix, msg_matrix);
}