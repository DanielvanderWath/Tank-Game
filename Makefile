
SOURCE:= bullet.cpp \
	 baddy.cpp \
	 formation.cpp \
	 tank.cpp \
	 explosion.cpp \
	 main.cpp 

MYLIBPATH = ../mylib

MYLIB:= $(MYLIBPATH)/errorcheck.cpp $(MYLIBPATH)/mylib.cpp 

LIBS:= -lGL -lSDL -I$(MYLIBPATH)

tank :  tank.cpp bullet.cpp baddy.cpp formation.cpp explosion.cpp main.cpp
	g++ -o tank -g -Wno-write-strings $(SOURCE) $(MYLIB) $(LIBS)


