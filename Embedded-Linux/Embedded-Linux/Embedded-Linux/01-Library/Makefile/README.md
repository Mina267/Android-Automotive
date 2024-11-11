# Makefile

Automate the build process with a `Makefile`:

```Makefile
# Compiler and flags
CC = gcc
CFLAGS = -Wall -I ./includes/
LDFLAGS = -L./lib/ -lmylib
PICFLAGS = -fPIC

# Directories
SRC_DIR = ./src
OBJ_DIR = ./obj
OBJ_DYNAMIC_DIR = ./objDynamic
LIB_DIR = ./lib
APP_DIR = ./app

# Files
STATIC_LIB = $(LIB_DIR)/libmylib.a
SHARED_LIB = $(LIB_DIR)/libmylib.so
STATIC_EXEC = Run
DYNAMIC_EXEC = dynamicApp

# Source files
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJ_DYNAMIC_FILES = $(SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DYNAMIC_DIR)/%.o)

# Targets
all: $(STATIC_EXEC) $(DYNAMIC_EXEC)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DYNAMIC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(PICFLAGS) -c $< -o $@

$(STATIC_LIB): $(OBJ_FILES)
	ar -rcs $@ $^

$(SHARED_LIB): $(OBJ_DYNAMIC_FILES)
	$(CC) -shared -o $@ $^

$(STATIC_EXEC): $(APP_DIR)/main.c $(STATIC_LIB)
	$(CC) $(CFLAGS) -static $< -o $@ $(LDFLAGS)

$(DYNAMIC_EXEC): $(APP_DIR)/main.c $(SHARED_LIB)
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS) -Wl,-rpath=$(LIB_DIR)

clean:
	rm -f $(OBJ_DIR)/*.o $(OBJ_DYNAMIC_DIR)/*.o $(STATIC_LIB) $(SHARED_LIB) $(STATIC_EXEC) $(DYNAMIC_EXEC)

.PHONY: all clean
```
