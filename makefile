CFLAGS=-W -Wall -g

install : 
	make programme.exe
	make clean 
programme.exe :  constants.o ingredient.o recipes.o cocktail.o music.o main.o 
	gcc $^ -o musicocktail.exe $(CFLAGS)

constants.o :constants.c
	gcc -c $^ $(CFLAGS) -lm

ingredient.o :ingredient.c
	gcc -c $^ $(CFLAGS) -lm

recipes.o :recipes.c
	gcc -c $^ $(CFLAGS) -lm

cocktail.o :cocktail.c
	gcc -c $^ $(CFLAGS) -lm

music.o :music.cpp
	g++ -c $^ $(CFLAGS) -lm

main.o :main.cpp
	g++ -c $^ $(CFLAGS) -lm

clean : 
	rm -f *.o
cleanall:
	rm -f *.o *.exe 