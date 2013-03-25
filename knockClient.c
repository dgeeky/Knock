#include <sys/types.h>

#include <sys/socket.h>

#include <netinet/in.h>

#include <arpa/inet.h>

#include <unistd.h>

#include <netdb.h> // pour h_errno

#include <fcntl.h>

#include <stdio.h>

#include <string.h>

#include <stdlib.h>



#define NOMBRE_PORT 3



//extern int  h_errno





int main(int argc, char const *argv[])

{

	

	int sock;

	struct sockaddr_in sin;

	struct hostent* host;



	int tPort[NOMBRE_PORT];

	int flags;

	int i;

	



	/* variable temporaire */



	char h[20];



	printf("entrer server ip:");

	scanf("%s" , h);

	host = gethostbyname(h);

	for (i = 0; i < NOMBRE_PORT; i++)

	{

		printf("entrer %d-eme port " , i+1);

		scanf("%d" , &tPort[i]);

	}

	

	for (i = 0; i < NOMBRE_PORT; i++)

	{

	

	sock = socket(AF_INET , SOCK_STREAM , 0);

	flags = fcntl(sock, F_GETFL, 0);

	fcntl(sock, F_SETFL, flags | O_NONBLOCK);



	sin.sin_addr.s_addr = *((long*)host->h_addr_list[0]);

    	sin.sin_family = AF_INET;   

    	sin.sin_port = htons(tPort[i]);



	connect(sock, (struct sockaddr*)&sin, sizeof(struct sockaddr));

            printf("Connexion à %s sur le port %d\n", inet_ntoa		(sin.sin_addr), htons(sin.sin_port));



         

        close(sock);

}



	return 0;

}
