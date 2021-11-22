CC=g++
ARGS=-Wall
INCLUDE_PATHS=-Isrc/include
LIB_PATHS=-Lsrc/lib
FILES=src/include/Graph/*.cpp src/*.cpp
INCLUDES=-lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf

all:
	${CC} ${ARGS} ${FILES} -o main ${INCLUDE_PATHS} ${LIB_PATHS} ${INCLUDES}
run:
	main.exe
