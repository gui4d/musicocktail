CFLAGS=-W -Wall -g
ESSENTIAI= -pipe -O2 -fPIC -I/usr/local/include/essentia/ -I/usr/local/include/essentia/scheduler/ -I/usr/local/include/essentia/streaming/  -I/usr/local/include/essentia/utils -I/usr/include/taglib -I/usr/local/include/gaia2 -I/usr/include/qt4 -I/usr/include/qt4/QtCore -D__STDC_CONSTANT_MACROS  
ESSENTIAL= -L/usr/local/lib -lessentia -lfftw3 -lyaml -lavcodec -lavformat -lavutil -lsamplerate -ltag -lfftw3f -lQtCore -lgaia2
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

TestMusicExtractor:streaming_key.cpp 
	g++  $(ESSENTIAI)  $^ -o streaming_extractor.exe $(ESSENTIAL)

%.o : %.cpp
	g++ -c $(ESSENTIAI) $^ $(ESSENTIAL)

clean : 
	rm -f *.o

cleanall:
	rm -f *.o *.exe