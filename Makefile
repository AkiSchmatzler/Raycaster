CC = g++
IFLAGS = -lsfml-graphics -lsfml-window -lsfml-system


main :
	g++ -c Player.cpp -lsfml-graphics
	g++ -c Rays.cpp -lsfml-graphics
	$(CC) -o grid grid.cpp $(IFLAGS) Player.cpp Rays.cpp

.PHONY : clean

clean: 
	rm grid *.o