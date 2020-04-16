# prefix set to appropriate directory for package management when "make" 
# is called from debian build, see debian/rules
prefix=/usr/local
bindir=$(prefix)/bin
sharedir=$(prefix)/share

all: game

game: GameObject.o Graphics.o Input.o Level.o main.o RigidBody.o Ship.o Time.o Image.o Color.o
	g++ -g -o spacepirates GameObject.o Graphics.o Input.o Level.o main.o RigidBody.o Ship.o Time.o Image.o Color.o -L/usr/lib -lSDL2 -lSDL2_image -lSDL2_ttf
gameWithLibs: GameObject.o Graphics.o Input.o Level.o main.o RigidBody.o Ship.o Time.o Image.o Color.o
	g++ -g -o gameWithLibs GameObject.o Graphics.o Input.o Level.o main.o RigidBody.o Ship.o Time.o Image.o Color.o -lGL -Wl,-rpath,'$ORIGIN/lib' -Llib -l:libSDL-1.2.so.0 -l:libSDL_image-1.2.so.0 -l:libSDL_ttf-2.0.so.0

GameObject.o:
	g++ -c -g GameObject.cpp -o GameObject.o -std=c++0x -I/usr/include/SDL2

Graphics.o:
	g++ -c -g Graphics.cpp -o Graphics.o -std=c++0x -I/usr/include/SDL2

Input.o:
	g++ -c -g Input.cpp -o Input.o -I/usr/include/SDL2

Level.o:
	g++ -c -g Level.cpp -o Level.o -std=c++0x -I/usr/include/SDL2

main.o:
	g++ -c -g main.cpp -o main.o -std=c++0x -I/usr/include/SDL2

RigidBody.o:
	g++ -c -g RigidBody.cpp -o RigidBody.o
	
Ship.o:
	g++ -c -g Ship.cpp -o Ship.o -std=c++0x -I/usr/include/SDL2

Time.o:
	g++ -c -g Time.cpp -o Time.o -I/usr/include/SDL2

Image.o:
	g++ -std=c++11 -c -g Image.cpp -o Image.o -I/usr/include/SDL2

Color.o:
	g++ -c -g Color.cpp -o Color.o -I/usr/include/SDL2

install: all
	install spacepirates $(DESTDIR)$(bindir)
	install a.png $(DESTDIR)$(sharedir)/spacepirates

clean:
	rm -f game *.o
