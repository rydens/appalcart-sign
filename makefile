CC = g++
CFLAGS = -c -std=c++17 -O2 -Wall -Werror
OBJS = sign.o

.cpp.o:
	$(CC) $(CFLAGS) -o $@ $<

sign: $(OBJS)
	$(CC) $(OBJS) -o sign

sign.o: sign.cpp

clean:
	rm sign *.o
