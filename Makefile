CC = cc
DOTFLAGS = -DDOT_MAX_CLUSTERS=40 -DDOT_MAX_EDGES=10 -DDOT_MAX_NODES=100 -DDOT_MAX_LABEL_SIZE=300
INCLUDEFLAGS = -I. -Iinclude
FLAGS = -ansi -DVSNPRINTF_SUPPORTED -D_POSIX_C_SOURCE=200809L ${DOTFLAGS} ${INCLUDEFLAGS}
DEBUGFLAGS = -pedantic-errors -Wall -Werror -O0 -g
RELEASEFLAGS = -DNDEBUG -O2

debug:
	${CC} src/* ${FLAGS} ${DEBUGFLAGS} -o bin/compileDFA.out

release:
	${CC} src/* ${FLAGS} ${RELEASEFLAGS} -o bin/compileDFA.out
