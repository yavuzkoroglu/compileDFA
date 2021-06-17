CC = cc
DOTFLAGS = -DDOT_MAX_CLUSTERS=40 -DDOT_MAX_EDGES=10 -DDOT_MAX_NODES=100 -DDOT_MAX_LABEL_SIZE=300
INCLUDEFLAGS = -I. -Iinclude
FLAGS = -pedantic-errors -Wall -Werror -ansi ${DOTFLAGS} ${INCLUDEFLAGS}
DEBUGFLAGS = -O0 -g
RELEASEFLAGS = -O2

debug:
	${CC} src/* ${FLAGS} ${DEBUGFLAGS} -o bin/compileDFA.out

release:
	${CC} src/* ${FLAGS} ${RELEASEFLAGS} -o bin/compileDFA.out
