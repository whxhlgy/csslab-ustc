all:
	gcc hello.c

step:
	cpp hello.c -o hello.i
	/usr/lib/gcc/x86_64-linux-gnu/11/cc1 hello.i -o hello.s
	as hello.s -o hello.o
	ld hello.o -e main -o hello.out

notmain:
	#first compile the lib
	gcc -c mini-lib.c -g -fno-builtin -fno-stack-protector
	gcc -c notmain.c -g -fno-builtin -fno-stack-protector
	ld notmain.o mini-lib.o -e notmain -o notmain.out -g

clean:
	rm -rf hello.i hello.s hello.o a.out hello.out
	rm -rf nolib.i nolib.s nolib.o nolib.out

