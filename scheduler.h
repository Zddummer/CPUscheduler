/*
 * Header file for scheduler.c
 *
 * @author Zach Dummer
 *
 * CS 441/541: CPU Scheduler
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>


/******************************
 * Defines
 ******************************/


/******************************
 * Structures
 ******************************/
typedef struct {
	int intProcessId;
	int intCPUBurstLength;
	int intPriority;
	int intWaitTime;
	int intTurnAroundTime;
} Process;

/******************************
 * Global Variables
 ******************************/
	int intAlgorithmNumber = 0;
	int intQuantumValue = 0;
	char *strFileName = "";
	double dblAvgWaitTime = 0.0;
	double dblAvgTurnAroundTime = 0.0;

/******************************
 * Function declarations
 ******************************/
bool fillGlobalVariables(int argc, char **argv);
int isnumber (const char *c);