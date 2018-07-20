CFLAGS=-W -Wall 

programme.exe : main.o ingredient.o
	gcc $^ -o programme.exe $(CFLAGS)

%.o :%.c
	gcc -c $^ $(CFLAGS) -lm

clean:
	rm -f *.o *.exe 