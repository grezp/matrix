**********
Compiling:
**********

Navigate to the 'build' directory and type 'make' to compile the source.
This will create an executable in the ‘build’ directory called ‘matrix’.

The makefile is autogenerated by CMake. To rebuild the makefile,
you will need at least version 3.13.4 or greater.

************************
Running the application:
************************

The application reads a CSV file placed in the parent directory. As an example, two files have been saved
called ‘a1.csv’ and ‘a2.csv’. Please note, the application can only take integers values.

Once executed, a prompt will ask for user input.

What would you like to do?
Enter:	'0' ---- to close
	    '1' ---- to multiply matrices
	    '2' ---- to transpose matrices

Enter the appropriate value to execute the action of interest. Once an action is complete,
the program will bring you back to the main prompt. If an error is detected, it will also take you
back to the main prompt.

***************
Example Output:
***************
What would you like to do?
Enter:	'0' ---- to close
	    '1' ---- to multiply matrices
	    '2' ---- to transpose matrices
1

Enter file name to read: 
a1.csv
a1.csv:
[0]:         1,         2,         3,
[1]:         4,         5,         6,

Enter file name to read: 
a2.csv
a2.csv:
[0]:         1,         2,
[1]:         3,         4,
[2]:         5,         6,

Result: 
        22        28
        49        64

