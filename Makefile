### TEST MAKEFILE 
### Copyright 2023 Peregrin

sources = $(wildcard src/*.c)
objects = $(subst src/,build/,$(sources:.c=.o))
tests   = $(wildcard tst/*.c)
t_obj   = $(subst tst/,build/,$(tests:.c=.o)) $(subst build/left_right.o,,$(objects))

app: check ${objects} | build
	gcc ${objects} -o app

test-suite: $(t_obj) | build
	gcc $(t_obj) -o test-suite

build/%.o : tst/%.c | build
	gcc -c $< -o $@

build/%.o : src/%.c | build
	gcc -c $< -o $@   

build:
	mkdir build

check: test-suite
	@echo "Run test-suite:" 
	@./test-suite

### ABSTRACT
.PHONY : clean
.PHONY : vars

vars:
	@echo "objects = ${objects}"
	@echo "sources = ${sources}"
	@echo "tests = $(tests)"
	@echo "t_obj = $(t_obj)"

clean: | build
	@rm -rf build
	@rm app
	@rm test-suite
	@echo "Directory cleaned!"
