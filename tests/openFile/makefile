CFLAGS=-W -Wall
GRAPHICS= `pkg-config gtkmm-3.0 --cflags --libs`



test: application.o main.o 
	gcc $^ -o test.exe $(CFLAGS) $(GRAPHICS)

%.o : %.cpp 
	gcc -c $^ $(CFLAGS) $(GRAPHICS)

clean: 
	rm -rf *.o

	