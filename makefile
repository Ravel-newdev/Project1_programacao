# para saber mais: https://makefiletutorial.com/
CC = gcc

# flags pro compilador agir como a máquina (pré-histórica, era com -ansi) que o migs quer
CFLAGS = -std=c99 -pedantic -Wall -Wextra -lm

TARGET = projeto/build/jogo
SRC := $(wildcard projeto/src/*.c)
OBJ := $(patsubst projeto/src/%.c,projeto/build/%.o,$(SRC)) # subsitui o caminho do arquivo .o para build

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

# regra que de fato compila os .o e direciona para /build
projeto/build/%.o: projeto/src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJ)