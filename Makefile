CC=gcc
LINK=gcc
TARGET=logger
TEST=hashtest
OBJS=logger.o config.o sensors.o commands.o can_helper.o
OBJSTEST=hashtest.o
CFLAGS= -g -Wall -Wextra
LFLAGS= -g -pthread

all: ${TARGET} ${TEST}

${TARGET}: ${OBJS}
	${CC} ${LFLAGS} -o $@ $^

${TEST}: ${OBJSTEST}
	${CC} ${LFLAGS} -o $@ $^

logger.o: logger.c
config.o: config.c config.h
sensors.o: sensors.c sensors.h
commands.o: commands.c commands.h
can_helper.o: can_helper.c can_helper.h

.PHONY : clean

clean:
	rm -f ${TARGET} core*
	rm -f ${TEST} core*
	rm -f *.o core*
