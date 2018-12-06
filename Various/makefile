CC=gcc
CFLAGS=-Wall -std=c99

PROGS = dynarr dynarrt lldeq lldeqt clldeq

all: ${PROGS}


dynarr: dynamicArray.o dynamicArrayMain.o
	gcc -g -Wall -std=c99 -o dynarr dynamicArray.o dynamicArrayMain.o
dynarrt: dynamicArray.o dynamicArrayMain_timing.o
	gcc -g -Wall -std=c99 -o dynarrt dynamicArray.o dynamicArrayMain_timing.o
dynamicArray.o: dynamicArray.c dynArray.h
	gcc -g -Wall -std=c99 -c dynamicArray.c
dynamicArrayMain_timing.o: dynamicArrayMain_timing.c dynArray.h
	gcc -g -Wall -std=c99 -c dynamicArrayMain_timing.c
dynamicArrayMain.o: dynamicArrayMain.c dynArray.h
	gcc -g -Wall -std=c99 -c dynamicArrayMain.c

lldeq: linkedList.o linkedListMain.o
	gcc -g -Wall -std=c99 -o lldeq linkedList.o linkedListMain.o
lldeqt: linkedList.o linkedListMain_timing.o
	gcc -g -Wall -std=c99 -o lldeqt linkedList.o linkedListMain_timing.o
linkedList.o: linkedList.c linkedList.h
	gcc -g -Wall -std=c99 -c linkedList.c
linkedListMain.o: linkedListMain.c linkedList.h
	gcc -g -Wall -std=c99 -c linkedListMain.c
linkedListMain_timing.o: linkedListMain_timing.c linkedList.h
	gcc -g -Wall -std=c99 -c linkedListMain_timing.c

clldeq: circularList.o circularListMain.o
	gcc -g -Wall -std=c99 -o clldeq circularList.o circularListMain.o
circularList.o: circularList.c circularList.h
	gcc -g -Wall -std=c99 -c circularList.c
circularListMain.o: circularListMain.c circularList.h
	gcc -g -Wall -std=c99 -c circularListMain.c

clean:
	-rm *.o

cleanall: clean
	-rm ${PROGS}
