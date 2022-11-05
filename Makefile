CC=gcc
LINK=gcc
TARGET=logger.exe
TEST=hashtest.exe
OBJS=logger.o config.o sensors.o
OBJSTEST=hashtest.o
CFLAGS=-g -Wall -Wextra
LFLAGS= -g

all: ${TARGET} ${TEST}

${TARGET}: ${OBJS}
	${CC} ${LFLAGS} -o$@ $^

${TEST}: ${OBJSTEST}
	${CC} ${LFLAGS} -o$@ $^

logger.o: logger.c
config.o: config.c config.h
sensors.o: sensors.c sensors.h

.PHONY : clean

clean:
	del -f ${TARGET} core*
	del -f ${TEST} core*
	del -f *.o core*