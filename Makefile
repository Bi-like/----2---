CC = gcc
LD = gcc
CCFLAGS = -Wall -g -std=c99
LDFLAGS =
TARGET = merge_prog
SOURCES = main.c merge.c
OBJECTS = main.o merge.o

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(LD) $(LDFLAGS) -o $(TARGET) $(OBJECTS)

main.o: main.c merge.h
	$(CC) $(CCFLAGS) -c main.c

merge.o: merge.c merge.h
	$(CC) $(CCFLAGS) -c merge.c

clean:
	rm -f $(OBJECTS) $(TARGET)

rebuild: clean all