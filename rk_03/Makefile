CFILES := $(wildcard *.c)
FLAGS := -Wall -g -std=c99 

build: $(patsubst %.c,%.o,$(CFILES))
	gcc $(FLAGS) $(MAKEKEY) $^ -o app.exe

run: build
	./app.exe in.txt

clean: 
	rm *.o *.exe *.d *.out

%.o: %.c 
	gcc $(FLAGS) -c -MD $<

include $(wildcard *.d)
