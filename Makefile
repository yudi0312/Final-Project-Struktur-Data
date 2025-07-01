CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
TARGET = transportation_system
SOURCES = main.cpp TransportationSystem.cpp

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

clean:
	rm -f $(TARGET)
	rm -f visualizer

run: $(TARGET)
	./$(TARGET)

.PHONY: clean run
