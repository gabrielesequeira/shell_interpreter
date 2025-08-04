# Shell Interpreter (Terminal Command Interpreter)

Project for the course **INF1018 - Software Básico**  
Developed in C language, focusing on system calls, process management, input/output redirection, pipes, and environment variables.

## Objective

Create a simplified yet advanced shell interpreter that can:

- Read and parse user commands from the terminal
- Execute system commands with arguments
- Handle input and output redirection (`>`, `<`)
- Support pipes (`|`) for chaining commands
- Manage environment variables and basic built-in commands (`cd`, `exit`, etc.)

## Features

### Core Shell Functionalities
- Read command line input with prompt  
- Parse commands and arguments  
- Execute commands using `fork()` and `execvp()`  
- Support built-in commands such as `cd` and `exit`  
- Environment variable expansion (`$HOME`, `$PATH`, etc.)  

### Advanced Features
- Input redirection (`command < file`)  
- Output redirection (`command > file`)  
- Pipes to connect multiple commands (`command1 | command2`)  
- Handling of multiple pipes in a single command line  

### Error Handling
- Report command not found  
- Handle syntax errors in redirection and pipes  
- Graceful exit and cleanup  

## Topics Learned and Practiced

During the development of this project for the course, key system programming concepts were applied and reinforced, including:

- **Process Management**  
  - Creating child processes using `fork()`  
  - Executing commands with `execvp()`  
  - Waiting for process termination with `wait()`  

- **Interprocess Communication**  
  - Using `pipe()` to create communication channels between processes  
  - Redirecting standard input/output using `dup2()`  

- **File Descriptor Manipulation**  
  - Managing input/output redirection through file descriptors  
  - Opening and closing files for redirection  

- **Command Parsing and String Manipulation**  
  - Splitting input strings into commands and arguments  
  - Detecting and processing special symbols like `|`, `<`, and `>`  

- **Environment Variables**  
  - Accessing environment variables with `getenv()`  
  - Expanding variables in command input  

- **Built-in Command Implementation**  
  - Handling commands that modify shell state (e.g., `cd`) internally  

- **Terminal Interaction**  
  - Implementing a command prompt  
  - Reading user input dynamically  

- **Error Detection and Handling**  
  - Validating command syntax  
  - Reporting and managing runtime errors  

## Project Structure
``` bash
shell_interpreter/
├── main.c
├── MAKEFILE
├── README
├── programs/
│   ├── parser.c
│   ├── executer.c
    ├── shell.c
├── headers/
│   ├── parser.h
│   ├── executer.h
    ├── shell.h
```
