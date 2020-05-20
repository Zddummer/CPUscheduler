# CS441/541 Project 4 Test Suite

This directory should contain your additional tests.

test_1:
	This test is a random order and number test. It is meant to test an arrival order, CPU burst length,
	and priority given in no structured way.

test_2:
	This test is the "zero" test. All tests should have a basline test. This tests what will happen if the program is given no inputs.

test_3:
	This test is a scaling test. It tests to make sure the program works when give a clear ascending order of
	process IDs, CPU burst lengths, and priorities.

test_4:
	This test is the opposite of test_3. It tests with a descending order.

test_5:
	This test is a test where the process IDs are random, but the CPU burst length and the priority are all the same. This is meant to test what branches are taken on equivalent variables.