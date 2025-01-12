CXX = g++
CXXFLAGS = -std=c++11 -I./include -I/usr/include/SFML -L/usr/lib -lsfml-graphics -lsfml-window -lsfml-system
SOURCES = game.cpp element.cpp personnage.cpp plateforme.h drapeau.cpp danger.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = plateforme

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) -o $@ $^ $(CXXFLAGS)

%.o: %.cpp
	$(CXX) -c $< $(CXXFLAGS)

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

run: $(EXECUTABLE)
	./$(EXECUTABLE)

.PHONY: all clean run