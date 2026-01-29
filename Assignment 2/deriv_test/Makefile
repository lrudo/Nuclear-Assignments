CC	=	gcc
CFLAGS	=	-I.	-lm
RM	=	rm	-f

default:	all

all:	deriv_test

deriv_test:	main_deriv.c derivatives.c
			$(CC)	-o	deriv_test	main_deriv.c	derivatives.c $(CFLAGS)


clean veryclean:
			$(RM)	deriv_test 
