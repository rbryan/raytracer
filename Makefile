# Just some random graphics rendering program I'm going to attempt to throw together. 

CC = gcc
CFLAGS =  -g -Wall -O2

main: main.o render.o trace.o
	$(CC) $(CFLAGS) $(gsl-config --cflags)  -o main main.o render.o trace.o -lm $(gsl-config --libs)
	

main.o: main.c config.h
	$(CC) $(CFLAGS)  -c main.c
	

render.o: render.c render.h config.h 
	$(CC) $(CFLAGS)  -c render.c 

trace.o: trace.c config.h
	$(CC) $(CFLAGS) -c trace.c 
	
image:
	python parse_ouput.py

clean:
	rm -f *.o
	rm -f render_output