CFLAGS = -I ./include
LFLAGS = -lrt -lX11 -lGLU -lGL -pthread -lm #-lXrandr

all: bobsdayoff 

bobsdayoff: bobsdayoff.cpp log.cpp tristanB.cpp rudyM.cpp kennyT.cpp
	g++ $(CFLAGS) bobsdayoff.cpp log.cpp tristanB.cpp rudyM.cpp kennyT.cpp libggfonts.a -Wall -Wextra $(LFLAGS) -obobsdayoff

clean:
	rm -f bobsdayoff
	rm -f *.o

