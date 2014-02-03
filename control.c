/*       control.c 	  /
/          		  /
/   movements for tank.   /
/   may need gcc -02 to   /
/   compile. 		  /
/                         /
/   David Baker 2004      /
/                        */

#include <stdio.h>
#include <string.h>
#include <asm/io.h>
#include "control.h"

#define BASEPORT 0x378 /* lp1 */

/* used primarily for taking contents of macro file */
void move_tank(char direc[], int time)
{
	if (!strcmp(direc, "ff")) {
		forward(time);
	}

	else if (!strcmp(direc, "bb")) {
		backward(time);
	}

	else if (!strcmp(direc, "fr")) {
		foright(time);
	}

	else if (!strcmp(direc, "fl")) {
		foleft(time);
	}

	else if (!strcmp(direc, "br")) {
		baright(time);
	}

	else if (!strcmp(direc, "bl")) {
		baleft(time);
	}

	else if (!strcmp(direc, "ss")) {
		stop(time);
	}
	
	else {
		printf("ERROR: cannot move tank in that direction\n");
		safe_exit(1);
	}

} /* end move_tank function */ 


/* seven possible tank movements */

void forward (int time)
{
	outb(8, BASEPORT); /* 1000 */
	sleep(time);
	outb(0, BASEPORT);
}

void backward (int time)
{
	outb(4, BASEPORT); /* 0100 */
	sleep(time);
	outb(0, BASEPORT);
}

void foright (int time)
{
	outb(10, BASEPORT); /* 1001 */
	sleep(time);
	outb(0, BASEPORT); 
}

void foleft (int time)
{
	outb(9, BASEPORT); /* 1010 */
	sleep(time);
	outb(0, BASEPORT);
}

void baright (int time)
{
	outb(6, BASEPORT); /* 0101 */
	sleep(time);
	outb(0, BASEPORT);
}

void baleft (int time)
{
	outb(5, BASEPORT); /* 0110 */
	sleep(time);
	outb(0, BASEPORT);
}	

void stop(int time)
{
	outb(0, BASEPORT); /* 0000 */
	sleep(time);
}

/* end of the seven tank movements */

/*/ / / / / / / / / / / / / / / / / /
/  manual mode requires the ports to
/  be set for an indefinite amount 
/  of time, so they require their 
/  own functions */

/* manual mode movement functions */

void man_f(void) /* forward */
{
	outb(8, BASEPORT);
	/*printf("status: %d\n", inb(BASEPORT));*/
}

void man_b(void) /* backward */
{
	outb(4, BASEPORT);
	/*printf("status: %d\n", inb(BASEPORT));*/
}

void man_fr(void) /* for+right */
{
	outb(10, BASEPORT);
	/*printf("status: %d\n", inb(BASEPORT));*/
}

void man_fl(void) /* for+left */
{
	outb(9, BASEPORT);
	/*printf("status: %d\n", inb(BASEPORT));*/
}

void man_br(void) /* bac+right */
{
	outb(6, BASEPORT);
	/*printf("status: %d\n", inb(BASEPORT));*/
}

void man_bl(void) /* bac+left */
{
	outb(5, BASEPORT);
	/*printf("status: %d\n", inb(BASEPORT));*/
}

void man_stop(void) /* brakes (-: */
{
	outb(0, BASEPORT);
	/*printf("status: %d\n", inb(BASEPORT));*/
}
