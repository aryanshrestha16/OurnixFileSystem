#
# Macros Definition
#
CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -fstack-protector-all -Werror

all: public01.x public02.x public03.x public04.x public05.x public06.x public07.x public08.x public09.x public10.x public11.x public12.x public13.x public14.x public15.x

public01.x: public01.o ournix.o
	$(CC) public01.o ournix.o -o public01.x

public02.x: public02.o ournix.o
	$(CC) public02.o ournix.o -o public02.x

public03.x: public03.o ournix.o
	$(CC) public03.o ournix.o -o public03.x

public04.x: public04.o ournix.o
	$(CC) public04.o ournix.o -o public04.x

public05.x: public05.o ournix.o
	$(CC) public05.o ournix.o -o public05.x

public06.x: public06.o ournix.o
	$(CC) public06.o ournix.o -o public06.x

public07.x: public07.o ournix.o
	$(CC) public07.o ournix.o -o public07.x

public08.x: public08.o ournix.o
	$(CC) public08.o ournix.o -o public08.x

public09.x: public09.o ournix.o
	$(CC) public09.o ournix.o -o public09.x

public10.x: public10.o ournix.o driver.o
	$(CC) public10.o ournix.o driver.o -o public10.x

public11.x: public11.o ournix.o
	$(CC) public11.o ournix.o -o public11.x

public12.x: public12.o ournix.o
	$(CC) public12.o ournix.o -o public12.x

public13.x: public13.o ournix.o
	$(CC) public13.o ournix.o -o public13.x

public14.x: public14.o ournix.o memory-checking.o
	$(CC) public14.o ournix.o memory-checking.o -o public14.x

public15.x: public15.o ournix.o memory-checking.o
	$(CC) public15.o ournix.o  memory-checking.o -o public15.x

ournix.o: ournix.c ournix.h
	$(CC) $(CFLAGS) -c ournix.c

public01.o: public01.c ournix.h
	$(CC) $(CFLAGS) -c public01.c

public02.o: public02.c ournix.h
	$(CC) $(CFLAGS) -c public02.c

public03.o: public02.c ournix.h
	$(CC) $(CFLAGS) -c public03.c

public04.o: public04.c ournix.h
	$(CC) $(CFLAGS) -c public04.c

public05.o: public05.c ournix.h
	$(CC) $(CFLAGS) -c public05.c

public06.o: public06.c ournix.h
	$(CC) $(CFLAGS) -c public06.c

public07.o: public07.c ournix.h
	$(CC) $(CFLAGS) -c public07.c

public08.o: public08.c ournix.h
	$(CC) $(CFLAGS) -c public08.c

public09.o: public09.c ournix.h
	$(CC) $(CFLAGS) -c public09.c

public10.o: public10.c ournix.h driver.h
	$(CC) $(CFLAGS) -c public10.c

public11.o: public11.c ournix.h
	$(CC) $(CFLAGS) -c public11.c

public12.o: public12.c ournix.h
	$(CC) $(CFLAGS) -c public12.c

public13.o: public13.c ournix.h
	$(CC) $(CFLAGS) -c public13.c

public14.o: public14.c ournix.h memory-checking.h
	$(CC) $(CFLAGS) -c public14.c

public15.o: public15.c ournix.h memory-checking.h
	$(CC) $(CFLAGS) -c public15.c

clean:
	-rm public01.o public01.x public02.o public02.x public03.o public03.x public04.o public04.x public05.o public05.x public06.o public06.x public07.o public07.x public08.o public08.x public09.o public09.x public10.o public10.x public11.o public11.x public12.o public12.x public13.o public13.x public14.o public14.x public15.o public15.x
