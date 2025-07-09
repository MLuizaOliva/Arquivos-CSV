OUT_DIR := build
SRC_DIR := src
INC_DIR := include
CFLAGS := 
CC := gcc

SOURCES := $(shell find $(SRC_DIR) -name '*.c')

ifeq ($(OS), Windows_NT)
	EXE_EXT := .exe
	RUN := $(OUT_DIR)\Main.exe
else
	EXE_EXT := 
	RUN := ./$(OUT_DIR)/Main
endif

EXE_PATH := $(OUT_DIR)/Main$(EXE_EXT)

all: $(EXE_PATH)

$(EXE_PATH): $(SOURCES) | $(OUT_DIR)
	$(CC) -o $@ $(SOURCES) -I$(INC_DIR) $(CFLAGS)

$(OUT_DIR):
	@mkdir -p $(OUT_DIR)

run: $(EXE_PATH)
	$(RUN)

clean:
	rm -f $(OUT_DIR)/*.o $(OUT_DIR)/*.exe $(EXE_PATH)