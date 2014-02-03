/*         tankserv.c		 /
/				 / 
/ this is the server. client	 /
/ program 'tank' connects to the /
/ IP address of tankserv, the 	 /
/ commands of a macro are sent   /
/ to the server, where they are  /
/ processed, interpreted, and    /
/ executed.			*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <asm/io.h>

#define PORT 9696
#define BASEPORT 0x378 /* lp1 port */


void netcom_process(char *com);
void netmove_tank(char direc[], int time);
void open_port(void);
void close_port(void);
void safe_exit(int value);
void forward(int time);
void backward(int time);
void foright(int time);
void foleft(int time);
void baright(int time);
void baleft(int time);
void stop(int time);

main(int argc, char *argv[])
{
	open_port(); /* open lp1 port */
	outb(0, BASEPORT); /* take voltage off lp1, turn on switch */

	int cont, create_socket, new_socket, addrlen; /* socket info */
	int bufsize = 1024;
	char *buffer = malloc(bufsize);
	struct sockaddr_in address;

	if (argc != 2) {
		printf("\nUsage: tankserver {IP ADDRESS}\n");
		safe_exit(1);
	}
		
	if ((create_socket = socket(AF_INET, SOCK_STREAM, 0)) > 0)
		printf("Socket created\n");
	address.sin_family = AF_INET;
	inet_pton(AF_INET, argv[1], &address.sin_addr);
	address.sin_port = htons(PORT);
	if (bind(create_socket,(struct sockaddr *)&address,sizeof(address)) ==0)
		printf("Binding socket\n");
	listen(create_socket, 3);
	addrlen = sizeof(struct sockaddr_in);
	new_socket = accept(create_socket,(struct sockaddr *)&address,&addrlen);
	if (new_socket > 0) {
		printf("Client %s connected.\n",inet_ntoa(address.sin_addr));
		for (cont=1; cont < 5000; cont++)
			printf("\x7");
	}
	do {
		/*printf("Message to send: ");
		gets(buffer);
		send(new_socket, buffer, bufsize, 0);*/
		recv(new_socket, buffer, bufsize, 0);
		printf("Command recieved: %s\n", buffer);
		netcom_process(buffer);
	} while (strcmp(buffer, "q")); 
	close(new_socket);
	close(create_socket);

	safe_exit(0);
}

void netcom_process(char *com)
{
        static char direction[2] = {0};
        static int seconds;


        strncpy(direction, com, 2);
        /*printf("\n%s", direction);*/
        seconds = atoi(&com[2]);
/*      printf("\n%i", seconds);        */
                        
        if (direction[1] != 0) {
                netmove_tank(direction, seconds);
        }
        
        
}

void netmove_tank(char direc[], int time)
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

} /* end netmove_tank function */


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

