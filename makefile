CC = g++

RGB_LIB_DISTRIBUTION=../rpi-rgb-led-matrix
RGB_LIB_DIR=$(RGB_LIB_DISTRIBUTION)/lib
RGB_LIB_NAME=rgbmatrix

# our directories
SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = bin

# general, compiler, and linker flags
# march=native and -mtune are for aarm64
# -flto=2
CFLAGS = -c -Wall -Werror -O3 -march=native -mtune=native -flto=2 -g -Wextra -Wno-unused-parameter
LDFLAGS = -march=native -mtune=native -flto=2 -L$(RGB_LIB_DIR) -l$(RGB_LIB_NAME) -lrt -lm -lpthread
LDLIBS =

INCLUDES = -I $(RGB_LIB_DISTRIBUTION)/include -I include

# objects
OBJS := $(BUILD_DIR)/*.o

main: $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(OBJS) -o main $(LDFLAGS) $(LDLIBS)
	@echo "built main"

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CC) -c $< $(CFLAGS) $(INCLUDES) $(LDFLAGS) $(LDLIBS) -o $@

clean:
	rm -f $(BUILD_DIR)/*.o
	rm main
