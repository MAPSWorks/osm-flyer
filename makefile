CC=g++
CFLAGS=-Wall
LIBS=-lsfml-graphics -lsfml-window -lsfml-system -lGLU
INCPATH=
SRCDIR=src/

all: osm-flyer

osm-flyer: $(SRCDIR)osm-flyer.cpp FlyerWindow.o 
	$(CC) $(CFLAGS) -o osm-flyer FlyerWindow.o FlyerCamera.o FlyerMap.o FlyerMapBuilder.o $(SRCDIR)osm-flyer.cpp $(LIBS) $(INCPATH) 

FlyerWindow.o: $(SRCDIR)FlyerWindow.cpp $(SRCDIR)FlyerWindow.hpp FlyerCamera.o FlyerMap.o
	$(CC) $(CFLAGS) -c $(SRCDIR)FlyerWindow.cpp $(LIBS) $(INCPATH)

FlyerCamera.o: $(SRCDIR)FlyerCamera.cpp $(SRCDIR)FlyerCamera.hpp
	$(CC) $(CFLAGS) -c $(SRCDIR)FlyerCamera.cpp $(LIBS) $(INCPATH)

FlyerMap.o: $(SRCDIR)FlyerMap.cpp $(SRCDIR)FlyerMap.hpp FlyerMapBuilder.o
	$(CC) $(CFLAGS) -c $(SRCDIR)FlyerMap.cpp $(LIBS) $(INCPATH)

FlyerMapBuilder.o: $(SRCDIR)FlyerMapBuilder.cpp $(SRCDIR)FlyerMapBuilder.hpp
	$(CC) $(CFLAGS) -c $(SRCDIR)FlyerMapBuilder.cpp $(LIBS) $(INCPATH)

clean:
	rm osm-flyer FlyerWindow.o FlyerCamera.o FlyerMap.o FlyerMapBuilder.o
