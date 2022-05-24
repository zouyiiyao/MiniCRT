BUILD_DIR = ./build
SRC_DIR = ./src
INC_DIR = ./include
CC = gcc
CPP = g++
LD = ld
LIB = -I $(INC_DIR)
CFLAGS = $(LIB) -c -fno-builtin -nostdlib -fno-stack-protector -m32
CPPFLAGS = $(LIB) -c -nostdinc++ -fno-rtti -fno-exceptions -fno-builtin -nostdlib -fno-stack-protector -m32
OBJS = $(BUILD_DIR)/malloc.o $(BUILD_DIR)/printf.o $(BUILD_DIR)/stdio.o $(BUILD_DIR)/string.o $(BUILD_DIR)/entry.o $(BUILD_DIR)/atexit.o

$(OBJS): $(SRC_DIR)/entry.c $(SRC_DIR)/malloc.c $(SRC_DIR)/stdio.c $(SRC_DIR)/string.c $(SRC_DIR)/printf.c $(SRC_DIR)/atexit.c
	$(CC) $(CFLAGS) $(SRC_DIR)/entry.c $(SRC_DIR)/malloc.c $(SRC_DIR)/stdio.c $(SRC_DIR)/string.c $(SRC_DIR)/printf.c $(SRC_DIR)/atexit.c
	@mv ./*o $(BUILD_DIR)

$(BUILD_DIR)/minicrt.a: $(OBJS)
	$(CPP) $(CPPFLAGS) $(SRC_DIR)/crtbegin.cpp $(SRC_DIR)/crtend.cpp $(SRC_DIR)/ctors.cpp $(SRC_DIR)/new_delete.cpp $(SRC_DIR)/sysdep.cpp $(SRC_DIR)/iostream.cpp
	@mv ./*.o $(BUILD_DIR)
	ar -rs $@ $(OBJS) $(BUILD_DIR)/ctors.o $(BUILD_DIR)/iostream.o $(BUILD_DIR)/new_delete.o $(BUILD_DIR)/sysdep.o 

test.bin: test.cpp $(BUILD_DIR)/minicrt.a
	$(CPP) -I ./include -c -nostdinc++ -fno-rtti -fno-exceptions -fno-builtin -nostdlib -fno-stack-protector test.cpp -o ./build/test.o -m32
	$(LD) -static -e mini_crt_entry ./build/crtbegin.o ./build/test.o ./build/minicrt.a ./build/crtend.o -o ./test.bin -m elf_i386
 

.PHONY: mk_dir clean all

mk_dir:
	@if [ ! -d $(BUILD_DIR) ]; then mkdir $(BUILD_DIR); fi

clean:
	@rm -f ./test.bin
	cd $(BUILD_DIR) && rm -f ./*

build: test.bin

all: mk_dir build
