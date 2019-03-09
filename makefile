CFLAGS=-W -Wall -g
GRAPHICS= `pkg-config gtkmm-3.0 --cflags --libs`

ESSENTIAI= -pipe -Wall -O2 -fPIC -I/usr/local/lib/ -I/usr/local/include/essentia/  -I/usr/local/include/essentia/scheduler/ -I/usr/local/include/essentia/streaming/  -I/usr/local/include/essentia/utils -I/usr/include/taglib -I/usr/local/include/gaia2 -I/usr/include/qt4 -I/usr/include/qt4/QtCore -D__STDC_CONSTANT_MACROS 
ESSENTIAL= -L/usr/local/lib -lgaia2 -lessentia -lfftw3  -lavcodec -lavformat -lavutil -lsamplerate -ltag -lfftw3f -lQtCore -lyaml

CFLAGS=-W -Wall -g


install : 
	make programme.exe
	make clean 
	echo done 

run :
	make programme.exe
	echo done 


demo : constants.o ingredient.o recipes.o serialCommunication.o music.o demo.o 
	g++ $^ -o musicocktail.exe $(CFLAGS) $(GRAPHICS)

programme.exe :  src/constants.o src/ingredient.o src/recipes.o src/serialCommunication.o src/musicAnalysis/extractor_music/MusicExtractor.o src/musicAnalysis/extractor_music/MusicRhythmDescriptors.o src/musicAnalysis/extractor_music/MusicTonalDescriptors.o src/musicAnalysis/extractor_music/MusicLowlevelDescriptors.o src/musicAnalysis/streaming_extractor_music.o src/interface.o main.o 
	g++ $^ -o musicocktail.exe $(CFLAGS) $(GRAPHICS) $(ESSENTIAL)

src/constants.o :src/constants.c
	gcc -c $^ $(CFLAGS) -lm -o src/constants.o

src/ingredient.o :src/ingredient.c
	gcc -c $^ $(CFLAGS) -lm -o  src/ingredient.o

src/recipes.o :src/recipes.c
	gcc -c $^ $(CFLAGS) -lm -o  src/recipes.o

src/serialCommunication.o: src/serialCommunication.c
	gcc -c $^ $(CFLAGS) -lm -o src/serialCommunication.o

demo.o :demo.c
	gcc -c $^ $(CFLAGS) -lm

src/music.o :src/music.cpp
	g++ -c $^ $(CFLAGS) -lm -o src/music.o 

main.o : main.cpp
	g++ -c $^  $(CFLAGS) -lm $(GRAPHICS)

src/interface.o : src/interface.cpp
	g++ -c $^  $(CFLAGS) -lm $(GRAPHICS) -o src/interface.o


src/musicAnalysis/streaming_extractor_music.o: src/musicAnalysis/streaming_extractor_music.cpp 
	g++ -c $(ESSENTIAI)   src/musicAnalysis/streaming_extractor_music.cpp  -o src/musicAnalysis/streaming_extractor_music.o $(CFLAGS)


src/musicAnalysis/extractor_music/MusicLowlevelDescriptors.o: src/musicAnalysis/extractor_music/MusicLowlevelDescriptors.cpp 
	g++ -c $(ESSENTIAI)   src/musicAnalysis/extractor_music/MusicLowlevelDescriptors.cpp -o src/musicAnalysis/extractor_music/MusicLowlevelDescriptors.o $(CFLAGS)

src/musicAnalysis/extractor_music/MusicTonalDescriptors.o: src/musicAnalysis/extractor_music/MusicTonalDescriptors.cpp
	g++ -c $(ESSENTIAI)  src/musicAnalysis/extractor_music/MusicTonalDescriptors.cpp -o src/musicAnalysis/extractor_music/MusicTonalDescriptors.o $(CFLAGS)

src/musicAnalysis/extractor_music/MusicRhythmDescriptors.o: src/musicAnalysis/extractor_music/MusicRhythmDescriptors.cpp
	g++ -c $(ESSENTIAI) src/musicAnalysis/extractor_music/MusicRhythmDescriptors.cpp -o src/musicAnalysis/extractor_music/MusicRhythmDescriptors.o $(CFLAGS)

src/musicAnalysis/extractor_music/MusicExtractor.o: src/musicAnalysis/extractor_music/MusicExtractor.cpp
	g++ -c $(ESSENTIAI) src/musicAnalysis/extractor_music/MusicExtractor.cpp -o src/musicAnalysis/extractor_music/MusicExtractor.o $(CFLAGS)

%.exe: %.o 
	echo default compil:
	g++ $^ $(CFLAGS) $(ESSENTIAL) -o $@
	
clean : 
	find . -name "*.o" -type f -delete

cleanexe:
	rm -f  *.exe 