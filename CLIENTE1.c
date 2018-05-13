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
	char msgenviada[4096], msgreceb[4096], user[500]; // dois chars
	int i;
	int p;
	
	printf("Escolha um nome de usuario: ");
	
	scanf("%s\n",user);

	write(meusocket, user, strlen(user));

	read(meusocket, msgreceb, 4096);
	
	while(strcmp(msgenviada, "xau") != 0 && strcmp(msgreceb, "xau") != 0)
	{
		
		bzero(msgenviada,sizeof(msgenviada));
		printf("Digite uma mensagem: ");
		
		fgets(msgenviada,4096,fp);
		
		printf("<%s>%s\n", user,msgenviada);

		write(meusocket, msgenviada, strlen(msgenviada));
		
		printf("aguardando mensagem ...\n");
	
		read(meusocket, msgreceb, 4096);

		printf(" Mensagem recebida: %s\n", msgreceb);
		//printf("Mensagem enviada: %s ", msgenviada);
		
	}
}

void str_echo(int meusocket)
{
	ssize_t n;
	char buf[4069];

	again:
		while( (n = read(meusocket, buf, 4096)) > 0)
		{
			write(meusocket, buf, n);
		}
		if(n < 0 && errno == EINTR)
			goto again;
		else if(n<0)
		exit(1);
		//break;
		//erry_sys("str_echo: read error");
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