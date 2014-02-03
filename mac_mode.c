/*       mac_mode.c          	/
/				/
/ this is macro mode code. the 	/
/ values of the macro are read,	/
/ interpreted, and executed.	/
/				/
/ David Baker 2004		/
/			       */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "mac_mode.h"
#include "control.h"

#define MAXLEN 5


void mac_mode(char filename[])
{
	FILE *fp;
	char *commands[50]; /*list of commands to execute*/	
	char buffer[MAXLEN];
	int count = 1;
	char pause[2];


	if ( (fp = fopen( filename, "r" )) != NULL )
	{
		printf("\nFile %s opened successfully.\n", filename);
		printf("Turn on switch, type 'ok' and press Enter. ");
		scanf("%s",pause);
	}
	else
	{
		fprintf(stderr, "\nError opening %s\n", filename);
		safe_exit(1);
	}
 
	for (count = 1; count <= 50; count++)
	{
       		/*printf("\ninside first for loop");*/
		fgets(buffer, MAXLEN, fp);
		commands[count] = buffer;
		/*printf("\n%s", commands[count]);*/
		com_process(commands[count]);
	}	

	printf("\nclosing file\n");
	fclose(fp);

} /*end mac_mode*/

/* processes the commands from fgets */
void com_process(char *com)
{
	static char direction[2] = {0};
	static int seconds;


	strncpy(direction, com, 2);
	/*printf("\n%s", direction);*/
	seconds = atoi(&com[2]);
/*	printf("\n%i", seconds);	*/
			
	if (direction[1] != 0) {
		move_tank(direction, seconds);
	}
	
	
}



	


