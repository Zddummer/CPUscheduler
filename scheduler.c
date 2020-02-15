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

// Helper function to see if a string is a number.
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

// Validate the command line arguements and store them in global variables.
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
			if (intQuantumValue != 0)
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
	if(intAlgorithmNumber == 4 && intQuantumValue == 0)
	{
		return false;
	}

	return (blnIsTextFileValid && blnIsAlgorithmNumberValid);
}

// Implementation of First Come First Serve algorithm.
void firstComeFirstServe(Process arrProcesses[], int intArraySize){

	int index;
	for(index = 0; index < intArraySize; index++)
	{
		arrProcesses[index].intTurnAroundTime = arrProcesses[index].intWaitTime + arrProcesses[index].intCPUBurstLength;
		arrProcesses[index + 1].intWaitTime = arrProcesses[index].intWaitTime + arrProcesses[index].intCPUBurstLength;

		dblAvgWaitTime = dblAvgWaitTime + arrProcesses[index].intWaitTime;
		dblAvgTurnAroundTime = dblAvgTurnAroundTime + arrProcesses[index].intTurnAroundTime;

		printf("# %d\t%d\t%d\t%d\t%d\n", arrProcesses[index].intProcessId, arrProcesses[index].intCPUBurstLength, arrProcesses[index].intPriority, arrProcesses[index].intWaitTime, arrProcesses[index].intTurnAroundTime);
	}
	dblAvgWaitTime = dblAvgWaitTime / intArraySize;
	dblAvgTurnAroundTime = dblAvgTurnAroundTime / intArraySize;
}

// Implementation of Shortest Job First algorithm.
void shortestJobFirst(Process arrProcesses[], int intArraySize){

	Process arrProcesses_Copy[intArraySize];
	bool blnDidSwapOccur;

	// copy the array so we can sort an calculate times but keep arrival order in the copy
	int i;
	for (i = 0; i < intArraySize; i++) {
    	arrProcesses_Copy[i] = arrProcesses[i];
	}

	do // sort the array by CPU burst length
	{
		blnDidSwapOccur = false;
		int index;
		for(index = 0; index < (intArraySize - 1); index++)
		{
			if(arrProcesses[index].intCPUBurstLength > arrProcesses[index + 1].intCPUBurstLength)
			{
				// swap order
				Process tempProcess = arrProcesses[index];
				arrProcesses[index] = arrProcesses[index + 1];
				arrProcesses[index + 1] = tempProcess;

				blnDidSwapOccur = true;
			}
		}
	} while(blnDidSwapOccur);

	// calculated the wait time and turnaround time for the sorted array
	int index;
	for(index = 0; index < intArraySize; index++)
	{
		arrProcesses[index].intTurnAroundTime = arrProcesses[index].intWaitTime + arrProcesses[index].intCPUBurstLength;
		arrProcesses[index + 1].intWaitTime = arrProcesses[index].intWaitTime + arrProcesses[index].intCPUBurstLength;

		dblAvgWaitTime = dblAvgWaitTime + arrProcesses[index].intWaitTime;
		dblAvgTurnAroundTime = dblAvgTurnAroundTime + arrProcesses[index].intTurnAroundTime;
	}

	dblAvgWaitTime = dblAvgWaitTime / intArraySize;
	dblAvgTurnAroundTime = dblAvgTurnAroundTime / intArraySize;

	// set the wait and turnaround time for the array that is still sorted by arrival time
	int index2;
	for(index2 = 0; index2 < intArraySize; index2++)
	{
		int index3;
		for(index3 = 0; index3 < intArraySize; index3++)
		{
			if(arrProcesses_Copy[index2].intProcessId == arrProcesses[index3].intProcessId)
			{
				arrProcesses_Copy[index2].intWaitTime = arrProcesses[index3].intWaitTime;
				arrProcesses_Copy[index2].intTurnAroundTime = arrProcesses[index3].intTurnAroundTime;
			}
		}

		printf("# %d\t%d\t%d\t%d\t%d\n", arrProcesses_Copy[index2].intProcessId, arrProcesses_Copy[index2].intCPUBurstLength, arrProcesses_Copy[index2].intPriority, arrProcesses_Copy[index2].intWaitTime, arrProcesses_Copy[index2].intTurnAroundTime);
	}
}

