CC = gcc
LD = gcc
CCFLAGS = -Wall -g -std=c99
LDFLAGS =
TARGET = mergesort_prog
SOURCES = main.c merge_sort.c
OBJECTS = main.o merge_sort.o

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(LD) $(LDFLAGS) -o $(TARGET) $(OBJECTS)

main.o: main.c merge_sort.h
	$(CC) $(CCFLAGS) -c main.c

merge_sort.o: merge_sort.c merge_sort.h
	$(CC) $(CCFLAGS) -c merge_sort.c

clean:
	rm -f $(OBJECTS) $(TARGET)

rebuild: clean all