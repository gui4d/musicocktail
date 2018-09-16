CFLAGS=-W -Wall -g

communication : constants.o ingredient.o serialCommunication.o testCommunication.o
	gcc $^ -o testCommunication.exe $(CFLAGS)
	rm -rf *.o

firstRecipe : constants.o ingredient.o recipes.o serialCommunication.o TestEndToEndRecipe.o
	gcc $^ -o testEndToEndRecipe.exe $(CFLAGS)
	rm -rf *.o

constants.o :../constants.c
	gcc -c $^ $(CFLAGS) -lm

ingredient.o :../ingredient.c
	gcc -c $^ $(CFLAGS) -lm

recipes.o :../recipes.c
	gcc -c $^ $(CFLAGS) -lm

serialCommunication.o: ../serialCommunication.c
	gcc -c $^ $(CFLAGS) -lm

demo.o :../demo.c
	gcc -c $^ $(CFLAGS) -lm

music.o :../music.cpp
	g++ -c $^ $(CFLAGS) -lm

main.o :main.cpp
	g++ -c $^ $(CFLAGS) -lm

testCommunication.o :testCommunication.c
	gcc -c $^ $(CFLAGS) -lm

TestEndToEndRecipe.o:TestEndToEndRecipe.c
	gcc -c $^ $(CFLAGS) -lm


clean : 
	rm -f *.o

cleanall:
	rm -f *.o *.exe 

//change tis makefile dependant from the original one  in order to avoid redondance 