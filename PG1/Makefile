OBJ = bin/app.out
CC = g++-11
INCLUDE = -I"../../../../libs/boost_1_79_0" -I"../../../../libs/libgcrypt-1.10.1/build/include" -I"../../../../libs/libgpg-error-1.45/build/include"
LIB =
SRCS = $(wildcard src/*.cpp)

app:
	${CC} -Wall ${SRCS} ${INCLUDE} -o ${OBJ} ${LIB}

clean:
	-rm -f bin/*