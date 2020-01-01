CFILES := $(wildcard *.c)
FLAGS := -Wall

build: $(patsubst %.c,%.o,$(CFILES))
	gcc $(FLAGS) $^ -o app.exe

run: build
	./app.exe in.txt

clean:
	rm *.o *.exe *.d *.out

%.o: %.c
	gcc $(FLAGS) -c -MD $<

include $(wildcard *.d)
