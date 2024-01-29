# Компилятор
CC := gcc

# Названия папок
INC_DIR := ./inc
SRC_DIR := ./src
OUT_DIR := ./out
UNIT_DIR := ./unit_tests

OBJS := $(OUT_DIR)/libarr.o

UNIT_SRCS := $(UNIT_DIR)/check_arr.c
HEADERS := $(INC_DIR)/libarr.h $(INC_DIR)/liberr.h

# Опции компиляции
CFLAGS := -std=c99 -I$(INC_DIR) -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion
UNIT_LDFLAGS := -lcheck -lm -lpthread -lrt

unit_tests.exe : libarr.so $(OUT_DIR)/check_main.o $(UNIT_SRCS)
	$(CC) $(CFLAGS) $(OUT_DIR)/check_main.o -o $@ -lm $(UNIT_LDFLAGS) -L. -larr

unit : unit_tests.exe
	LD_LIBRARY_PATH=$LD_LIBRARY_PATH:. && \
	export LD_LIBRARY_PATH && \
	./$<

run : libarr.so
	LD_LIBRARY_PATH=$LD_LIBRARY_PATH:. && \
	export LD_LIBRARY_PATH && \
	python3 main.py


unit_valgrind : unit_tests.exe
	valgrind --leak-check=yes -q ./$<

dyn_lib : libarr.so

libarr.so : $(OBJS) $(HEADERS)
	$(CC) -o libarr.so -shared $(OBJS)

$(OUT_DIR)/check_main.o : $(UNIT_DIR)/check_main.c
	mkdir -p $(OUT_DIR)
	$(CC) -o ./$@ $(CFLAGS) -c $<

$(OUT_DIR)/%.o : $(SRC_DIR)/%.c
	mkdir -p $(OUT_DIR)
	$(CC) -o ./$@ $(CFLAGS) -c -fPIC $<

.PHONY : clean unit unit_valgrind dyn_lib
clean :
	rm -f -r $(OUT_DIR)
	rm -f ./*.exe ./*tmp* ./*.so
