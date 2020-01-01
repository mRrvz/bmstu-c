CFILES := $(wildcard *.c)
TESTS_PATH := tests/func_tests/run_tests.sh
FLAGS := -Wall -Werror -O2 -std=c99
DEBUG_FLAGS := -DDEBUG -g

ifeq (debug,$(firstword $(MAKECMDGOALS)))
	FLAGS := $(FLAGS) $(DEBUG_FLAGS)
endif

app.exe: $(patsubst %.c,%.o,$(CFILES))
	gcc $(FLAGS) $^ -o app.exe

debug: $(patsubst %.c,%.o,$(CFILES))
	gcc $(FLAGS) $^ -o app.exe

tests: $(TESTS_PATH)
	$^

run: app.exe
	./app.exe

clean:
	rm *.o *.exe *.d *.out

%.o: %.c
	gcc $(FLAGS) -c -MD $<

include $(wildcard *.d)
