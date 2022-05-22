BUILD_DIR = ./build
SRC_DIR = ./src
CC = gcc
LD = ld
LIB = -I $(SRC_DIR)
CFLAGS = $(LIB) -c -fno-builtin -nostdlib -fno-stack-protector -m32
OBJS = $(BUILD_DIR)/malloc.o $(BUILD_DIR)/printf.o $(BUILD_DIR)/stdio.o $(BUILD_DIR)/string.o $(BUILD_DIR)/entry.o

$(OBJS): $(SRC_DIR)/entry.c $(SRC_DIR)/malloc.c $(SRC_DIR)/stdio.c $(SRC_DIR)/string.c $(SRC_DIR)/printf.c
	$(CC) $(CFLAGS) $(SRC_DIR)/entry.c $(SRC_DIR)/malloc.c $(SRC_DIR)/stdio.c $(SRC_DIR)/string.c $(SRC_DIR)/printf.c
	@mv ./*o $(BUILD_DIR)

$(BUILD_DIR)/minicrt.a: $(OBJS)
	ar -rs $@ $(OBJS)

test.bin: test.c $(BUILD_DIR)/minicrt.a
	$(CC) -I ./src -c -ggdb -fno-builtin -nostdlib -fno-stack-protector test.c -o ./build/test.o -m32
	$(LD) -static -e mini_crt_entry ./build/test.o ./build/minicrt.a -o ./test.bin -m elf_i386

.PHONY: mk_dir clean all

mk_dir:
	@if [ ! -d $(BUILD_DIR) ]; then mkdir $(BUILD_DIR); fi

clean:
	rm ./test.bin && cd $(BUILD_DIR) && rm ./*

build: test.bin

all: mk_dir build
