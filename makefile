CC = g++

RGB_LIB_DISTRIBUTION=../rpi-rgb-led-matrix

RGB_LIB_DIR=$(RGB_LIB_DISTRIBUTION)/lib
RGB_LIB_NAME=rgbmatrix

#include directories
INCLUDES = -I $(RGB_LIB_DISTRIBUTION)/include

#general, compiler, and linker flags
# march=native and -mtune are for aarm64
# -flto=thin
CFLAGS = -Wall -O3 -march=native -mtune=native -flto=2 -g -Wextra -Wno-unused-parameter
LDFLAGS = -march=native -mtune=native -flto=2 -L$(RGB_LIB_DIR) -l$(RGB_LIB_NAME) -lrt -lm -lpthread
LDLIBS = 

main: main.o
	$(CC) main.o -o main $(LDFLAGS) $(LDLIBS)

main.o: main.cpp
	$(CC) $(INCLUDES) $(CFLAGS) -c -o main.o main.cpp

clean: 
	rm -f main.o 
	rm -f main
