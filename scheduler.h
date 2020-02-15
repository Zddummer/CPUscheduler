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
	int intTimeLeftOnCPU;
	int intTotalTimeOnCPU;
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
int isnumber (const char *c);
bool fillGlobalVariables(int argc, char **argv);
void firstComeFirstServe(Process arrProcesses[], int intArraySize);
void shortestJobFirst(Process arrProcesses[], int intArraySize);
void priority(Process arrProcesses[], int intArraySize);
void roundRobin(Process arrProcesses[], int intArraySize);
void readFile();