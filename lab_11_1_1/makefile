# Компилятор
CC := gcc

INC_DIR := ./inc
SRC_DIR := ./src
OUT_DIR := ./out
UNIT_DIR := ./unit_tests

OBJS := $(OUT_DIR)/my_snprintf.o
HEADERS := $(INC_DIR)/my_snprintf.h

UNIT_SRC := $(UNIT_DIR)/check_my_snprintf.c

# Опции компиляции
CFLAGS := -I$(INC_DIR) -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion
UNIT_LDFLAGS := -lcheck -lm -lpthread -lrt

unit_tests.exe : $(OBJS) $(OUT_DIR)/check_main.o $(UNIT_SRCS) $(HEADERS)
	$(CC) $(OBJS) $(OUT_DIR)/check_main.o -o $@ -lm $(UNIT_LDFLAGS)

unit : unit_tests.exe
	./$<

unit_valgrind : unit_tests.exe
	valgrind --leak-check=yes -q ./$<

$(OUT_DIR)/check_main.o : $(UNIT_DIR)/check_main.c $(HEADERS)
	mkdir -p $(OUT_DIR)
	$(CC) -o ./$@ $(CFLAGS) -c $<

$(OUT_DIR)/%.o : $(SRC_DIR)/%.c $(HEADERS)
	mkdir -p $(OUT_DIR)
	$(CC) -o ./$@ $(CFLAGS) -c $<

.PHONY : clean unit unit_valgrind
clean :
	rm -f ./*.exe ./*tmp* ./*.o
	rm -f -r $(OUT_DIR)
