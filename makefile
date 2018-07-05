hellomake: *.cpp
	g++ -c -g -pthread main.cpp
	g++ *.o -lpthread -o interference -lsfml-graphics -lsfml-window -lsfml-system
