#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers\parser.h"
#include "headers\executer.h"
#include "headers\utils.h"

#define MAX_INPUT 1024

void shell_run(){
    char input[MAX_INPUT]; //BUFFER FIXO
    
    while(1){
        printf("mysh> ");
        if(fgets(input, MAX_INPUT, stdin)==NULL){
            printf("\n");
            break;
        }
        input[strspn(input, "\n")] = '\0'; //retorna o indice do primeiro \n encontrado e substitui por \0

        if(strlen(input) == 0) continue; // usuário aperta Enter
        char **args = parse_input(input); //PARSE.H
        if (args == NULL) continue;  // se o parse(separador de tokens) falhar ignora e continua
        execute_command(args); //EXECUTER.H
        free_args(args); // libera memoria alocada dinamicamente - UTILS.H
    }
}