#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../headers/parser.h"

#define MAX_TOKENS 128

// Verifica se o caractere é um operador especial
int is_operator(char c) {
    return (c == '|' || c == '<' || c == '>');
}

char **parse_input(const char *input) {
    char **tokens = malloc(MAX_TOKENS * sizeof(char *));
    if (!tokens) {
        perror("malloc");
        return NULL;
    }

    int i = 0; // índice para tokens
    const char *p = input;

    while (*p != '\0') {
        // Pula espaços
        while (isspace(*p)) p++;

        if (*p == '\0') break;

        if (is_operator(*p)) {
            // operador isolado: | < >
            tokens[i] = malloc(2);
            if (tokens[i] == NULL) break;
            tokens[i][0] = *p;
            tokens[i][1] = '\0';
            p++;
            i++;
        } else if (*p == '\"' || *p == '\'') {
            // strings entre aspas
            char quote = *p++;
            const char *start = p;
            while (*p && *p != quote) p++;

            size_t len = p - start;
            tokens[i] = malloc(len + 1);
            if (tokens[i] == NULL) break;
            strncpy(tokens[i], start, len);
            tokens[i][len] = '\0';
            if (*p == quote) p++; // consome a aspa final
            i++;
        } else {
            // palavra comum
            const char *start = p;
            while (*p && !isspace(*p) && !is_operator(*p)) p++;

            size_t len = p - start;
            tokens[i] = malloc(len + 1);
            if (tokens[i] == NULL) break;
            strncpy(tokens[i], start, len);
            tokens[i][len] = '\0';
            i++;
        }

        if (i >= MAX_TOKENS - 1) break;
    }

    tokens[i] = NULL; // finaliza o array
    return tokens;
}

void free_args(char **args) {
    if (args == NULL) return;
    for (int i = 0; args[i] != NULL; i++) {
        free(args[i]);
    }
    free(args);
}
