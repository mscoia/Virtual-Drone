/*
problems.c
Author: Matt Coia
Date created: September 29, 2014 modified October 28, 2014
This program uses threading to create drones that will leave a base, go to a target, and return home.
The area of operations is simulated by a 50x50 grid with base in center.  Targets are assigned randomly.  Collisions are avoided.
Problems.c provides functionality for collision avoidance.
*/

#include"drone.h"


void *avoid(long droneid, int *homeRow, int *homeCol, int *targetRow, int *targetCol){

	printf("Drone %d Avoiding Drone Near (%d, %d)!!!\n", droneid, *homeRow, *homeCol);
	pthread_mutex_lock(&mutex3);
	if(d.grid[*homeRow+1][*homeCol]==0)
		increaseRow(droneid, homeRow, homeCol, targetRow, targetCol);
	else if(d.grid[*homeRow][*homeCol+1]==0)
		increaseCol(droneid, homeRow, homeCol, targetRow, targetCol);
	else if(d.grid[*homeRow][*homeCol-1]==0)
		decreaseCol(droneid, homeRow, homeCol, targetRow, targetCol);
	else if(d.grid[*homeRow-1][*homeCol]==0)
		decreaseRow(droneid, homeRow, homeCol, targetRow, targetCol);
	else{
		abrt(droneid);
	}
	pthread_mutex_unlock(&mutex3);
}

void *abrt(long arg){

	printf(" Warning: Drone %d is aborting!!\n", arg);
	
}
