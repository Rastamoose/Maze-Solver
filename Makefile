CC = gcc
INCLUDE_DIR := include
BIN_DIR := bin
SRC_DIR := src
OBJ_DIR := obj
GRAPHICS_DIR := drawapp

SOURCES := $(shell find $(SRC_DIR) $(GRAPHICS_DIR) -type f -name '*.c') 
OBJECTS := $(addprefix $(OBJ_DIR)/,$(SOURCES:.c=.o))

CFLAGS := -g -Wall -Wextra -MMD -MP 

.PHONY: all clean

all: $(BIN_DIR)/main

$(BIN_DIR)/main: $(OBJECTS)
	$(CC) $^ -o $@ 

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) -c $< -o $@ $(CFLAGS) -I$(INCLUDE_DIR) -I$(GRAPHICS_DIR)

clean:
	rm -rf $(BIN_DIR)/*
	rm -rf $(OBJ_DIR)/*

-include $(OBJECTS:.o:.d)