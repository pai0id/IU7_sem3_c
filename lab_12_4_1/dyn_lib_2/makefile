# Компилятор
CC := gcc

# Названия папок
INC_DIR := ./lib_inc
SRC_DIR := ./lib_src
OUT_DIR := ./out
FUNC_DIR := ./func_tests

OBJS := $(OUT_DIR)/libarr.o $(OUT_DIR)/libmysort.o $(OUT_DIR)/libfilter.o

LIBHEADERS := $(INC_DIR)/libarr.h $(INC_DIR)/liberr.h $(INC_DIR)/libfilter.h $(INC_DIR)/libmysort.h

# Опции компиляции
CFLAGS := -std=c99 -I$(INC_DIR) -Wall -Werror -Wextra -Wfloat-equal -Wfloat-conversion

debug : CFLAGS += -g3
debug : app.exe

release : app.exe

app.exe : $(OUT_DIR)/main.o libarr.so libfilter.so ./err.h
	$(CC) $< -o $@ -ldl

func : app.exe
	./func_tests/scripts/func_tests.sh

valgrind : debug
	./func_tests/scripts/func_tests.sh --valgrind

dyn_libs : libarr.so libfilter.so

libarr.so : $(OUT_DIR)/libarr.o $(INC_DIR)/libarr.h $(INC_DIR)/liberr.h $(OUT_DIR)/libmysort.o $(INC_DIR)/libmysort.h
	$(CC) -o libarr.so -shared $(OUT_DIR)/libarr.o $(OUT_DIR)/libmysort.o

libfilter.so : $(OUT_DIR)/libfilter.o $(INC_DIR)/libfilter.h $(INC_DIR)/liberr.h
	$(CC) -o libfilter.so -shared $(OUT_DIR)/libfilter.o

debug_gcov : CC += --coverage
debug_gcov : debug
	mv $(wildcard ./*.gcno) $(OUT_DIR) 2> /dev/null || true
	
debug_asan : CFLAGS += -fno-omit-frame-pointer
debug_asan : CC := clang
debug_asan : CC += -fsanitize=address
debug_asan : debug

debug_msan : CFLAGS += -fPIE  -fno-omit-frame-pointer
debug_msan : CC := clang
debug_msan : CC += -fsanitize=memory
debug_msan : debug

debug_ubsan : CFLAGS += -fno-omit-frame-pointer
debug_ubsan : CC := clang
debug_ubsan : CC += -fsanitize=undefined
debug_ubsan : debug

all :
	LD_LIBRARY_PATH=$LD_LIBRARY_PATH:. && \
	export LD_LIBRARY_PATH && \
	./func_tests/scripts/main_test.sh

$(OUT_DIR)/main.o : main.c
	mkdir -p $(OUT_DIR)
	$(CC) -o ./$@ $(CFLAGS) -c $<

$(OUT_DIR)/%.o : $(SRC_DIR)/%.c
	mkdir -p $(OUT_DIR)
	$(CC) -o ./$@ $(CFLAGS) -c -fPIC $<

.PHONY : clean func debug valgrind debug_gcov debug_asan debug_msan debug_ubsan all dyn_libs
clean :
	rm -f -r $(OUT_DIR)
	rm -f ./*.exe ./*tmp* ./*.so ./*.o
