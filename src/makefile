# OR use `g++ -Wall *.cpp -o connectfour.out -std=c17`
# OR use `g++ *.cpp -o connectfour.out -std=c17`


OBJS	= main.o autoc4player.o connect4board.o connect4move.o connect4state.o gamemove.o gamestate.o humanplayer.o player.o players.o
SOURCE	= main.cpp autoc4player.cpp connect4board.cpp connect4move.cpp connect4state.cpp gamemove.cpp gamestate.cpp humanplayer.cpp player.cpp players.cpp
HEADER	= gameboard.h autoc4player.h connect4board.h connect4move.h connect4state.h gamemove.h gamestate.h humanplayer.h player.h players.h
OUT	= connectfour.out
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp -std=c17

autoc4player.o: autoc4player.cpp
	$(CC) $(FLAGS) autoc4player.cpp -std=c17

connect4board.o: connect4board.cpp
	$(CC) $(FLAGS) connect4board.cpp -std=c17

connect4move.o: connect4move.cpp
	$(CC) $(FLAGS) connect4move.cpp -std=c17

connect4state.o: connect4state.cpp
	$(CC) $(FLAGS) connect4state.cpp -std=c17

gamemove.o: gamemove.cpp
	$(CC) $(FLAGS) gamemove.cpp -std=c17

gamestate.o: gamestate.cpp
	$(CC) $(FLAGS) gamestate.cpp -std=c17

humanplayer.o: humanplayer.cpp
	$(CC) $(FLAGS) humanplayer.cpp -std=c17

player.o: player.cpp
	$(CC) $(FLAGS) player.cpp -std=c17

players.o: players.cpp
	$(CC) $(FLAGS) players.cpp -std=c17


clean:
	rm -f $(OBJS) $(OUT) connectfour

run: $(OUT)
	./$(OUT)
