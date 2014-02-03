/*              man_mode.c                /
/                                         /
/  this is the manual mode code. uses     /
/  8,4,5,6,1,2,3, to move tank and q to   /
/  leave				  /
/					  /
/  David Baker 2004			  /
/				   	 */

#include <stdio.h>
#include <termios.h>
#include <sys/ioctl.h>
#include "man_mode.h"
#include "control.h"   
 
void man_mode(void)
{   
	struct termios ts;       /* hold info about terminal characteristics */
	struct termios new_ts;   /* hold new info to give back to terminal */
	char c;
	ioctl(0, TCGETS, &ts);        /* get current terminal info */
	new_ts = ts;
	new_ts.c_lflag &= !ICANON;    /* don't buffer */
	new_ts.c_lflag &= !ECHO;      /* don't echo */
	ioctl(0, TCSETS, &new_ts);    /* set terminal w/new characteristics */

	printf("\nTurn on switch\n");

	/* now we get keyboard input */

	do {
		c=getchar();

		switch(c)
		{
			case '8':  man_f(); break;
			case '2':  man_b(); break;
			case '6':  man_fr(); break;
			case '4':  man_fl(); break;
			case '3':  man_br(); break;
			case '1':  man_bl(); break;
			case '5':  man_stop(); break;
			default:   NULL; break;
		} /* end switch */
					
	}while(c!='q'); /* q: quit! */

	ioctl(0, TCSETS, &ts);   /* set terminal back to normal */
}
