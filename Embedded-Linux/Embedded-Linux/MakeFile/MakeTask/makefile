cc = gcc
INCS = -I ./include
SRC_DIR = src
BIN_DIR = bin
BULID_DIR = build
DIRS = $(BIN_DIR) $(BULID_DIR)
src = $(wildcard $(SRC_DIR)/*.c)
obj = $(patsubst $(SRC_DIR)/%.c, $(BIN_DIR)/%.o, $(src))
projectName = app
TARGET = $(BULID_DIR)/$(projectName)


all : clean docs $(TARGET) 

docs:
	@$(foreach DIR, $(DIRS), mkdir -p $(DIR);)

# Compiling the .c files to .o files
# | $(BIN_DIR): create bin file, if it did not exist 
$(BIN_DIR)/%.o : $(SRC_DIR)/%.c | $(BIN_DIR)
	$(cc) -c $(INCS) $< -o $@

# Create the object files directory if it does not exist
$(BIN_DIR): 
	mkdir -p $(BIN_DIR)

# Linking the object files to create the final executable
$(TARGET) : $(obj) | $(BULID_DIR)
	$(cc) $(INCS) $^ -o $@


# Create the build directory if it does not exist	
$(BULID_DIR):
	mkdir -p $(BULID_DIR)
	
.PHONY:clean
clean:
	@$(foreach DIR, $(DIRS), rm -rf $(DIR) ;)

