CFILES := $(wildcard *.c)
TEST := snprintf.c string_funcs.c cunit_tests.c parsing.c
FLAGS := -Wall -Werror -O2 -std=c99
DEBUG_FLAGS := -DDEBUG -g

ifeq (debug,$(firstword $(MAKECMDGOALS)))
	FLAGS := $(FLAGS) $(DEBUG_FLAGS)
endif

app.exe: $(patsubst %.c,%.o,$(CFILES))
	gcc $(FLAGS) $^ -o app.exe

debug: $(patsubst %.c,%.o,$(CFILES))
	gcc $(FLAGS) $^ -o app.exe

test.exe:
	gcc $(FLAGS) tests/unit_tests/unit_tests.c -o test.exe

cunit_tests.exe: $(patsubst %.c,%.o,$(TEST))
	gcc $(FLAGS) -lcunit $^ -o $@

run: app.exe
	./app.exe

run_tests: cunit_tests.exe
	./cunit_tests.exe

clean:
	rm *.o *.exe *.d *.out

%.o: %.c
	gcc $(FLAGS) -c -MD $<

cunit_tests.o: tests/unit_tests/cunit_tests.c
	gcc $(FLAGS) -c -MD $<

include $(wildcard *.d tests/unit_tests/*.d)
