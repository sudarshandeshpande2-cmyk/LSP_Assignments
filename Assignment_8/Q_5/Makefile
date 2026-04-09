CC = gcc
CFLAGS = -Wall -Wextra -O2

TARGET = app
LIB = libmath.a

OBJ = math.o
APP_OBJ = main.o

.PHONY: all lib app clean

all: lib app

# -------- Build Static Library --------
lib: $(LIB)

$(LIB): $(OBJ)
	ar rcs $(LIB) $(OBJ)

# -------- Compile Object Files --------
math.o: math.c math.h
	$(CC) $(CFLAGS) -c math.c

main.o: main.c math.h
	$(CC) $(CFLAGS) -c main.c

# -------- Link Application --------
app: $(APP_OBJ) $(LIB)
	$(CC) $(APP_OBJ) -L. -lmath -o $(TARGET)

# -------- Clean --------
clean:
	rm -f *.o *.a $(TARGET)
