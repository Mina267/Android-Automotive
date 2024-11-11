
# Project Structure

The project directory is organized as follows:

- `src/` - Contains the `.c` source files.
- `include/` - Contains the `.h` header files.
- `bin/` - Contains the compiled object files.
- `build/` - Contains the final executable.

## Makefile Overview


### Variables

- `cc` - The compiler to use (gcc).
- `INCS` - Include directories (`-I ./include`).
- `SRC_DIR` - Directory containing source files (`src`).
- `BIN_DIR` - Directory for object files (`bin`).
- `BULID_DIR` - Directory for the final executable (`build`).
- `DIRS` - Directories to be created (`bin` and `build`).
- `src` - List of source files in the `src` directory.
- `obj` - List of object files corresponding to the source files.
- `projectName` - Name of the project executable (`app`).
- `TARGET` - Path to the final executable (`build/app`).

### Targets

- `all` - Default target. Cleans previous builds, creates necessary directories, and builds the target executable.
- `docs` - Creates the `bin` and `build` directories if they do not exist.
- `$(BIN_DIR)/%.o` - Compiles `.c` files into `.o` object files.
- `$(BIN_DIR)` - Creates the `bin` directory if it does not exist.
- `$(TARGET)` - Links the object files to create the final executable.
- `$(BULID_DIR)` - Creates the `build` directory if it does not exist.
- `clean` - Removes the `bin` and `build` directories.


### Key Makefile Features

#### Directory Creation and Cleanup

- `@$(foreach DIR, $(DIRS), mkdir -p $(DIR);)`
  - This line uses the `foreach` function to iterate over the directories specified in `DIRS` (`bin` and `build`).
  - For each directory, it runs the `mkdir -p` command, which creates the directory if it does not exist.
  - The `@` symbol suppresses the command output, keeping the Makefile output clean.

- `@$(foreach DIR, $(DIRS), rm -rf $(DIR);)`
  - This line also uses the `foreach` function to iterate over the directories specified in `DIRS`.
  - For each directory, it runs the `rm -rf` command, which removes the directory and its contents recursively.
  - The `@` symbol suppresses the command output.

#### Source and Object Files

- `src = $(wildcard $(SRC_DIR)/*.c)`
  - The `wildcard` function generates a list of all `.c` source files in the `src` directory.
  - This list is stored in the `src` variable.

- `obj = $(patsubst $(SRC_DIR)/%.c, $(BIN_DIR)/%.o, $(src))`
  - The `patsubst` function converts the list of source files (`src`) into a list of object files.
  - It replaces the `src` directory and `.c` extension with the `bin` directory and `.o` extension.
  - The resulting list of object files is stored in the `obj` variable.

