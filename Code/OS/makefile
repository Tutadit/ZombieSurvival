os.img: os.prg
	burnroms

os.prg: start.o init.o main.o              # uncomment below for linking libc
	ld -o os.prg start.o init.o main.o # crt0.o libc.a

start.o: start.s
	gen -L2 start.s

init.o: init.c
	cc68x -c init.c

main.o: main.c
	cc68x -c main.c
