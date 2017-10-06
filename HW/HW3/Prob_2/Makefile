CC=gcc
OBJ = pthread_api.o

%.o: %.c
	$(CC) -pthread $^


hellomake: $(OBJ)	
	./a.out

clean: 
	rm a.out	
