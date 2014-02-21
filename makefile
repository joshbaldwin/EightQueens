TARGET = EightQueens

all: $(TARGET)

$(TARGET): main.o Population.o Organism.o
	g++ main.o Population.o Organism.o -o $@

main.o: main.cpp
	g++ -c main.cpp

Population.o: Population.cpp
	g++ -c Population.cpp

Organism.o: Organism.cpp
	g++ -c Organism.cpp

clean:
	rm *.o && rm $(TARGET)

