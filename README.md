# CS441/541 Scheduling Project

## Author(s):

Zach Dummer


## Date:

2/18/2020


## Description:

This program is a CPU scheduling simulator.


## How to build the software

To run the program, navigate to the path that contains the scheduler exe file.
In the command line type ./scheduler followed by the commands specified in the "How to use section".


## How to use the software

After typing ./scheduler you can enter 2 or 3 commands to run the program. These commands can be in any order.
-s <integer> is the type of scheduling algorithm you want to use. (1 - 4)
-q <integer> is only used if -s 4 is specified. This is how much time each process takes on the CPU.
<fileName>.txt is the file name or file path of the file you want to run through the program. (must be positive)

	EXAMPLE: ./scheduler -s 4 test.txt -q 6


## How the software was tested

This software was tested with the files in the given-tests and tests folder.
You can find a further description in the README file in those folders.

## Test Suite

- Files found in given-tests foler
- Files found in tests folder


## Known bugs and problem areas

There are no known bugs or issues at this time.
If you find a bug or issue, please raise an issue @ https://bitbucket.org/zdummer/cs441-scheduler/src/master/