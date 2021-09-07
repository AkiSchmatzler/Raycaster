CC = g++
IFLAGS = -lsfml-graphics -lsfml-window -lsfml-system
SRC = src/


main :
	$(CC) -c $(SRC)Grid.cpp
	$(CC) -c $(SRC)Rays.cpp -lsfml-graphics
	$(CC) -c $(SRC)Player.cpp -lsfml-graphics
	$(CC) -o main $(SRC)main.cpp $(IFLAGS) $(SRC)Player.cpp $(SRC)Rays.cpp $(SRC)Grid.cpp
	mkdir obj/
	mkdir bin/
	mv *.o obj/
	mv main bin/


.PHONY : clean

clean: 
	rm -rf bin/ obj/