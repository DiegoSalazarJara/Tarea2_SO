CC = g++
CFLAGS = -std=c++11 -Wall -Wextra -O3
LIBS = `pkg-config --cflags --libs opencv4`
TARGET = tarea2

all: $(TARGET)

$(TARGET): tarea2.cpp
	$(CC) $(CFLAGS) tarea2.cpp -o $(TARGET) $(LIBS)

.PHONY: clean

clean:
	rm -f $(TARGET)
