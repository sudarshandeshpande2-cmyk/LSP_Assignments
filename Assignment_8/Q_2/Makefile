CC = gcc

CFLAGS = -Wall -Wextra -O2

TARGET = app

SRC = main.c 

$(TARGET) : $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
	