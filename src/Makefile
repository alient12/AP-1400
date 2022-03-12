CXX = g++
CXXFLAGS = -std=c++2a -Wall -I../include
OBJS = server.o client.o main.o crypto.o
DEPS = server.h client.h crypto.h
TARGET = main

%.o: %.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS)
#	rm $(OBJS)
	./$(TARGET).exe

clean:
	rm $(TARGET)
	
clear:
	rm $(OBJS)