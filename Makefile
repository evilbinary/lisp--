##########################################################################################
# Project: Lisp++ 
# # Makefile Evilbinary 小E
# # Mail:rootntsd@gmail.com
# ##########################################################################################
CPP = gcc
CXXFLAGS = -g  -O2
LDFLAGS =

LIBS = 
INCS = 
SRCS = $(wildcard *.c )
OBJS = $(patsubst %.c,%.o,$(SRCS))

TARGET=lisp--
.PHONY :all test clean run

all:$(TARGET)

run:$(TARGET) lib.lisp
	./$(TARGET) --load lib.lisp
test:$(TARGET) test.l
	./$(TARGET) ./test.l
clean:
	rm -rf *.o $(TARGET) *.exe

$(TARGET):$(OBJS)
	$(CPP) -o $(TARGET) $(OBJS) $(CXXFLAGS)

.cpp.o:
	$(CPP) -c -o $@ $< $(LIBS) $(INCS) $(CXXFLAGS)
