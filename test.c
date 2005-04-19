/*
*	AUTHORS:  Jon Rohan
*	DATE:	  4/19/05     
*	PURPOSE:  To implement a clock module on the linux 2.6 kernel.
*/


#include <stdlib.h>
#include <stdio.h>


/* Main test method that will run our module clock 10 times
*  As specified by the instructions in the assignment.
*/

int main()
{
	/* variable i counts */
	int i;


	/* Begin for loop to count 1 to 10 */
	/* Loops through loading the module clock */

	for (i = 0; i < 10; i++)
	{
		/* Set necessary memory allocations */

		FILE * theFile;
		char * data = (char*)malloc(125);


		/* Open the clock module and load into theFile */

		theFile = fopen("/proc/clock", "r");
		fgets(data, 125, theFile);
		struct timeval *  tim;

		/* Provides the current time of day */
		/* Also prints out readings from current time and 
		   time accessed from the clock module */
		
		gettimeofday(tim);
		printf("%d %d %s\n", tim->tv_sec, tim->tv_usec, data);
		

		/* End and close the file opened */

		close(theFile);
	}
return 0;
}
