CC = g++

RGB_LIB_DISTRIBUTION=../rpi-rgb-led-matrix

RGB_LIB_DIR=$(RGB_LIB_DISTRIBUTION)/lib
RGB_LIB_NAME=rgbmatrix

#include directories
INCLUDES = -I $(RGB_LIB_DISTRIBUTION)/include -I include

OBJS = main.o render.o module.o

#general, compiler, and linker flags
# march=native and -mtune are for aarm64
# -flto=thin
CFLAGS = -Wall -Werror -O3 -march=native -mtune=native -flto=2 -g -Wextra -Wno-unused-parameter
LDFLAGS = -march=native -mtune=native -flto=2 -L$(RGB_LIB_DIR) -l$(RGB_LIB_NAME) -lrt -lm -lpthread
LDLIBS = 

.cpp.o:
	$(CC) $(INCLUDES) $(CFLAGS) -o $@ $<

main: $(OBJS)
	$(CC) $(OBJS) -o sign $(LDFLAGS) $(LDLIBS)

main.o: main.cpp

render.o: render.cpp

module.o: module.cpp 

clean: 
	rm *.o sign
