# the compiler: gcc for C program, define as g++ for C++
CC = gcc

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -g -Wall

# the build target executable:
TARGET = lsmd

all: $(TARGET)

$(TARGET): lsmd.c node.h pretty.h arguments.h
	$(CC) $(CFLAGS) -o $(TARGET) arguments.h node.h pretty.h lsmd.c -lvlc

clean:
	$(RM) $(TARGET)
