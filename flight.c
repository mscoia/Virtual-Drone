/*
flight.c
Author: Matt Coia
Date created: September 29, 2014 modified October 28, 2014
This program uses threading to create drones that will leave a base, go to a target, and return home.
The area of operations is simulated by a 50x50 grid with base in center.  Targets are assigned randomly.  Collisions are avoided.
Flight.c provides functionality for the drones when they are in the air.
*/

#include"drone.h"


void *fly(long droneid, int *homeRow, int *homeCol, int *targetRow, int *targetCol, int mission, int *state, int *active){

//	printf("Drone %d is on the way to target.\n", droneid);


						if(*targetRow > *homeRow){

							// if target row is larger, move to next larger row.
							increaseRow( droneid, homeRow, homeCol, targetRow, targetCol);
							locate(droneid); 

							return;

						}
						if(*targetRow < *homeRow){  //if target row is smaller, move to correct column first.

							if(*targetCol > *homeCol){

								// if target column is larger, move to next larger column.
								increaseCol(droneid, homeRow, homeCol, targetRow, targetCol);
								locate(droneid);

								return;

							}
							if(*targetCol < *homeCol){

								// if target column is smaller, move to next smaller column.
								decreaseCol(droneid, homeRow, homeCol, targetRow, targetCol);
								locate(droneid);

								return;

							}
							if(*targetCol == *homeCol){

								//once target column is reached we can move to smaller row.
								decreaseRow(droneid, homeRow, homeCol, targetRow, targetCol);
								locate(droneid);

								return;

							}

							else
								return;

						}
						if(*targetRow == *homeRow){ //reached the correct row

							if(*targetCol > *homeCol){

								// if target column is larger, move to next larger column.
								increaseCol(droneid, homeRow, homeCol, targetRow, targetCol);
								locate(droneid);

								return;

							}
							if(*targetCol < *homeCol){

								// if target column is smaller, move to next smaller column.
								decreaseCol(droneid, homeRow, homeCol, targetRow, targetCol);
								locate(droneid);

								return;

							}
						}								

							if(*targetCol == *homeCol){

								if(mission==0){	//if mission is 0 then drone is looking for initial target							
									printf("Target reached by drone %d.\n", droneid);
									*state = 7;

									sleep(2);
	
									return;
								}else{  //if mission is not 0 then drone is on the way home to base.
									printf("Drone %d is ready to land at the base.\n", droneid);
									*state = 9;

									sleep(2);
	
									return;
								}

							}else {  //failsafe but it shouldn't ever reach these lines

								printf("Drone %d lost.  Send out the troops!", droneid);
								*active = 0;
								sleep(2);
	
								return;

							}

	
							// another failsafe but it should never reach here either
							return;							
					
}

void *deliverPayload(long droneid, int *targetRow, int *targetCol, int *mission){  //resets target to be base coords, sets mission to 1 which indicates return to base mode

	printf("Drone %d has delivered its payload!  Time to head home!\n", droneid);
	*targetRow = 25;
	*targetCol = 25;
	*mission = 1;
	sleep(1);

}

void *returnHome(long droneid){

	printf("Drone %d is now enroute to base.\n", droneid);

}

void *land(long droneid, int *homeRow, int *homeCol){  //parks drone, resets base to zero (no drone present)

	printf("Drone %d on final approach.  Mission Complete!\n", droneid);
	pthread_mutex_lock(&mutex3);
	d.grid[*homeRow][*homeCol] = 0;
	pthread_mutex_unlock(&mutex3);
}

void *locate(long id){ //scans grid for drone number that is passed in, prints out coords when found.
	for(r=0;r<50;r++){	
		for(c=0;c<50;c++){
			if(d.grid[r][c]==id){
				printf("Drone %d is currently at (%d,%d).\n", id, r, c);
			}
		}
	}
}

void *increaseRow(long droneid, int *homeRow, int *homeCol, int *targetRow, int *targetCol){  //movement function for increasing row location in grid by 1



	if(d.grid[*homeRow+1][*homeCol]==0){
		pthread_mutex_lock(&mutex2);
		++(*homeRow);
		d.grid[*homeRow][*homeCol] = droneid;
		d.grid[*homeRow-1][*homeCol]=0;
		pthread_mutex_unlock(&mutex2);
	}else {

		avoid( droneid, homeRow, homeCol, targetRow, targetCol);
		sleep(1);
	}
}

void *increaseCol(long droneid, int *homeRow, int *homeCol, int *targetRow, int *targetCol){  //movement function for increasing column location in grid by 1


	if(d.grid[*homeRow][*homeCol+1]==0){
		pthread_mutex_lock(&mutex2);
		++(*homeCol);
		d.grid[*homeRow][*homeCol] = droneid;
		d.grid[*homeRow][*homeCol-1]=0;
		pthread_mutex_unlock(&mutex2);
	}else {

		avoid( droneid, homeRow, homeCol, targetRow, targetCol);
		sleep(1);
	}
}

void *decreaseRow(long droneid, int *homeRow, int *homeCol, int *targetRow, int *targetCol){   //movement function for decreasing row location in grid by 1


	if(d.grid[*homeRow-1][*homeCol]==0){
		pthread_mutex_lock(&mutex2);
		--(*homeRow);
		d.grid[*homeRow][*homeCol] = droneid;
		d.grid[*homeRow+1][*homeCol]=0;
		pthread_mutex_unlock(&mutex2);
	}else {

		avoid( droneid, homeRow, homeCol, targetRow, targetCol);
		sleep(1);
	}
}

void *decreaseCol(long droneid, int *homeRow, int *homeCol, int *targetRow, int *targetCol){   //movement function for decreasing column location in grid by 1


	if(d.grid[*homeRow][*homeCol-1]==0){
		pthread_mutex_lock(&mutex2);
		--(*homeCol);
		d.grid[*homeRow][*homeCol] = droneid;
		d.grid[*homeRow][*homeCol+1]=0;
		pthread_mutex_unlock(&mutex2);
	}else {

		avoid( droneid, homeRow, homeCol, targetRow, targetCol);
		sleep(1);
	}
}

						

