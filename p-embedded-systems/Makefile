CC=gcc
CFLAGS=-c -Wall
BUILD_DIR=build
SRC_DIR=src

all: dirs $(BUILD_DIR)/main.o $(BUILD_DIR)/circular_buffer.o
	$(CC) $(BUILD_DIR)/main.o $(BUILD_DIR)/circular_buffer.o -o main.out

run: all
	./main.out

dirs:
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/main.o: $(SRC_DIR)/main.c
	$(CC) $(CFLAGS) $(SRC_DIR)/main.c -o $(BUILD_DIR)/main.o

$(BUILD_DIR)/circular_buffer.o: $(SRC_DIR)/circular_buffer.c
	$(CC) $(CFLAGS) $(SRC_DIR)/circular_buffer.c -o $(BUILD_DIR)/circular_buffer.o

clean:
	$(RM) -r $(BUILD_DIR)
	$(RM) *.out

