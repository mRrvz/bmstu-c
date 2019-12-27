CFILES := src/dirname.c
FLAGS := -Wall -O2 -std=c99

ifeq (dynamic,$(firstword $(MAKECMDGOALS)))
	FLAGS := $(FLAGS) -fPIC
endif

static: static_lib
	gcc $(FLAGS) src/main.c -L. -ldirname -o app.exe -ldl

dynamic: dynamic_lib
	gcc $(FLAGS) src/main.c libdirname.so '-Wl,-rpath,$$ORIGIN/' -o app.exe -ldl

dynamic_rt: dynamic_lib
	gcc $(FLAGS) src/main.c '-Wl,-rpath,$$ORIGIN/' -o app.exe -ldl

static_lib: $(patsubst src/%.c,./%.o,$(CFILES))
	ar cr libdirname.a $^ 

dynamic_lib: $(patsubst src/%.c,./%.o,$(CFILES))
	gcc -shared $^ -o libdirname.so

run: app.exe
	./app.exe

clean:
	sudo rm *.o *.exe *.d *.out *.so *.a /usr/lib/libdirname.so

%.o: src/%.c
	gcc $(FLAGS) -c -MD $<

include $(wildcard *.d)
