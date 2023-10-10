# Компилятор
CC := gcc

# Названия папок
INC_DIR := ./inc
SRC_DIR := ./src
OUT_DIR := ./out
FUNC_DIR := ./func_tests
UNIT_DIR := ./unit_tests

OBJS := $(OUT_DIR)/arr.o $(OUT_DIR)/mysort.o $(OUT_DIR)/filter.o

UNIT_SRCS := unit_tests/check_arr.c unit_tests/check_filter.c unit_tests/check_main.c unit_tests/check_mysort.c
HEADERS := inc/arr.h inc/err.h inc/filter.h inc/mysort.h

# Опции компиляции
CFLAGS := -std=c99 -I$(INC_DIR) -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion
UNIT_LDFLAGS := -lcheck -lm -lpthread -lrt

debug : CFLAGS += -g3
debug : app.exe

release : app.exe

app.exe : $(OBJS) $(OUT_DIR)/main.o
	$(CC) $^ -o $@ -lm

unit_tests.exe : $(OBJS) $(OUT_DIR)/check_main.o $(UNIT_SRCS)
	$(CC) $(OBJS) $(OUT_DIR)/check_main.o -o $@ -lm $(UNIT_LDFLAGS)

unit : unit_tests.exe
	./$<

func : app.exe
	./func_tests/scripts/func_tests.sh

valgrind : app.exe
	./func_tests/scripts/func_tests.sh --valgrind

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

$(OUT_DIR)/check_main.o : $(UNIT_DIR)/check_main.c $(HEADERS)
	mkdir -p $(OUT_DIR)
	$(CC) -o ./$@ $(CFLAGS) -c $<

$(OUT_DIR)/%.o : $(SRC_DIR)/%.c $(inc/arr.h inc/err.h inc/filter.h inc/mysort.h)
	mkdir -p $(OUT_DIR)
	$(CC) -o ./$@ $(CFLAGS) -c $<

.PHONY : clean unit func debug valgrind debug_gcov debug_asan debug_msan debug_ubsan all
clean :
	rm -f -r $(OUT_DIR)
	rm -f ./*.exe ./*tmp*
