/*
 * This program is a simulation of a CPU scheduler. It takes in 2 or 3 arguments
 * from the command line depending on the commands and simulates the cooresponding
 * scheduling algorithm.
 *
 * @author Zach Dummer
 *
 * CS 441/541: CPU Scheduler
 */

#include "scheduler.h"

int isnumber (const char *strToCheck) { 
    while (*strToCheck) { 
		if (*strToCheck < '0' || *strToCheck > '9')
		{
			return 0;
		} 
		strToCheck++; 
    } 
    return 1; 
}

bool fillGlobalVariables(int argc, char **argv){

	int index;
	bool blnIsTextFileValid = false;
	bool blnIsAlgorithmNumberValid = false;
	char *strSField = "-s";
	char *strQField = "-q";

	// Fill and validate the global variables with the commandline arguments.
	for (index = 1; index < argc; index++)
	{
		// check if the paramter is -s
		if (strcmp(argv[index], strSField) == 0)
		{
			// check for duplicate
			if (blnIsAlgorithmNumberValid)
			{
				return false;
			}

			// make sure arg after -s is valid
			if (argv[index + 1] != NULL && isnumber(argv[index + 1]))
			{
				intAlgorithmNumber = atoi(argv[index + 1]);
				if(intAlgorithmNumber < 1 || intAlgorithmNumber > 4)
				{
					return false;
				}
				blnIsAlgorithmNumberValid = true;
				index++;
			}
			else
			{
				return false;
			}
		}
		// check if the parameter is -q
		else if (strcmp(argv[index], strQField) == 0)
		{
			// check for duplicate
			if (intQuantumValue != -1)
			{
				return false;
			}

			// make sure arg after -q is valid
			if(argv[index + 1] != NULL && isnumber(argv[index + 1]))
			{
				intQuantumValue = atoi(argv[index + 1]);
				if(intQuantumValue < 1)
				{
					return false;
				}
				index++;
			}
			else
			{
				return false;
			}
		}
		// check if parameter is the text file
		else if (strstr(argv[index], ".txt") != NULL)
		{
			// check for duplicate
			if (blnIsTextFileValid)
			{
				return false;
			}

			strFileName = argv[index];
			blnIsTextFileValid = true;
		}
		// we got some invalid data
		else
		{
			return false;
		}
	}

	// check if the q value is filled if needed
	if(intAlgorithmNumber == 4 && intQuantumValue == -1)
	{
		return false;
	}

	return (blnIsTextFileValid && blnIsAlgorithmNumberValid);
}

int main(int argc, char **argv)
{
	printf("Start program\n");
	if (fillGlobalVariables(argc, argv))
	{
		printf("DATA IS VALID\n");
	}
	else
	{
		printf("ERROR: Invalid parameters!\n");
		printf("REQUIRED FIELDS:\n");
		printf("\t-s <1, 2, 3, 4> -> Determines which scheduling Alogorithm to use.\n");
		printf("\t<filename>.txt -> The name of the text file to run.\n");
		printf("\t-q <int greater than 0> -> The quantum value required for -s 4.\n");

		return 0;
	}
	printf("End program\n");

    return 0;
}
