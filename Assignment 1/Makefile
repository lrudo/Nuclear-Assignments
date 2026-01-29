CC	=	gcc
CFLAGS	=	-I.	-lm
RM	=	rm	-f

default:	all

all:	solve_test

solve_test:	main_solve.c solve.c
			$(CC)	$(CFLAGS)	-o	solve_test	main_solve.c	solve.c

clean veryclean:
			$(RM)	solve_test
