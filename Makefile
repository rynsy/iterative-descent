topspin:
	g++ -std=c++11 -g main.cpp topspin.cpp randomizer.cpp node.cpp ida.cpp -o topspin

clean:
	rm -f topspin *.o *.s
