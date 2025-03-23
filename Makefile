# Variabili
CC = g++
CFLAGS = -std=c++17 -Wall
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system
SRC_DIR = src
BUILD_DIR = build
OUTPUT = sassoCartaForbici

# File sorgenti
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
# File oggetto corrispondenti ai file sorgenti
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Regola principale (compilazione)
$(OUTPUT): $(OBJS)
	$(CC) $(OBJS) -o $(OUTPUT) $(LDFLAGS)

# Regola per creare i file oggetto
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -Iinclude -c $< -o $@

# Regola per pulire i file oggetto e l'eseguibile
clean:
	rm -rf $(BUILD_DIR)/*.o $(OUTPUT)

# Regola di default (compila tutto)
all: $(OUTPUT)

