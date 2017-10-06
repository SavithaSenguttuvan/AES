CC=gcc
OBJ = multithread_File.o

%.o: %.c
	$(CC) -pthread $^


hellomake: $(OBJ)	
	./a.out

clean: 
	rm a.out	