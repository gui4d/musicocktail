CFLAGS=-W -Wall 

programme.exe :cocktail.o  main.o
	gcc $^ -o programme.exe $(CFLAGS)

%.o :%.c
	gcc -c $^ $(CFLAGS) -lm

clean:
	rm -f *.o *.exe 