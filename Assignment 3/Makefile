CC	=	gcc
CFLAGS	=	-I.	-lm
RM	=	rm	-f

default:	all

all:	numerov_test


numerov_test: numerov.c main_numerov.c vector_mtx.c
			$(CC) -o numerov_test numerov.c main_numerov.c vector_mtx.c $(CFLAGS)

clean veryclean:
			$(RM)	numerov_test
