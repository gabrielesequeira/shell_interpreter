#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

#define MAX_TOKENS 64

char **parse_input(const char *input) {
    char **tokens = malloc(MAX_TOKENS * sizeof(char *));
    if (tokens == NULL) {
        perror("malloc");
        return NULL;
    }

    char *input_copy = strdup(input);  // Duplicamos a string para não modificar a original
    if (input_copy == NULL) {
        perror("strdup");
        free(tokens);
        return NULL;
    }

    int i = 0;
    char *token = strtok(input_copy, " ");
    while (token != NULL && i < MAX_TOKENS - 1) {
        tokens[i++] = strdup(token);  // Copia cada token para a lista
        token = strtok(NULL, " ");
    }
    tokens[i] = NULL;  // Termina com NULL (necessário para execvp, por exemplo)

    free(input_copy);
    return tokens;
}

void free_args(char **args) {
    if (args == NULL) return;
    for (int i = 0; args[i] != NULL; i++) {
        free(args[i]);
    }
    free(args);
}
