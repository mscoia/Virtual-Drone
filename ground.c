/*
ground.c
Author: Matt Coia
Date created: September 29, 2014 modified October 28, 2014
This program uses threading to create drones that will leave a base, go to a target, and return home.
The area of operations is simulated by a 50x50 grid with base in center.  Targets are assigned randomly.  Collisions are avoided.
Ground.c provides functionality for drone operations while at or just leaving the base.
*/
#include"drone.h"

void *regDrone(long droneid){

	printf("Drone %d is registered in the system.  Moving to launch sequence.\n", droneid);
	
}

void *assignGate(long droneid){
	
	printf("Drone %d is assigned to launch gate...awaiting mission.\n", droneid);

}

void *assignMission(long droneid, int *targetRow, int *targetCol){ //creates random target coordinates located on grid

	printf("Mission target being assigned to drone %d now.\n", droneid);
	*targetRow = rand() %50;
	*targetCol = rand() %50;


}

void *giveClearance(long droneid, int *homeRow, int *homeCol){ //puts drone into takeoff location at base coords, locks mutex for takeoff sequence

	printf("Drone %d requesting clearance for takeoff.\n", droneid);

	pthread_mutex_lock(&mutex);

			d.grid[*homeRow][*homeCol] = droneid;
			printf("Clearance granted for drone %d.\n", droneid);
			locate(droneid);
			sleep(1);
	
}

void *takeOff(long droneid, int *homeRow, int *homeCol, int *targetRow, int *targetCol){  //Moves drone out of base to intermediate grid location, if available.

	printf("Drone %d has taken off from the launch pad.\n", droneid);
	if(d.grid[*homeRow+1][*homeCol]==0){

		(*homeRow)++;
		d.grid[*homeRow][*homeCol]=droneid;
	   d.grid[*homeRow-1][*homeCol]=0;

	}else{
		avoid(droneid, homeRow, homeCol, targetRow, targetCol);
		sleep(1);							
	}
	locate(droneid);	
	sleep(1);
}

void *reachAlt(long droneid, int *homeRow, int *homeCol, int *targetRow, int *targetCol){  //Moves drone to second intermediate grid location, if available

	printf("Drone %d has reached cruising altitude.\n", droneid);
	

	if(d.grid[*homeRow][*homeCol]==0){
		(*homeRow)++;
		d.grid[*homeRow][*homeCol]=droneid;
		d.grid[*homeRow-1][*homeCol]=0;

	}else{
		avoid(droneid, homeRow, homeCol, targetRow, targetCol);
		sleep(1);
	}	
	locate(droneid);
	sleep(1);
}

void *initialize(){  //initailize all locations to be unoccupied

	for(r=0;r<50;r++){	
		for(c=0;c<50;c++){
			d.grid[r][c] = 0;
		}
	}
}
