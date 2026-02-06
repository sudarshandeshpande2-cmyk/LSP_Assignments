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

help:
	@echo "Usage Instructions:"
	@echo "make or make all  -> Build the application"
	@echo "make run          -> Run the application"
	@echo "make clean        -> Remove compiled binary"