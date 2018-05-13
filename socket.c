#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <strings.h> // coloquei pra bzero
#include <unistd.h>
#include <string.h>
#define SA struct sockaddr
int indice = 0;

struct cliente// struct padrão de cliente com endereço variavel de connfd que guarda meu sochet
{
	struct sockaddr_in addr;
	int connfd; // descritor do arquivo de conexão
	char nome[50];
};
struct cliente clientes[100];
// fiz a echo só pra rodar mesmo mas por enquanto ela não faz nada sem o cliente então ignorem,precisamos saber mais sobre a mesma
// COMENTÁRIO EM MAIUSCULO SÃO COISAS QUE EU JULGUEI SEREM INTERESSANTES DE RESSALTAR.DEPOIS EU ORGANIZO.
void str_echo(int sockfd,char vc[])
{
	ssize_t n;
	char buf[4096];
	while(strcmp(buf, "xau") != 0)
	{
		//printf("Mensgam recebida : %s \n", buf);
		//fgets(buf, 4096, stdin);
		printf("aguardando mensagem ...\n");
		//printf("%d", sockfd);
		read(sockfd,buf,4096);// le oque ele escreve
		printf("Mensagem recebida : <%s>%s\n", vc,buf);

		printf("Digite uma mensagem : ");

		fgets(buf, 4096, stdin);

		write(sockfd,buf,50);

		printf("Mensagem enviada : %s\n", buf);
	}
}

int main()
{
 	int meusocket, resposta_server, a=0,i;
 	pid_t  criacao_filhos;
 	char buff[50];
 	socklen_t tamanho_cliente;//coloquei o socklen aqui, QUE TEM PELO MENOS 32 BITS,TAMANHO DE ALGUMA COISA,NO CASO ELE ENTRA NO ACCEPT ENTÃO É DO ENDEREÇO
 	struct sockaddr_in cliaddr, servaddr;// CRIAÇÃO DA VARIÁVEL TIPO STRUCT
 	

 	meusocket = socket(AF_INET, SOCK_STREAM, 0);
 	bzero(&servaddr, sizeof(servaddr));
 	servaddr.sin_family = AF_INET;
 	servaddr.sin_addr.s_addr = htonl(0);// DIZ NO LIVRO QUE PODE SER QUALQUER VALOR AQUI QUE NORMALMENTE É A CONSTANTE NUMERICA 0  
 	servaddr.sin_port = htons(9503);//HTONS E HTONL RETORNAM O VALOR NA ORDEM DE BYTES DA REDE.

 	bind(meusocket, (SA*)&servaddr, sizeof(servaddr));
	// bind(): QUANDO UM SOCKET É CRIADO,ELE TEM UM NOME(ENDEREÇO DA FAMILIA/PROTOCOLO DA FAMILIA) PORÉM ELE NÃO TEM UM ENDEREÇO.
	//BIND VAI FAZER COM QUE SEJA DESIGNADO UM ENDEREÇO LOCAL( OU PORTA LOCAL) PARA ESSE SOCKET ESPECIFICADO PELO ADDR REFERENTE PELO DESCRITOR(QUE FOI CRIADO PELO AF_INET,QUE DEVER O SOCKFD??) DO ARQUIVO.
	//O BIND DEVE SER EXECUTADO ANTES DE QUALQUER CONEXÃO DO CLIENTE COM O SERVIDOR,PORQUE AÍ O SERV VAI TER UM ENDEREÇO,SÓ ENTÃO ELE DEVE ACEITAR CONEXÕES.
	//É O BIND QUE VAI VER SE A PORTA JÁ ESTÁ SENDO USADA POR OUTRO PROCESSO.
	// BASICAMENTE, O PAPEL DO BIND É DESIGNAR UM ENDEREÇO AO SOCKET PARA O CLIENTE PODER USAR O MESMO PARA SE CONECTAR AO SERVIDOR.É USADO PRA DEFINIR O PONTO FINAL DA COMUNICAÇÃO(ACHO QUE ONDE A COMUNICAÇÃO VAI OCORRER??).
 	
 	listen(meusocket, 1024);

 	
  	for(;;)
 	{
 		printf("aguardando cliente\n");
 		tamanho_cliente = sizeof(cliaddr);
 		resposta_server = accept( meusocket,(SA*)&cliaddr, &tamanho_cliente);
 		if((criacao_filhos = fork()) == 0)
 		{
 			close(meusocket);
 		
 			clientes[indice].addr = cliaddr; // guarda endereço do cliente num struct
 		
 			clientes[indice].connfd = meusocket; // guarda variavel de retorno da criação do socket no struct
			
			//	indice++;
 			
 			read(resposta_server,buff,4096); // le o nome do usuario
 		
 			write(resposta_server,buff,4096); // envia o nome do usuario
 
 			for(i=0;i < strlen(buff);i++)
 			{
 				clientes[indice].nome[i] = buff[i]; // guarda o nome no buff
 			}
 			printf("%s!!!!!!\n",clientes[indice].nome);
 			indice++;
 			
 			printf("Cliente conectado com sucesso! %s seu identificador eh %d\n", buff, indice);
 			str_echo(resposta_server,buff);
 			exit(0);
 		}
 		else
 		{
 			printf("falha no fork!");
 		}
 		close(resposta_server);
 	}
 	// acho que tá tudo direitinho...
	// acho que o programa cai no loop quando executado.
	return 0;
}
