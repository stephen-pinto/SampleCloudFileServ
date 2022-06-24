OBJ = bin/app.out
CC = g++-11
INCLUDE = -I"../../../../libs/boost_1_79_0"
LIB =
SRCS = $(wildcard src/*.cpp)

app:
	${CC} -Wall ${SRCS} ${INCLUDE} -o ${OBJ} ${LIB}

clean:
	-rm -f bin/*