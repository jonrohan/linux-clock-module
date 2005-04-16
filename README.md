# Adding a Linux Module

## Description of logic:
The program gets the time info from the xtime function then places it into a buffer which is written to the /proc/clock module. The program also keeps track of the number of calls to the system.

## Errors:
We had a couple of compiling warnings from the compiler but other than that our program runs perfectly.