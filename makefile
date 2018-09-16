CFLAGS=-W -Wall -g
GRAPHICS= `pkg-config gtkmm-3.0 --cflags --libs`

install : 
	make programme.exe
	make clean 

demo : constants.o ingredient.o recipes.o serialCommunication.o music.o demo.o 
	g++ $^ -o musicocktail.exe $(CFLAGS) $(GRAPHICS)

programme.exe :  constants.o ingredient.o recipes.o serialCommunication.o music.o main.o 
	g++ $^ -o musicocktail.exe $(CFLAGS) $(GRAPHICS)

constants.o :constants.c
	gcc -c $^ $(CFLAGS) -lm

ingredient.o :ingredient.c
	gcc -c $^ $(CFLAGS) -lm

recipes.o :recipes.c
	gcc -c $^ $(CFLAGS) -lm

serialCommunication.o: serialCommunication.c
	gcc -c $^ $(CFLAGS) -lm

demo.o :demo.c
	gcc -c $^ $(CFLAGS) -lm

music.o :music.cpp
	g++ -c $^ $(CFLAGS) -lm

main.o : main.cpp
	g++ -c $^  $(CFLAGS) -lm $(GRAPHICS)

clean : 
	rm -f *.o

cleanall:
	rm -f *.o *.exe 