# para saber mais: https://makefiletutorial.com/
CC = gcc

# flags pro compilador agir como a máquina pré-histórica que o migs quer
CFLAGS = -ansi -pedantic -Wall -Wextra

BUILD_DIR = projeto/build
TARGET = $(BUILD_DIR)/jogo
SRC := $(wildcard projeto/src/*.c)
OBJ := $(patsubst projeto/src/%.c,$(BUILD_DIR)/%.o,$(SRC)) # subsitui o caminho do arquivo .o para build

# adiciona $(BUILD_DIR) como dependência para garantir que a pasta exista
all: $(BUILD_DIR) $(TARGET)

# regra para criar o diretório de build
# uso if para ser compativel com ambos os sistemas
$(BUILD_DIR):
	@if not exist "$(BUILD_DIR)" mkdir "$(BUILD_DIR)"

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

# regra que de fato compila os .o e direciona para /build
projeto/build/%.o: projeto/src/%.c
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -f $(TARGET) $(OBJ)