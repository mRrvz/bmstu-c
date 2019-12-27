CFILES := $(wildcard *.c)
FLAGS := -Wall -Werror -std=c99 
DEBUG := DDEBUG
MAKEKEY := -O2
DEBUGKEY := -ggdb

ifeq (app.exe,$(firstword $(MAKECMDGOALS)))
  RUN_ARGS := $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))
  $(eval $(RUN_ARGS):;@:)

  ifeq "$(DEBUG)" "$(RUN_ARGS)"
  	MAKEKEY := $(DEBUGKEY)
  endif
  
endif

app.exe: $(patsubst %.c,%.o,$(CFILES))
	gcc $(FLAGS) $(MAKEKEY) $^ -o app.exe

test.exe:
	gcc $(FLAGS) tests/UnitTests/test.c -o test.exe

CUnitTests.exe: $(patsubst %.c,%.o,$(TEST))
	gcc $(FLAGS) -lcunit $^ -o $@

run: app.exe
	./app.exe

runTests: CUnitTests.exe
	./CUnitTests.exe

clean: 
	rm *.o *.exe *.d *.out

%.o: %.c 
	gcc $(FLAGS) -c -MD $<

CUnitTests.o: tests/UnitTests/*.c
	gcc $(FLAGS) -c -MD $<

include $(wildcard *.d tests/UnitTests/*.d)
