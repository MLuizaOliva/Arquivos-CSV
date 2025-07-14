OUT_DIR := build
SRC_DIR := src
INC_DIR := include
CFLAGS := -Wall -Wextra -std=c99
CC := gcc

ifeq ($(OS), Windows_NT)
	EXE_EXT := .exe
	RUN := $(OUT_DIR)\Main.exe
	SOURCES := $(wildcard $(SRC_DIR)/**/*.c) $(wildcard $(SRC_DIR)/*.c)
	MKDIR := if not exist $(OUT_DIR) mkdir $(OUT_DIR)
	RM := del /Q
	PATH_SEP := \\
else
	EXE_EXT := 
	RUN := ./$(OUT_DIR)/Main
	SOURCES := $(shell find $(SRC_DIR) -name '*.c')
	MKDIR := mkdir -p $(OUT_DIR)
	RM := rm -f
	PATH_SEP := /
endif

EXE_PATH := $(OUT_DIR)/Main$(EXE_EXT)

all: $(EXE_PATH)

$(EXE_PATH): $(SOURCES) | $(OUT_DIR)
	$(CC) -o $@ $(SOURCES) -I$(INC_DIR) $(CFLAGS)

$(OUT_DIR):
	$(MKDIR)

run: $(EXE_PATH)
	$(RUN)

clean:
	$(RM) $(OUT_DIR)$(PATH_SEP)*.o $(OUT_DIR)$(PATH_SEP)*.exe $(EXE_PATH)

.PHONY: all run clean