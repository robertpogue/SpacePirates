# prefix set to appropriate directory for package management when "make" 
# is called from debian build, see debian/rules
prefix=/usr/local
bindir=$(prefix)/bin
sharedir=$(prefix)/share

all: game

game: Block.o GameObject.o Gold.o Graphics.o Image.o Input.o Level.o main.o Platform.o RigidBody.o Ship.o Time.o
	g++ -g -o spacepirates Block.o GameObject.o Gold.o Graphics.o Image.o Input.o Level.o main.o Platform.o RigidBody.o Ship.o Time.o -L/usr/local/lib -lSDL2 -lSDL2_image
gameWithLibs: Block.o GameObject.o Gold.o Graphics.o Image.o Input.o Level.o main.o Platform.o RigidBody.o Ship.o Time.o
	g++ -g -o gameWithLibs Block.o GameObject.o Gold.o Graphics.o Image.o Input.o Level.o main.o Platform.o RigidBody.o Ship.o Time.o -lGL -Wl,-rpath,'$ORIGIN/lib' -Llib -l:libSDL-1.2.so.0 -l:libSDL_image-1.2.so.0 -l:libSDL_ttf-2.0.so.0

Block.o: Block.cpp Block.h Point.h Graphics.h
	g++ -c -g Block.cpp -o Block.o

GameObject.o:
	g++ -c -g GameObject.cpp -o GameObject.o

Gold.o:
	g++ -c -g Gold.cpp -o Gold.o
	
Graphics.o:
	g++ -c -g Graphics.cpp -o Graphics.o -I/usr/local/include/SDL2

Image.o:
	g++ -c -g Image.cpp -o Image.o -std=c++0x -I/usr/local/include/SDL2

Input.o:
	g++ -c -g Input.cpp -o Input.o -I/usr/local/include/SDL2

Level.o:
	g++ -c -g Level.cpp -o Level.o -std=c++0x -I/usr/local/include/SDL2

main.o:
	g++ -c -g main.cpp -o main.o -std=c++0x -I/usr/local/include/SDL2

Platform.o:
	g++ -c -g Platform.cpp -o Platform.o

RigidBody.o:
	g++ -c -g RigidBody.cpp -o RigidBody.o
	
Ship.o:
	g++ -c -g Ship.cpp -o Ship.o -std=c++0x

Time.o:
	g++ -c -g Time.cpp -o Time.o -I/usr/local/include/SDL2

install: all
	install spacepirates $(DESTDIR)$(bindir)
	install a.png $(DESTDIR)$(sharedir)/spacepirates

clean:
	rm -f game *.o
