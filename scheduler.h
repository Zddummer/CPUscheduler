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


/******************************
 * Global Variables
 ******************************/
	int intAlgorithmNumber = 0;
	int intQuantumValue = -1;
	char *strFileName = "";

/******************************
 * Function declarations
 ******************************/
bool fillGlobalVariables(int argc, char **argv);
int isnumber (const char *c);