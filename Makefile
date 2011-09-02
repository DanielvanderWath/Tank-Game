
SOURCE:= bullet.cpp \
	 baddy.cpp \
	 formation.cpp \
	 tank.cpp \
	 main.cpp 

MYLIBPATH = ../mylib

MYLIB:= $(MYLIBPATH)/errorcheck.cpp $(MYLIBPATH)/mylib.cpp 

LIBS:= -lGL -lSDL -I$(MYLIBPATH)

tank :  tank.cpp bullet.cpp baddy.cpp formation.cpp main.cpp
	g++ -g -o tank -Wno-write-strings $(SOURCE) $(MYLIB) $(LIBS)


