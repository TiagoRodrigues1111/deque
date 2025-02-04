CC = gcc
CFLAGS = -Wall -Wextra -g
OBJ = simplemain.o deque.o
OBJ_ll = simplemain.o deque_ll.o
TARGET = deque_test

# Default target
all: $(TARGET)

run: $(TARGET)
	./$(TARGET)



$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)


deque_ll: $(OBJ_ll)
	$(CC) $(OBJ_ll) -o $(TARGET)






simplemain.o: simplemain.c deque.h
	$(CC) $(CFLAGS) -c simplemain.c





deque.o: deque.c deque.h
	$(CC) $(CFLAGS) -c deque.c


deque_ll.o: deque_ll.c deque.h
	$(CC) $(CFLAGS) -c deque_ll.c






clean:
	rm -f $(OBJ) $(OBJ_ll) $(TARGET)



rebuild: clean all
