CC=g++
CFLAGS=-Wall
LIBS=-lsfml-graphics -lsfml-window -lsfml-system -lGLU -lm -lcurl -Wl,-Bsymbolic-functions
INCPATH=
SRCDIR=src/

all: osm-flyer

osm-flyer: $(SRCDIR)osm-flyer.cpp FlyerWindow.o 
	$(CC) $(CFLAGS) -o osm-flyer FlyerWindow.o FlyerCamera.o FlyerMap.o FlyerMapBuilder.o OSMConnection.o FlyerConverter.o $(SRCDIR)osm-flyer.cpp $(LIBS) $(INCPATH) 

FlyerWindow.o: $(SRCDIR)FlyerWindow.cpp $(SRCDIR)FlyerWindow.hpp FlyerCamera.o FlyerMap.o FlyerConverter.o
	$(CC) $(CFLAGS) -c $(SRCDIR)FlyerWindow.cpp $(LIBS) $(INCPATH)

FlyerCamera.o: $(SRCDIR)FlyerCamera.cpp $(SRCDIR)FlyerCamera.hpp
	$(CC) $(CFLAGS) -c $(SRCDIR)FlyerCamera.cpp $(LIBS) $(INCPATH)

FlyerMap.o: $(SRCDIR)FlyerMap.cpp $(SRCDIR)FlyerMap.hpp FlyerMapBuilder.o FlyerConverter.o
	$(CC) $(CFLAGS) -c $(SRCDIR)FlyerMap.cpp $(LIBS) $(INCPATH)

FlyerMapBuilder.o: $(SRCDIR)FlyerMapBuilder.cpp $(SRCDIR)FlyerMapBuilder.hpp OSMConnection.o
	$(CC) $(CFLAGS) -c $(SRCDIR)FlyerMapBuilder.cpp $(LIBS) $(INCPATH)

OSMConnection.o: $(SRCDIR)OSMConnection.cpp $(SRCDIR)OSMConnection.hpp
	$(CC) $(CFLAGS) -c $(SRCDIR)OSMConnection.cpp $(LIBS) $(INCPATH)

FlyerConverter.o: $(SRCDIR)FlyerConverter.cpp $(SRCDIR)FlyerConverter.hpp
	$(CC) $(CFLAGS) -c $(SRCDIR)FlyerConverter.cpp $(LIBS) $(INCPATH)

clean:
	rm osm-flyer FlyerWindow.o FlyerCamera.o FlyerMap.o FlyerMapBuilder.o OSMConnection.o FlyerConverter.o
