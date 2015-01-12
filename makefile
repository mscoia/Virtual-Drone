all: drone

drone.o: drone.c drone.h
	gcc drone.c -c -o drone.o

ground.o: ground.c drone.h
	gcc ground.c -c -o ground.o

flight.o: flight.c drone.h
	gcc flight.c -c -o flight.o

problems.o: problems.c drone.h
	gcc problems.c -c -o problems.o

drone: drone.o ground.o flight.o problems.o
	gcc drone.o ground.o flight.o problems.o -o drone -lpthread

clean: 
	rm -f drone
	rm -f *.o
