CC = gcc
CFLAGS = -Wall -Wextra -O2

TARGET = app
OBJ = main.o helper.o

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

main.o: main.c helper.h
	$(CC) $(CFLAGS) -c main.c

helper.o: helper.c helper.h
	$(CC) $(CFLAGS) -c helper.c

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f *.o $(TARGET)
