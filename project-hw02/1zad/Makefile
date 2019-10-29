SRC=src/cmplx.c src/io.c
OBJ=$(patsubst %c, %o, $(SRC))
INC=inc/
CFLAGS=-I $(INC)

all: exe/test01.elf exe/test03.elf

exe/%.elf: src/%.o $(OBJ)
	gcc $< $(OBJ) -o $@ -lm

%.o: %.c
	gcc -c $^ -I $(INC) -o $@

clean:
	rm -f exe/test01.elf src/test01.o exe/test03.elf src/test03.o

test: all 
	./exe/test01.elf;./exe/test03.elf
