#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include "../headers/parser.h"
#include "../headers/executer.h"

#define MAX_INPUT 1024

void handle_sigint(int sig) {
    // Ao receber Ctrl+C, finaliza o shell (sem reapresentar o prompt)
    printf("\nEncerrando o shell com Ctrl+C...\n");
    exit(0);
}

void shell_run() {
    char input[MAX_INPUT]; // Buffer fixo para entrada

    // Define o comportamento para Ctrl+C (SIGINT)
    signal(SIGINT, handle_sigint);

    while (1) {
        printf("mysh> ");
        if (fgets(input, MAX_INPUT, stdin) == NULL) {
            // Se for Ctrl+D ou erro de leitura, sai do shell
            printf("\n");
            break;
        }

        // Remove o '\n' do final da linha
        input[strcspn(input, "\n")] = '\0';

        // Ignora linhas em branco
        if (strlen(input) == 0) continue;

        // Trata o comando interno "exit"
        if (strcmp(input, "exit") == 0) {
            printf("Encerrando o shell...\n");
            break;
        }

        // Faz o parsing da linha de comando
        char **args = parse_input(input);
        if (args == NULL) continue;

        // Executa o comando
        execute_command(args);

        // Libera memória dos argumentos
        free_args(args);
    }
}
