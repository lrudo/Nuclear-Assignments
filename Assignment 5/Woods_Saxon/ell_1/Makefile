CC	=	gcc
CFLAGS	=	-I.	-lm
RM	=	rm	-f

default:	all

all:	schrodinger


schrodinger: main_schrodinger.c solve.c radial_eq_functions.c vector_mtx.c extremum.c derivatives.c numerov.c schrodinger.c init.c
			$(CC) -o schrodinger main_schrodinger.c schrodinger.c numerov.c solve.c radial_eq_functions.c vector_mtx.c extremum.c derivatives.c init.c $(CFLAGS)

clean veryclean:
			$(RM)	schrodinger
