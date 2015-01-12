/*
drone.h
Author: Matt Coia
Date created: September 29, 2014 modified October 28, 2014
This header file initializes all program functions and assigns libraries to include.
*/


#ifndef DRONE_H
#define DRONE_H

#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>

pthread_mutex_t mutex;
pthread_mutex_t mutex2;
pthread_mutex_t mutex3;

typedef struct 
{
	int grid[50][50];

} DATA;

DATA d;
int r, c;

void *assignGate(long droneid);

void *regDrone(long droneid);

void *assignMission(long droneid, int *targetRow, int *targetCol);

void *giveClearance(long droneid, int *homeRow, int *homeCol);

void *takeOff(long droneid, int *homeRow, int *homeCol, int *targetRow, int *targetCol);

void *reachAlt(long droneid, int *homeRow, int *homeCol, int *targetRow, int *targetCol);

void *initialize();

void *fly(long droneid, int *homeRow, int *homeCol, int *targetRow, int *targetCol, int mission, int *state, int *active);

void *deliverPayload(long droneid, int *targetRow, int *targetCol, int *mission);

void *returnHome(long droneid);

void *land(long droneid, int *homeRow, int *homeCol);

void *locate(long id);

void *avoid(long droneid, int *homeRow, int *homeCol, int *targetRow, int *targetCol);

void *abrt(long droneid);

void *increaseRow(long droneid, int *homeRow, int *homeCol, int *targetRow, int *targetCol);

void *increaseCol(long droneid, int *homeRow, int *homeCol, int *targetRow, int *targetCol);

void *decreaseRow(long droneid, int *homeRow, int *homeCol, int *targetRow, int *targetCol);

void *decreaseCol(long droneid, int *homeRow, int *homeCol, int *targetRow, int *targetCol);

#endif
