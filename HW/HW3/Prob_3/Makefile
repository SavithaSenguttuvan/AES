CC=gcc
OBJ = profile_fork_pthread.o

%.o: %.c
	$(CC) -pthread $^


hellomake: $(OBJ)	
	./a.out

clean: 
	rm a.out	
