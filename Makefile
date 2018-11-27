CFLAGS = -I ./include
LFLAGS = -lrt -lX11 -lGLU -lGL -pthread -lm #-lXrandr

all: bobsdayoff 

bobsdayoff: bobsdayoff.cpp global.cpp image.cpp sprite.cpp log.cpp tristanB.cpp rudyM.cpp kennyT.cpp timers.cpp level.cpp http.cpp global.h sprite.h image.h kennyT.h tristanB.h rudyM.h level.h http.h
	g++ $(CFLAGS) bobsdayoff.cpp global.cpp image.cpp sprite.cpp log.cpp level.cpp tristanB.cpp rudyM.cpp kennyT.cpp libggfonts.a timers.cpp http.cpp -Wall -Wextra $(LFLAGS) -obobsdayoff

clean:
	rm -f bobsdayoff
	rm -f *.o

