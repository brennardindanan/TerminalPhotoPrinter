CC = gcc
CFLAGS = -Wall

TARGET = a2

SRC = brennard_a2.c camera.o

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

