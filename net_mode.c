/*     net_mode.c       	/
/ 				/
/ Network mode. Connects to a 	/
/ server, sends contents of the /
/ macro file.			/
/				/
/			       */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>



#define PORT 9696

void net_mode(char *ipadd[])
{
	int create_socket;
	int bufsize = 1024;
	char *buffer = malloc(bufsize);
	struct sockaddr_in address;
	
	if ((create_socket = socket(AF_INET,SOCK_STREAM,0)) > 0)
		printf("Socket Created\n");
	address.sin_family = AF_INET;
	address.sin_port = htons(PORT); /* socket at port 9696 */
	inet_pton(AF_INET, ipadd, &address.sin_addr); /*put ip info in socket*/

	if(connect(create_socket,(struct sockaddr*)&address,sizeof(address))==0)
		printf("Accepted with server %s\n",inet_ntoa(address.sin_addr));
	
	do {
		printf("Movement (DDS): "); /*move in direction DD,seconds S*/
		gets(buffer);
		send(create_socket, buffer, bufsize, 0);
	} while (strcmp(buffer, "q")); /* q quits */
		
	close(create_socket);
}


