CFLAGS=-W -Wall -g

programme.exe : main.o ingredient.o cocktail.o
	gcc $^ -o programme.exe $(CFLAGS)

%.o :%.c
	gcc -c $^ $(CFLAGS) -lm

clean:
	rm -f *.o *.exe 