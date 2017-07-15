exec.exe: main.o Book.o Animation.o Collision.o Entity.o Game.o State.o MenuState.o PlayState.o
	g++ -std=c++11 main.o Book.o Collision.o Animation.o Entity.o Game.o State.o MenuState.o PlayState.o -o exec.exe -lsfml-graphics -lsfml-window -lsfml-system

main.o: main.cpp
	g++ -std=c++11 -c main.cpp

Book.o: Book.cpp
	g++ -std=c++11 -c Book.cpp

Collision.o: Collision.cpp
	g++ -std=c++11 -c Collision.cpp

Entity.o: Entity.cpp
	g++ -std=c++11 -c Entity.cpp

Game.o: Game.cpp
	g++ -std=c++11 -c Game.cpp

State.o: State.cpp
	g++ -std=c++11 -c State.cpp

MenuState.o: MenuState.cpp
	g++ -std=c++11 -c MenuState.cpp

PlayState.o: PlayState.cpp
	g++ -std=c++11 -c PlayState.cpp

Animation.o: Animation.cpp
	g++ -std=c++11 -c Animation.cpp
