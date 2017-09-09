CC = gcc

SRCS :=   main.c	\
		  circbuf.c 

OBJS = $(SRCS:.c=.o)

%.o : %.c
	$(CC) -c $< -o $@ 


.PHONY: build
build: $(OBJS) 
	$(CC) $(OBJS) -o new.out 		

.PHONY: clean
clean:  
	rm -rf *.o  new.out  