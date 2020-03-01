.PHONY: run

GCC_ARGS=
OUTFILE=game.out

build:
	gcc -Wall include/*.c main.c -o $(OUTFILE) -I include/ $(GCC_ARGS)

build.xterm: GCC_ARGS=-DXTERM=1
build.xterm: build

run: build
	./$(OUTFILE)

run.xterm: build.xterm
	./$(OUTFILE)
