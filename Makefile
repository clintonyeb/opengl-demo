all: out
clean:
        rm -f out *.o
.PHONY: all clean

CXX = gcc
CPPFLAGS =
CXXFLAGS = -std=c++11 -Wall -Wextra -g
LIBS = -lglfw -lGL -lGLU -lGLEW -lglut -lm -lX11 -lXxf86vm -lXrandr -pthread -lXi -ldl
LDFLAGS = -I./include -I./deps

out: main.o
        $(CXX) $(LDFLAGS) -o $@ $^ $(LIBS)