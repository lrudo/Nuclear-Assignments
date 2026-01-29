CC	=	gcc
CFLAGS	=	-I.	-lm
RM	=	rm	-f

default:	all

all:	extremum_test


extremum_test: main_extremum.c extremum.c derivatives.c solve.c
			$(CC) -o extremum_test main_extremum.c extremum.c derivatives.c solve.c $(CFLAGS)

clean veryclean:
			$(RM)	extremum_test