// Implementation for Priotity algorithm
// This function is the same as SJF except we sort the array by priority rather thatn CPU burst length.
void priority(Process arrProcesses[], int intArraySize){

	Process arrProcesses_Copy[intArraySize];
	bool blnDidSwapOccur;

	// copy the array so we can sort an calculate times but keep arrival order in the copy
	int i;
	for (i = 0; i < intArraySize; i++) {
    	arrProcesses_Copy[i] = arrProcesses[i];
	}

	do // sort the array by CPU burst length
	{
		blnDidSwapOccur = false;
		int index;
		for(index = 0; index < (intArraySize - 1); index++)
		{
			if(arrProcesses[index].intPriority > arrProcesses[index + 1].intPriority)
			{
				// swap order
				Process tempProcess = arrProcesses[index];
				arrProcesses[index] = arrProcesses[index + 1];
				arrProcesses[index + 1] = tempProcess;

				blnDidSwapOccur = true;
			}
		}
	} while(blnDidSwapOccur);

	// calculated the wait time and turnaround time for the sorted array
	int index;
	for(index = 0; index < intArraySize; index++)
	{
		arrProcesses[index].intTurnAroundTime = arrProcesses[index].intWaitTime + arrProcesses[index].intCPUBurstLength;
		arrProcesses[index + 1].intWaitTime = arrProcesses[index].intWaitTime + arrProcesses[index].intCPUBurstLength;

		dblAvgWaitTime = dblAvgWaitTime + arrProcesses[index].intWaitTime;
		dblAvgTurnAroundTime = dblAvgTurnAroundTime + arrProcesses[index].intTurnAroundTime;
	}

	dblAvgWaitTime = dblAvgWaitTime / intArraySize;
	dblAvgTurnAroundTime = dblAvgTurnAroundTime / intArraySize;

	// set the wait and turnaround time for the array that is still sorted by arrival time
	int index2;
	for(index2 = 0; index2 < intArraySize; index2++)
	{
		int index3;
		for(index3 = 0; index3 < intArraySize; index3++)
		{
			if(arrProcesses_Copy[index2].intProcessId == arrProcesses[index3].intProcessId)
			{
				arrProcesses_Copy[index2].intWaitTime = arrProcesses[index3].intWaitTime;
				arrProcesses_Copy[index2].intTurnAroundTime = arrProcesses[index3].intTurnAroundTime;
			}
		}

		printf("# %d\t%d\t%d\t%d\t%d\n", arrProcesses_Copy[index2].intProcessId, arrProcesses_Copy[index2].intCPUBurstLength, arrProcesses_Copy[index2].intPriority, arrProcesses_Copy[index2].intWaitTime, arrProcesses_Copy[index2].intTurnAroundTime);
	}
}

// Open and read from the txt file provided
void readFile(){
	FILE *fCurrentFile;
	int intNumberOfProcesses = 0;
	int intArraySize = 0;
	char str[20];

	fCurrentFile = fopen(strFileName, "r");
	if( fCurrentFile == NULL)
	{
		printf("ERROR: The file \"%s\" could not be found!\n", strFileName);
		return;
	}
	else
	{
		fscanf(fCurrentFile, "%d", &intNumberOfProcesses);
		Process arrProcesses[intNumberOfProcesses];
		intArraySize = intNumberOfProcesses;

		printf("Arrival Order: ");

		int index = 0;
		while(intNumberOfProcesses > 0)
		{
			fscanf(fCurrentFile, "%s", str);
			arrProcesses[index].intProcessId = atoi(str);

			fscanf(fCurrentFile, "%s", str);
			arrProcesses[index].intCPUBurstLength = atoi(str);

			fscanf(fCurrentFile, "%s", str);
			arrProcesses[index].intPriority = atoi(str);

			arrProcesses[index].intWaitTime = 0;
			arrProcesses[index].intTurnAroundTime = 0;

			printf("%d", arrProcesses[index].intProcessId);
			if(intNumberOfProcesses > 1)
			{
				printf(", ");
			}

			index++;
			intNumberOfProcesses--;
		}
		printf("\nProcess Information:\n");
		for(index = 0; index < intArraySize; index++)
		{
			printf("%d\t%d\t%d\n", arrProcesses[index].intProcessId, arrProcesses[index].intCPUBurstLength, arrProcesses[index].intPriority);
		}
		printf("-------------------------------\n");
		printf("Running...\n");
		printf("##################################################\n");
		printf("# #\tCPU\tPri\tW\tT\n");
		switch(intAlgorithmNumber)
		{
			case 1 :
				firstComeFirstServe(arrProcesses, intArraySize);
				break;
			case 2 :
				shortestJobFirst(arrProcesses, intArraySize);
				break;
			case 3 :
				priority(arrProcesses, intArraySize);
				break;
			case 4 :
				// RR
				break;
			default :
				break;
		}
	}

}

// Starting point for our program
int main(int argc, char **argv)
{
	if (fillGlobalVariables(argc, argv))
	{
		printf("Scheduler : %d ", intAlgorithmNumber);
		switch(intAlgorithmNumber)
		{
			case 1 :
				printf("FCFS\n");
				break;
			case 2 :
				printf("SJF\n");
				break;
			case 3 :
				printf("Priority\n");
				break;
			case 4 :
				printf("RR\n");
				break;
			default :
				break;
		}
		printf("Quantum : %d\n", intQuantumValue);
		printf("Sch. File : %s\n", strFileName);
		printf("-------------------------------\n");
		readFile();
		printf("##################################################\n");
		printf("# Avg. Waiting Time : %.2f\n", dblAvgWaitTime);
		printf("# Avg. Turnaround Time: %.2f\n", dblAvgTurnAroundTime);
		printf("##################################################\n");
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
    return 0;
}
