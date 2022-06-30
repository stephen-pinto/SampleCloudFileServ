OBJ = bin/app.out
##CC = g++-11
#For now cant use latest compiler for crypto++ so using default clang from mac
CC = g++
CFLAGS = -std=c++11
INCLUDE = -I"../../../../libs/boost_1_79_0" -I"../../../../libs/cryptopp860/build" 
LIB = -L"../../../../libs/boost_1_79_0/stage/lib" -L"../../../../libs/cryptopp860/build/lib"
LIBFILES = -lboost_filesystem -lcryptopp
SRCS = $(wildcard src/*.cpp)

app:
	${CC} -Wall ${SRCS} ${CFLAGS} ${INCLUDE} ${LIB} ${LIBFILES} -o ${OBJ}

clean:
	-rm -f bin/*	