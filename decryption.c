/*
** EPITECH PROJECT, 2019
** 103cipher_2019
** File description:
** decryption
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "encryption.h"

char **my_str_to_word_array(char const *str);

static void my_swap(int *a, int *b)
{
    int tmp = *a;

    *a = *b;
    *b = tmp;
}

static int determinant_key_matrix_2(int **matrix)
{
    int determinant = 0;

    determinant = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    return determinant;
}

static int determinant_key_matrix_3(int **matrix)
{
    int determinant = 0;
    int determinant_1 = 0;
    int determinant_2 = 0;
    int determinant_3 = 0;
    
    determinant_1 = matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1];
    determinant_2 = matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0];
    determinant_3 = matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0];
    determinant = matrix[0][0] * determinant_1 - matrix[0][1] * determinant_2 + matrix[0][2] * determinant_3;

    return determinant;
}

static int determinant(int dim_matrix, int **key_matrix)
{
    int determinant = 0;
    
    if (dim_matrix == 1)
        determinant = key_matrix[0][0] / key_matrix[0][0];
    if (dim_matrix == 2)
        determinant = determinant_key_matrix_2(key_matrix);
    if (dim_matrix == 3)
        determinant = determinant_key_matrix_3(key_matrix);
    if (determinant == 0)
        exit (84);
    return determinant;
}

int **get_commatrix(int dim_matrix, int **key_matrix)
{
    int **commatrice = malloc(sizeof(int *) * dim_matrix);
    
    for (int i = 0; i < dim_matrix; i++)
        commatrice[i] = malloc(sizeof(int) * dim_matrix);
    if (dim_matrix == 1)
        commatrice[0][0] = key_matrix[0][0];
    else if (dim_matrix == 2) {
        commatrice[0][0] = key_matrix[1][1];
        commatrice[0][1] = key_matrix[0][1] * - 1;
        commatrice[1][0] = key_matrix[1][0] * - 1;
        commatrice[1][1] = key_matrix[0][0];
    }
    else if (dim_matrix == 3) {
        commatrice[0][0] = key_matrix[1][1] * key_matrix[2][2] - key_matrix[1][2] * key_matrix[2][1];
        commatrice[0][1] = -1 * (key_matrix[1][0] * key_matrix[2][2] - key_matrix[1][2] * key_matrix[2][0]);
        commatrice[0][2] = key_matrix[1][0] * key_matrix[2][1] - key_matrix[2][0] * key_matrix[1][1];
        commatrice[1][0] = -1 * (key_matrix[0][1] * key_matrix[2][2] - key_matrix[2][1] * key_matrix[0][2]);
        commatrice[1][1] = key_matrix[0][0] * key_matrix[2][2] - key_matrix[2][0] * key_matrix[0][2];
        commatrice[1][2] = -1 * (key_matrix[0][0] * key_matrix[2][1] - key_matrix[2][0] * key_matrix[0][1]);
        commatrice[2][0] = key_matrix[0][1] * key_matrix[1][2] - key_matrix[1][1] * key_matrix[0][2];
        commatrice[2][1] = -1 * (key_matrix[0][0] * key_matrix[1][2] - key_matrix[1][0] * key_matrix[0][2]);
        commatrice[2][2] = key_matrix[0][0] * key_matrix[1][1] - key_matrix[1][0] * key_matrix[0][1];
        my_swap(&commatrice[0][1], &commatrice[1][0]);
        my_swap(&commatrice[1][2], &commatrice[2][1]);
        my_swap(&commatrice[0][2], &commatrice[2][0]);
    }
    return commatrice;
}

float **get_inversed_matrix(int **matrix, int determinant, int dim_matrix)
{
    float **inversed_matrix = malloc(sizeof(float *) * dim_matrix);

    for (int i = 0; i < dim_matrix; i++)
        inversed_matrix[i] = malloc(sizeof(float) * dim_matrix);
    if (dim_matrix == 1) {
        inversed_matrix[0][0] = 1 / (float)matrix[0][0];
        return inversed_matrix;
    }
    for (int i = 0; i < dim_matrix; i++)
        for (int j = 0; j < dim_matrix; j++)
            inversed_matrix[i][j] = (1.00 / (float)determinant) * (float)matrix[i][j];
    for (int i = 0; i < dim_matrix; i++)
        free(matrix[i]);
    free(matrix);
    return inversed_matrix;
}

static float **get_decrypted_matrix(int nb_char, int dim_matrix, float **inversed_matrix, int **msg_matrix)
{
    int nb_line = nb_char / dim_matrix + nb_char % dim_matrix;
    float **cpt_matrix = malloc(sizeof(float *) * nb_line);

    for (int i = 0; i < nb_line; i++)
        cpt_matrix[i] = malloc(sizeof(int) * dim_matrix);
    for (int i = 0; i < nb_line; i++) {
        for (int j = 0; j < dim_matrix; j++) {
            for (int k = 0; k < dim_matrix; k++) {
                cpt_matrix[i][j] += inversed_matrix[k][j] * (float)msg_matrix[i][k];
            }
        }
    }
    printf("Decrypted message:\n");
    for (int i = 0; i < nb_line; i++) {
        for (int j = 0; j < dim_matrix; j++) {
            if (round(cpt_matrix[i][j]) == 0);
            else
                printf("%c", (char)round(cpt_matrix[i][j]));
        }
    }
    printf("\n");
    return cpt_matrix;
}

int **get_crypted_matrix(char *message, int dim_matrix, int *nb_char)
{
    char **nbr = my_str_to_word_array(message);
    int *decrypted;    
    int nb_line = strlen(message) / dim_matrix + strlen(message) % dim_matrix;
    int **msg_matrix = malloc(sizeof(int *) * nb_line);
    size_t t = 0;
    
    for (*nb_char = 0; nbr[*nb_char] != NULL; *nb_char += 1);
    decrypted = malloc(sizeof(int ) * *nb_char);
    for (int i = 0; i < *nb_char; i++) 
        decrypted[i] = atoi(nbr[i]);
    for (int i = 0; i < nb_line; i++)
        msg_matrix[i] = malloc(sizeof(int) * dim_matrix);
    for (int y = 0; y < nb_line; y++) {
        for (int x = 0; x < dim_matrix; x++) {
            if (t < strlen(message)) {
                msg_matrix[y][x] = decrypted[t];
            }
            else
                msg_matrix[y][x] = 0;
            t++;
        }
    }
    return msg_matrix;
}

void decrypted(char *key, char *message) 
{
    int dim_matrix = 0;
    int **key_matrix;
    int **comatrice;
    float **inversed_matrix;
    int **crypted_message;
    int det = 0;
    int nb_char = 0;

    key_matrix = get_key_matrix(key, &dim_matrix);
    crypted_message = get_crypted_matrix(message, dim_matrix, &nb_char);
    det = determinant(dim_matrix, key_matrix);
    comatrice = get_commatrix(dim_matrix, key_matrix);
    inversed_matrix = get_inversed_matrix(comatrice, det, dim_matrix);
    printf("Key matrix:\n");
    for (int i = 0; i < dim_matrix; i++) {
        for (int j = 0; j < dim_matrix; j++) {
            printf("%.3f\t", inversed_matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    get_decrypted_matrix(nb_char, dim_matrix, inversed_matrix, crypted_message);
}