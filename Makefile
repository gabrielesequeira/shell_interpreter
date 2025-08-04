# Nome do compilador
CC = gcc

# Flags de compilação
CFLAGS = -Wall -Wextra -g

# Nome do executável
TARGET = mysh

# Fontes
SRCS = main.c programas/shell.c programas/parser.c programas/execute.c

# Objetos
OBJS = main.o programas/shell.o programas/parser.o programas/execute.o

# Regra padrão
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

programas/%.o: programas/%.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean run
