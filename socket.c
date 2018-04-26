#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <strings.h> // coloquei pra bzero
#define SA struct sockaddr
// fiz a echo só pra rodar mesmo mas por enquanto ela não faz nada sem o cliente então ignorem,precisamos saber mais sobre a mesma
void str_echo(int sockfd)
{
	ssize_t n;
	char buf[4096];// valor dado pelo livro para o comprimento de linha max do buffer???
	again: // O QUE BOBA É ISSO????
	while(( n = read(sockfd,buf,4096)) > 0)//read maior que zero pq tem que retornar algo??
	{
		write(sockfd,buf,n);// no livro ele fez uma funçao chamada writen mas faz quase a mesma coisa então botei write mesmo
	}
	// Opa tem um goto aqui mas não vou escrever,acho que por isso que tem um again,pro goto,vou deixar o again por conveniencia, vai q né
}

/*struct sockaddr_in
{
	uint8_t		sin_len;
	sa_family_t sin_family;
	in_port_t sin_port;

	struct in_addr sin_addr;	
	char   sin_zero[8];
}; descobri que se faz o struct lá na main não precisa dele aqui*/ 

int main()
{
 	int meusocket, resposta_server;
 	pid_t  criacao_filhos;
 	socklen_t tamanho_cliente;//coloquei o socklen aqui

 	struct sockaddr_in cliaddr, servaddr;

 	meusocket = socket(AF_INET, SOCK_STREAM, 0);
 	bzero(&servaddr, sizeof(servaddr));
 	servaddr.sin_family = AF_INET;
 	servaddr.sin_addr.s_addr = htonl(4711);// coloquei um valor qualquer que precisa ser revisado
 	servaddr.sin_port = htons(9502);

 	bind(meusocket, (SA*)&servaddr, sizeof(servaddr));
 	listen(meusocket, 1024);
 	for(;;)
 	{
 		tamanho_cliente = sizeof(cliaddr);
 		// tava faltando um virgula em accept e o &
 		resposta_server = accept( meusocket,(SA*)&cliaddr, &tamanho_cliente);
 		if((criacao_filhos == fork()) ==0)
 		{
 			close(meusocket);
 			str_echo(resposta_server);
 			exit(0);
 		}
 		close(resposta_server);
 	}
 	// acho que tá tudo direitinho...
	return 0;
}
