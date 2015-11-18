#Location and name of your application
OUT = bin/mvfs

#Compiler (i.e. g++ for C++, or gcc for C)
CXX = g++
CC  = gcc

#Directory for includes (headers, etc.)
IDIR = src

#Directory where the .o files will be placed
OBJ_DIR = obj

#Directory where the source files are located
SRC_DIR = src

#Path to includes (begin each entry with -I)
LOCAL_C_INCLUDES = $(patsubst %, -I%, $(shell /usr/bin/find $(SRC_DIR) -type d))
INC =  $(LOCAL_C_INCLUDES)

#Begin each directory location with -L and each flag with -l
LIBS = -lm

CC_SRC = $(shell find $(SRC_DIR) -name '*.c')
CXX_SRC = $(shell find $(SRC_DIR) -name '*.cpp')

#A list of your expected object files (typically, name one for each source file)
CC_OBJS = $(patsubst $(SRC_DIR)%, %, $(patsubst %.c, %.o, $(CC_SRC)))
CXX_OBJS = $(patsubst $(SRC_DIR)%, %, $(patsubst %.cpp, %.o, $(CXX_SRC)))

OBJ_FOLDERS = $(patsubst $(SRC_DIR)%, $(OBJ_DIR)%, $(shell /usr/bin/find $(SRC_DIR) -type d))

#Only change stuff below this line  if you're aware of what you're doing
OBJS = $(patsubst %,$(OBJ_DIR)%,$(CC_OBJS))
OBJS += $(patsubst %,$(OBJ_DIR)%,$(CXX_OBJS))

CFLAGS := -O2 -DLINUX_PLATFORM
CXXFLAGS := -O2 -std=gnu++11 -DLINUX_PLATFORM

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_FOLDERS)
	$(CC) -c $(INC) -o $@ $< $(CFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(OBJ_FOLDERS)
	$(CXX) -c $(INC) -o $@ $< $(CXXFLAGS)

$(OUT): $(OBJS)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)

.PHONY: clean build all install run

clean:
	rm -f $(OBJS) $(OUT)
	echo "Clean done!"

build:
	mkdir -p bin
	make bin/mvfs
	@echo "Build done!"

all:
	make clean
	make build

install:
	make all
	sudo cp $(OUT) /usr/bin/mvfs
	@echo "Install done!"

run:
	make build
	bin/mvfs
