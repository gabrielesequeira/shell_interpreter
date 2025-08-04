#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include "../headers/executer.h"

// Função auxiliar para contar tokens até encontrar um delimitador
int count_until(char **args, const char *delim) {
    int i = 0;
    while (args[i] && strcmp(args[i], delim) != 0) i++;
    return i;
}

// Função que executa um único comando simples (sem pipe)
void execute_simple_command(char **args) {
    int in_redirect = -1;
    int out_redirect = -1;

    // Detecta redirecionamento
    for (int i = 0; args[i]; i++) {
        if (strcmp(args[i], "<") == 0) {
            in_redirect = i;
        } else if (strcmp(args[i], ">") == 0) {
            out_redirect = i;
        }
    }

    // Manipula redirecionamento
    if (in_redirect != -1 || out_redirect != -1) {
        pid_t pid = fork();
        if (pid == 0) {
            // Redirecionamento de entrada
            if (in_redirect != -1) {
                int fd = open(args[in_redirect + 1], O_RDONLY);
                if (fd < 0) {
                    perror("open");
                    exit(EXIT_FAILURE);
                }
                dup2(fd, STDIN_FILENO);
                close(fd);
                args[in_redirect] = NULL;
            }

            // Redirecionamento de saída
            if (out_redirect != -1) {
                int fd = open(args[out_redirect + 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
                if (fd < 0) {
                    perror("open");
                    exit(EXIT_FAILURE);
                }
                dup2(fd, STDOUT_FILENO);
                close(fd);
                args[out_redirect] = NULL;
            }

            execvp(args[0], args);
            perror("execvp");
            exit(EXIT_FAILURE);
        } else {
            wait(NULL);
        }
        return;
    }

    // Execução sem redirecionamento
    pid_t pid = fork();
    if (pid == 0) {
        execvp(args[0], args);
        perror("execvp");
        exit(EXIT_FAILURE);
    } else {
        wait(NULL);
    }
}

// Função principal que lida com pipes e redirecionamentos
void execute_command(char **args) {
    int num_pipes = 0;

    // Conta quantos pipes existem
    for (int i = 0; args[i]; i++) {
        if (strcmp(args[i], "|") == 0) num_pipes++;
    }

    // Se não há pipes, trata como comando simples
    if (num_pipes == 0) {
        execute_simple_command(args);
        return;
    }

    // Pipeline: cria pipes e forks para cada comando
    int pipefd[2 * num_pipes];
    for (int i = 0; i < num_pipes; i++) {
        if (pipe(pipefd + i*2) < 0) {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
    }

    int cmd_index = 0;
    int pid;
    int i = 0;

    while (args[i]) {
        // Pega os argumentos até o próximo "|"
        char *cmd_args[64];
        int j = 0;

        while (args[i] && strcmp(args[i], "|") != 0) {
            cmd_args[j++] = args[i++];
        }
        cmd_args[j] = NULL;

        pid = fork();
        if (pid == 0) {
            // Se não é o primeiro comando, redireciona entrada do pipe anterior
            if (cmd_index != 0) {
                dup2(pipefd[(cmd_index - 1)*2], STDIN_FILENO);
            }

            // Se não é o último comando, redireciona saída para o pipe atual
            if (cmd_index < num_pipes) {
                dup2(pipefd[cmd_index*2 + 1], STDOUT_FILENO);
            }

            // Fecha todos os pipes no filho
            for (int k = 0; k < 2 * num_pipes; k++) close(pipefd[k]);

            execvp(cmd_args[0], cmd_args);
            perror("execvp");
            exit(EXIT_FAILURE);
        }

        // Pula o pipe "|"
        if (args[i]) i++;
        cmd_index++;
    }

    // Fecha todos os pipes no pai
    for (int i = 0; i < 2 * num_pipes; i++) close(pipefd[i]);

    // Espera todos os filhos
    for (int i = 0; i <= num_pipes; i++) wait(NULL);
}
