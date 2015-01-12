/*
drone.c
Author: Matt Coia
Date created: September 29, 2014 modified October 28, 2014
This program uses threading to create drones that will leave a base, go to a target, and return home.
The area of operations is simulated by a 50x50 grid with base in center.  Targets are assigned randomly.  Collisions are avoided.
*/


#include"drone.h"

void *start(void *arg){
	
	int active = 1;  //controls while loop
	int state = 0;  //init for state of case statements
	int mission = 0;  //int for mission mode (to target or to base)
	long droneid = (long)arg+1; //assigns thread# to drone
	int homeRow = 25;  //init of starting coord for row
	int homeCol = 25;  //int of starting coord for column
	int targetRow;
	int targetCol;
	time_t t;
	srand((unsigned) time(&t));  //for random number generator


	initialize();  //functions are commented where they are defined

	while(active==1){
		switch(state){
			case 0: 	regDrone(droneid);
						sleep(2);
						state = 1;
						break;

			case 1:	  assignGate(droneid);
						sleep(2);
						state = 2;
						break;

			case 2: 	assignMission(droneid, &targetRow, &targetCol);

						if(targetRow==25 && targetCol==25){ //so target is not created at base
							break;
						}else{
							sleep(1);
							printf("Drone %d has a target at (%d,%d).\n", droneid, targetRow, targetCol);
							sleep(1);
							state = 3;
							break;
						}

			case 3:	giveClearance(droneid, &homeRow, &homeCol);

						state = 4;
						break;

			case 4:	takeOff(droneid, &homeRow, &homeCol, &targetRow, &targetCol);

						state = 5;
						break;

			case 5: 	reachAlt(droneid, &homeRow, &homeCol, &targetRow, &targetCol);

						state = 6;
						printf("Drone %d is on the way to target.\n", droneid);
						pthread_mutex_unlock(&mutex);
						break;

			case 6:	fly(droneid, &homeRow, &homeCol, &targetRow, &targetCol, mission, &state, &active);
						sleep(1);
						break;
						

			case 7:	deliverPayload(droneid, &targetRow, &targetCol, &mission);

						state = 8;
						break;

			case 8:	returnHome(droneid);
						sleep(2);
						state = 6;
						break;

			case 9:	land(droneid, &homeRow, &homeCol);
					
						sleep(2);
						active = 0;

						break;
		}
	}
}


int main(int argc, char *argv[]){

	long i;
	void *status;
	int ret;
	long NUMTHREADS;

	if(argc==2){

		NUMTHREADS=strtol(argv[1], NULL, 0);
		pthread_t drone[NUMTHREADS];
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

		for(i=0;i<NUMTHREADS;i++)
			ret = pthread_create(&drone[i], &attr, start, (void *)i);
			if (ret){
				printf("Error: Thread not created!  Good bye!\n");
				exit(-1);
			}
		pthread_attr_destroy(&attr);
		for(i=0;i<NUMTHREADS;i++)
			ret = pthread_join(drone[i], &status);
			if(ret){
				printf("Error: Thread not joined!  Good bye!\n");
				exit(-1);
			}

		printf("All drones accounted for.  Good Night!\n");
		pthread_mutex_destroy(&mutex);
		pthread_exit(NULL);
	}

	else if(argc>2)
		printf("Too many arguments, looking for one int after executable name.\n");

	else
		printf("Need an integer as an argument for this program to run.\n");
}
