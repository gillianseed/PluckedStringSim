all: CircularBuffer.o StringSound.o KSGuitarSim.o
	g++ -o KSGuitarSim CircularBuffer.o StringSound.o KSGuitarSim.o -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

CircularBuffer.o: CircularBuffer.cpp CircularBuffer.hpp
	g++ -c CircularBuffer.cpp

StringSound.o: StringSound.cpp StringSound.hpp
	g++ -c StringSound.cpp

KSGuitarSim.o: KSGuitarSim.cpp
	g++ -c KSGuitarSim.cpp

KSGuitarSim: CircularBuffer.o StringSound.o KSGuitarSim.o
	g++ -o CircularBuffer.o StringSound.o KSGuitarSim.o KSGuitarSim

clean:
	rm *.o KSGuitarSim
