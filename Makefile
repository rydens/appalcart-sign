CFLAGS = -std=c++17 -O2 -Wall -Werror
OBJS = Fetcher.o
CC = g++

.cpp.o:
	$(CC) -c $(CFLAGS) -o $@ $<

all:
	make fetcher

fetcher: $(OBJS)
	$(CC) $(OBJS) -o fetcher -lcpr -lcurl

Fetcher.o: Fetcher.cpp Fetcher.h

clean:
	rm fetcher *.o
