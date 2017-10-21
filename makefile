install:
	g++ -c *.cpp
	g++ -o app *.o -lGL -lGLEW -lglfw
	rm *.o
