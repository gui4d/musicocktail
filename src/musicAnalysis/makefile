CFLAGS=-W -Wall -g
ESSENTIAI= -pipe -Wall -O2 -fPIC -I/usr/local/lib/ -I/usr/local/include/essentia/  -I/usr/local/include/essentia/scheduler/ -I/usr/local/include/essentia/streaming/  -I/usr/local/include/essentia/utils -I/usr/include/taglib -I/usr/local/include/gaia2 -I/usr/include/qt4 -I/usr/include/qt4/QtCore -D__STDC_CONSTANT_MACROS 

ESSENTIAL= -L/usr/local/lib -lgaia2 -lessentia -lfftw3  -lavcodec -lavformat -lavutil -lsamplerate -ltag -lfftw3f -lQtCore -lyaml



music_extractor:extractor_music/MusicLowlevelDescriptors.o extractor_music/MusicTonalDescriptors.o extractor_music/MusicRhythmDescriptors.o extractor_music/MusicExtractor.o streaming_extractor_music.o
	g++ $^ -o music_extractor $(CFLAGS) $(ESSENTIAL) 



extractor_music/MusicLowlevelDescriptors.o: extractor_music/MusicLowlevelDescriptors.cpp 
	g++ -c $(ESSENTIAI)   extractor_music/MusicLowlevelDescriptors.cpp -o extractor_music/MusicLowlevelDescriptors.o $(CFLAGS)

extractor_music/MusicTonalDescriptors.o: extractor_music/MusicTonalDescriptors.cpp
	g++ -c $(ESSENTIAI)  extractor_music/MusicTonalDescriptors.cpp -o  extractor_music/MusicTonalDescriptors.o $(CFLAGS)

extractor_music/MusicRhythmDescriptors.o: extractor_music/MusicRhythmDescriptors.cpp
	g++ -c $(ESSENTIAI) extractor_music/MusicRhythmDescriptors.cpp -o extractor_music/MusicRhythmDescriptors.o $(CFLAGS)

extractor_music/MusicExtractor.o: extractor_music/MusicExtractor.cpp
	g++ -c $(ESSENTIAI) extractor_music/MusicExtractor.cpp -o extractor_music/MusicExtractor.o $(CFLAGS)

%.exe: %.o 
	echo default compil:
	g++ $^ $(CFLAGS) $(ESSENTIAL) -o $@
	

%.o:%.cpp
	echo default compil:
	g++ -c $(ESSENTIAI) $^  $(CFLAGS)
	

clean: 
	rm -rf *.o 



