# Компилятор
CC := gcc

OBJS := ./associative_array_impl_1.o ./associative_array_pair.o ./list.o ./node_list.o 
CHECK_OBJS := ./check_main.o ./check_arr_clear.o ./check_arr_each.o ./check_arr_io.o ./check_arr_max.o ./check_arr_min.o ./check_arr_rem.o

HEADERS := ./associative_array.h ./associative_array_pair.h ./list.h ./node_list.h
CHECK_HEADERS := ./check_arr_clear.h ./check_arr_each.h ./check_arr_io.h ./check_arr_max.h ./check_arr_min.h ./check_arr_rem.h ./check_defines.h

# Опции компиляции
CFLAGS := -g -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion
UNIT_LDFLAGS := -lcheck -lm -lpthread -lrt

unit_tests.exe : $(OBJS) $(CHECK_OBJS) $(HEADERS) $(CHECK_HEADERS)
	$(CC) $(OBJS) $(CHECK_OBJS) -o $@ -lm $(UNIT_LDFLAGS)

unit : unit_tests.exe
	./$<

unit_valgrind : unit_tests.exe
	valgrind --leak-check=yes -q ./$<

./%.o : ./%.c $(HEADERS) $(CHECK_HEADERS)
	$(CC) -o ./$@ $(CFLAGS) -c $<

.PHONY : clean unit unit_valgrind
clean :
	rm -f ./*.exe ./*tmp* ./*.o
