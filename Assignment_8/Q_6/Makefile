CC = gcc
CFLAGS = -Wall -Wextra -O2 -fPIC

TARGET = app
LIB = libmath.so

OBJ = math.o
APP_OBJ = main.o

.PHONY: all so app run clean

all: so app

# ---------- Build Shared Library ----------
so: $(LIB)

$(LIB): $(OBJ)
	$(CC) -shared -o $(LIB) $(OBJ)

# ---------- Compile PIC Object ----------
math.o: math.c math.h
	$(CC) $(CFLAGS) -c math.c

main.o: main.c math.h
	$(CC) -Wall -Wextra -O2 -c main.c

# ---------- Link Application ----------
app: main.o $(LIB)
	$(CC) main.o -L. -lmath -o $(TARGET)

# ---------- Run Application ----------
run: app
	LD_LIBRARY_PATH=. ./$(TARGET)

# ---------- Clean ----------
clean:
	rm -f *.o *.so $(TARGET)
