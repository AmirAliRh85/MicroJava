TARGET = main
FILE = ./examples/hello_world.mj

SRCS = ${wildcard ./src/*.cpp}


run : compile
	./${TARGET}.exe ${FILE}

compile :
	g++ ${TARGET}.cpp -o ${TARGET}.exe ${SRCS}