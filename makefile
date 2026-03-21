CC = g++
#Libary Folder 
CPR_LIB_DISTRIBUTION=./lib/cpr

CPR_LIB_DIR=$(CPR_LIB_DISTRIBUTION)/lib
CPR_LIB_NAME=cppRequest
#include directories
INCLUDES = -I$(CPR_LIB_DISTRIBUTION)/include

#general, compiler, and linker flags
# march=native and -mtune are for aarm64
# -flto=thin
CFLAGS = -Wall -O3 -march=native -mtune=native -flto=2 -g -Wextra -Wno-unused-parameter
LDFLAGS = -march=native -mtune=native -flto=2 -L$(CPR_LIB_DIR) -lrt -lm -lpthread -lcpr -lcurl -lssl -lcrypto
LDLIBS = 

main: main.o
	$(CC) main.o -o main $(LDFLAGS) $(LDLIBS)

main.o: main.cpp
	$(CC) $(INCLUDES) $(CFLAGS) -c -o main.o main.cpp

clean: 
	rm -f main.o 
	rm -f main
