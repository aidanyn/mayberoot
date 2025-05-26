# Compiler and flags
CC ?= gcc
CFLAGS = -Wall -Wextra -pedantic -std=c11 -g
RELEASE_CFLAGS = -O2 -DNDEBUG

# Project structure
TARGET = mayberoot
SRC = src/main.c
OBJ = $(SRC:.c=.o)
BIN_DIR = bin

# Install paths (adjust as needed)
PREFIX = /usr/local
BINDIR = $(PREFIX)/bin

# Default build (debug)
all: $(BIN_DIR)/$(TARGET)

# Release build with optimizations
release: CFLAGS += $(RELEASE_CFLAGS)
release: clean $(BIN_DIR)/$(TARGET)

$(BIN_DIR)/$(TARGET): $(OBJ) | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^
	@echo "\nBuild successful: $(BIN_DIR)/$(TARGET)"

$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Install system-wide
install: release
	@install -Dm755 $(BIN_DIR)/$(TARGET) $(DESTDIR)$(BINDIR)/$(TARGET)
	@echo "Installed to $(DESTDIR)$(BINDIR)/$(TARGET)"

# Uninstall
uninstall:
	@rm -f $(DESTDIR)$(BINDIR)/$(TARGET)
	@echo "Removed $(DESTDIR)$(BINDIR)/$(TARGET)"

# Clean build artifacts
clean:
	@rm -rf $(BIN_DIR) $(OBJ)
	@echo "Clean complete"

# Run basic tests
test: all
	@echo "Running tests..."
	@$(BIN_DIR)/$(TARGET) touch /etc/protected_file || true

.PHONY: all release clean install uninstall test