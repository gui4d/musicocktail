CFLAGS=-W -Wall -g

install : 
	make programme.exe
	make clean 
programme.exe : main.o ingredient.o cocktail.o
	gcc $^ -o programme.exe $(CFLAGS)

%.o :%.c
	gcc -c $^ $(CFLAGS) -lm

clean : 
	rm -f *.o
cleanall:
	rm -f *.o *.exe 