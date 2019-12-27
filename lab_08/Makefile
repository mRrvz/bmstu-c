CFILES := $(wildcard *.c)
TEST := arr_oper.c math_oper.c CUnitTests.c
FLAGS := -Wall -Werror -std=c99

app.exe: $(patsubst %.c,%.o,$(CFILES))
	gcc $(FLAGS) -O2 $^ -o $@

DEBUG: $(patsubst %.c,%.o,$(CFILES))
	gcc $(FLAGS) -ggdb $^ -o app.exe

test.exe:
	gcc $(FLAGS) tests/UnitTests/test.c -o test.exe

CUnitTests.exe: $(patsubst %.c,%.o,$(TEST))
	gcc $(FLAGS) -lcunit $^ -o $@

run: app.exe
	./app.exe

runTests: CUnitTests.exe
	./CUnitTests.exe

clean: 
	rm *.o *.exe *.d

%.o: %.c 
	gcc $(FLAGS) -c -MD $<

CUnitTests.o: tests/UnitTests/*.c
	gcc $(FLAGS) -c -MD $<

include $(wildcard *.d tests/UnitTests/*.d)
