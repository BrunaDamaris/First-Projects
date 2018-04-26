#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <strings.h> // coloquei pra bzero
#include <unistd.h>
#define SA struct sockaddr
// fiz a echo só pra rodar mesmo mas por enquanto ela não faz nada sem o cliente então ignorem,precisamos saber mais sobre a mesma
// COMENTÁRIO EM MAIUSCULO SÃO COISAS QUE EU JULGUEI SEREM INTERESSANTES DE RESSALTAR.DEPOIS EU ORGANIZO.
void str_echo(int sockfd)
{
	ssize_t n;
	char buf[4096];
	while(( n = read(sockfd,buf,4096)) > 0)
	{
		write(sockfd,buf,n);
	}
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
 	socklen_t tamanho_cliente;//coloquei o socklen aqui, QUE TEM PELO MENOS 32 BITS,TAMANHO DE ALGUMA COISA,NO CASO ELE ENTRA NO ACCEPT ENTÃO É DO ENDEREÇO

 	struct sockaddr_in cliaddr, servaddr;// CRIAÇÃO DA VARIÁVEL TIPO STRUCT

 	meusocket = socket(AF_INET, SOCK_STREAM, 0);
 	bzero(&servaddr, sizeof(servaddr));
 	servaddr.sin_family = AF_INET;
 	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);// DIZ NO LIVRO QUE PODE SER QUALQUER VALOR AQUIU QUE NORMALMENTE É A CONSTANTE NUMERICA 0  
 	servaddr.sin_port = htons(9502);//HTONS E HTONL RETORNAM O VALOR NA ORDEM DE BYTES DA REDE.

 	bind(meusocket, (SA*)&servaddr, sizeof(servaddr));
	// bind(): QUANDO UM SOCKET É CRIADO,ELE TEM UM NOME(ENDEREÇO DA FAMILIA/PROTOCOLO DA FAMILIA) PORÉM ELE NÃO TEM UM ENDEREÇO.
	//O BIND VAI FAZER COM QUE SEJA DESIGNADO UM ENDEREÇO LOCAL(PORTA LOCAL) PARA ESSE SOCKET ESPECIFICADO PELO ADDR REFERENTE PELO DESCRITOR(QUE FOI CRIADO PELO AF_INET,QUE DEVER O SOCKFD??) DO ARQUIVO.O BIND DEVE SER EXECUTADO ANTES DE QUALQUER CONEXÃO DO CLIENTE COM O SERVIDOR,PORQUE AÍ O SERV VAI TER UM ENDEREÇO,SÓ ENTÃO ELE DEVE ACEITAR CONEXÕES
	//É O BIND QUE VAI VER SE A PORTA JÁ ESTÁ SENDO USADA POR OUTRO PROCESSO.
	// BASICAMENTE, O PAPEL DO BIND É DESIGNAR UM ENDEREÇO AO SOCKET PARA O CLIENTE PODER USAR O MESMO PARA SE CONECTAR AO SERVIDOR.É USADO PRA DEFINIR O PONTO FINAL DA COMUNICAÇÃO(ACHO QUE ONDE A COMUNICAÇÃO VAI OCORRER??).
 	listen(meusocket, 1024);
 	for(;;)
 	{
 		tamanho_cliente = sizeof(cliaddr);
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
	// acho que o programa cai no loop quando executado.
	return 0;
}
