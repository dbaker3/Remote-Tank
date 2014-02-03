/* tank.c - Tank Client Program /
/  				/
/  main() program, accesses	/
/  manual, network, and macro   /
/  modes. Requires root access  /
/  for port access ioperm()     /
/  May need to compile with:    /
/  gcc -02 ...blah blah...      /
/				/
/  David Baker 2004		/
/			       */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <asm/io.h>
#include "man_mode.h"
#include "mac_mode.h"

#define BASEPORT 0x378 /* lp1 */

void mac_mode(char []);
void net_mode(char []);
void open_port(void);
void close_port(void);
void safe_exit(int value);

int main(int argc, char *argv[])
{
	open_port();	   /* open lp1 port */
	outb(0, BASEPORT); /* safe to turn on switch */

	if (argc < 2) {
		printf("\nusage:  tank [MODE] {FILE/ADDRESS}\n");
		printf("\nmanual:  tank man\n");
		printf("macro:  tank mac /dir/file\n");
		printf("network:  tank net 0.0.0.0 /dir/file\n\n");	
		safe_exit(1);
	}

	else if (!strcmp(argv[1], "man")) {
		man_mode();
	}

	else if (!strcmp(argv[1], "mac")) {
		if (argc < 3) {
			printf("No file specified.\n");
			safe_exit(1);
		}
		mac_mode(argv[2]);
	}

	else if (!strcmp(argv[1], "net")) {
		if (argc < 3) {  
			printf("No address specified.\n");
			safe_exit(1);
		}		
		net_mode(argv[2]);
	}

	else {
		printf("ERROR: '%s' is unknown argument\n",argv[1]);
		printf("give no argument to see usage information\n");
		safe_exit(1);
	}	
	
	outb(0,BASEPORT); /* safe to turn switch off */
	safe_exit(0);
}

/* stub
void man_mode(void)
{
	printf("this is man_mode\n");
	safe_exit(1);
}
*/

/* stub 
void mac_mode(char macro[])
{
	printf("this is mac_mode\n");
	printf("file: "); puts(macro);
	safe_exit(1);
}  
*/

/* stub 
void net_mode(char addy[])
{
	printf("this is net_mode\n");
	printf("address: "); puts(addy);
	safe_exit(1);
} */

/* get access to the port */
void open_port(void)
{
        if (ioperm(BASEPORT, 3, 1)) {
                perror("ioperm");
                safe_exit(1);
        }
}

/* lose access to the port */
void close_port(void)
{
        if (ioperm(BASEPORT, 3, 0)) {
                perror("ioperm");
                safe_exit(1);
        }
}

/* take voltage off port so you can flip switch */
void safe_exit(int value)
{
	printf("Graceful Exit. Turn off switch.\n\n"); /* testing */
	outb(0, BASEPORT);
	close_port();
	exit(value);
}
