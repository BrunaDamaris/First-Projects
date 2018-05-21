#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/uio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/un.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>

#define SA struct sockaddr

void str_cli(FILE *fp, int meusocket)
{
	char	msgenviada[4096], msgreceb[4096], user[4096],msgant[4096], msg[4096]; // dois chars
	int i,j, ult;
	int p;
	
	printf("Escolha um nome de usuario: ");
	
	fgets(user, 500, stdin);

	write(meusocket, user, strlen(user));

	read(meusocket, msgreceb, 4096);
	
	while(strcmp(msgenviada, "xau") != 0 || strcmp(msgreceb, "xau") != 0)
	{
		/////////////////////////////////////////////////PARTE 1/////////////////////////////////////////////CORRETA!!!
		for(i=0;msg[i] != '\0';i++)
    	{
    		msg[i] = 0;
    		msgenviada[i] = 0;
    	}
    	printf("\n");
		//printf("Digite uma mensagem: ");
		
		fgets(msgenviada,4096,stdin);
    
    	for(i=0;user[i] != '\n';i++)
    	{
    		msg[i] = user[i];
    	}
    	msg[i] = ':';
    	i++;
    	msg[i] = '\n';
    	for(j=0;msgenviada[j] != '\n'; j++)
    	{
    		msg[i] = msgenviada[j];
    		i++;
    	}
  		msg[i] = '\n';

   		for(i=0;i<strlen(msg);i++)
  		{
   	 		if(msg[i] == '\n') msg[i] = '#';
  		}

	//	printf("Mensagem enviada : %s\n", msg);
		write(meusocket, msg, strlen(msg));// Envia mensagem para servidor
		
		/////////////////////////////////////////////////////////////////////PARTE 2////////////////////////////////////////////////////////FALTA !!
	
		read(meusocket, msgreceb, 4096); // Recebe mensagens do servidor

	//	printf("Mensagem recebida : %s\n", msgreceb);
		for(i=0;i< strlen(msgant);i++)
  		{
   	 		if(msgant[i] == '#') 
   	 		{
   	 		msgant[i] = '\n';
   	 		}  		
   	 	}
		
		for(i=0;i< strlen(msgreceb);i++)
  		{
   	 		if(msgreceb[i] == '#') 
   	 		{
   	 		msgreceb[i] = '\n';
   	 		ult = i;
   	 		//msgant[i] = '\n';
   	 		}  		
   	 	}
   	 	//printf("Mensagem recebida:  %s \n Mensagem anterior : %s \n", msgreceb, msgant);
		for(i=0; i < ult;i++)
  		{
  			if(msgreceb[i] != msgant[i])
  			{
  				printf("%c", msgreceb[i]);
  			//	printf("< %c >", msgant[i]);
  			}
  		}
		//printf(" %s\n", msgreceb);//printa mensagem recebida
		for(i=0;i < 4096;i++)
  		{
  			msgant[i] = msgreceb[i];
  		//	printf("<%c>", msgant[i]);
  			
  		}
  		for(i=0;i < 4096;i++)
  		{
  			msgreceb[i] = 0;
  		//	printf("<%c>", msgant[i]);
  			
  		}
		//printf("Mensagem enviada: %s ", msgenviada);
		
	}
}

int main(int argc, char **argv)
{
	int meusocket;
	struct sockaddr_in servaddr;
	
	if(argc != 2)//se você não digitar ip ele fecha
	{
		return 0;
	}
	
	meusocket = socket(AF_INET, SOCK_STREAM, 0); // abre o socket

	bzero(&servaddr, sizeof(servaddr));

	servaddr.sin_family = AF_INET; // familia do socket

	servaddr.sin_port = htons(9503); // porta do socket

	inet_pton(AF_INET, argv[1], &servaddr.sin_addr); // 
	
	connect(meusocket, (SA *) &servaddr, sizeof(servaddr)); //conetcando cliente em determidado socket,
															// usando o valore de retorno do socket, a suct do socket e o tamanho 
															// da struct severaddr 
	
	str_cli(stdin, meusocket); //entra na função que envia e recebe mensagens

	exit(0);
}