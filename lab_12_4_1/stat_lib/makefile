# Компилятор
CC := gcc

# Названия папок
INC_DIR := ./lib_inc
SRC_DIR := ./lib_src
OUT_DIR := ./out
FUNC_DIR := ./func_tests
UNIT_DIR := ./unit_tests

OBJS := $(OUT_DIR)/libarr.o $(OUT_DIR)/libmysort.o $(OUT_DIR)/libfilter.o

UNIT_SRCS := $(UNIT_DIR)/check_arr.c $(UNIT_DIR)/check_filter.c $(UNIT_DIR)/check_main.c $(UNIT_DIR)/check_mysort.c
LIBHEADERS := $(INC_DIR)/libarr.h $(INC_DIR)/liberr.h $(INC_DIR)/libfilter.h $(INC_DIR)/libmysort.h

# Опции компиляции
CFLAGS := -std=c99 -I$(INC_DIR) -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion
UNIT_LDFLAGS := -lcheck -lm -lpthread -lrt

debug : CFLAGS += -g3
debug : app.exe

release : app.exe

app.exe : $(OUT_DIR)/main.o libarr.a libfilter.a ./err.h
	$(CC) $(CFLAGS) $< -o $@ -lm -L. -larr -lfilter

unit_tests.exe : libarr.a libfilter.a $(OUT_DIR)/check_main.o $(UNIT_SRCS)
	$(CC) $(CFLAGS) $(OUT_DIR)/check_main.o -o $@ -lm $(UNIT_LDFLAGS) -L. -larr -lfilter

unit : unit_tests.exe
	./$<

unit_valgrind : unit_tests.exe
	valgrind --leak-check=yes -q ./$< 

func : app.exe
	./func_tests/scripts/func_tests.sh

valgrind : app.exe
	./func_tests/scripts/func_tests.sh --valgrind

stat_libs : libarr.a libfilter.a

libarr.a : $(OUT_DIR)/libarr.o $(INC_DIR)/libarr.h $(INC_DIR)/liberr.h $(OUT_DIR)/libmysort.o $(INC_DIR)/libmysort.h
	ar cr libarr.a $(OUT_DIR)/libarr.o $(OUT_DIR)/libmysort.o
	ranlib libarr.a

libfilter.a : $(OUT_DIR)/libfilter.o $(INC_DIR)/libfilter.h $(INC_DIR)/liberr.h
	ar cr libfilter.a $(OUT_DIR)/libfilter.o
	ranlib libfilter.a

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
	./func_tests/scripts/main_test.sh

$(OUT_DIR)/check_main.o : $(UNIT_DIR)/check_main.c
	mkdir -p $(OUT_DIR)
	$(CC) -o ./$@ $(CFLAGS) -c $<

$(OUT_DIR)/main.o : main.c
	mkdir -p $(OUT_DIR)
	$(CC) -o ./$@ $(CFLAGS) -c $<

$(OUT_DIR)/%.o : $(SRC_DIR)/%.c
	mkdir -p $(OUT_DIR)
	$(CC) -o ./$@ $(CFLAGS) -c $<

.PHONY : clean unit func debug valgrind debug_gcov debug_asan debug_msan debug_ubsan all stat_lib
clean :
	rm -f -r $(OUT_DIR)
	rm -f ./*.exe ./*tmp* ./*.a
