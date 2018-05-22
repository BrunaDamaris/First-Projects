#include <gtk/gtk.h>
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

GtkWidget *view;
GtkTextBuffer *saida;
GtkTextIter inicio,fim;
GtkWidget *user;
char *u;
int meusocket;
struct sockaddr_in servaddr;

char *converttostring(const char *s) 
{
    char *m = malloc (strlen (s) + 1);   // Space for length plus nul
    if (m == NULL) return NULL;          // No memory
    strcpy (m,s);                       // Copy the characters
    return m;                            // Return the new string
}

void str_cli(FILE *fp,int meusocket,GtkWidget *widget,GtkWidget *entrada)
{
	char msgenviada[4096], msgreceb[4096], user1[4096],msgant[4096],msg[4096],newmsg[4096]; // dois chars
	int i=0,j=0, ult;
	int p,l=0;
  	char *msg1;
  	const char *mensagem;
  	long int lcount=0;
  	gsize bytes_read = 0;
  	gsize bytes_written = 0;
	GError *error = NULL;
  
  	u = converttostring(gtk_entry_get_text(GTK_ENTRY(user)));;

  	strcpy(user1,u);
  	strcat(user1,"\n");
  	printf("%s!!@@\n", user1);
  	//printf("%d!\n",strlen(user1));
  	//printf("%s!\n",user1);
	
	write(meusocket, user1, strlen(user1));

	read(meusocket, msgreceb, 4096);

	for(i=0;msg[i] != '\0';i++)
    {
    	msg[i] = 0;
    	msgenviada[i] = 0;
    }
    //printf("ssss\n");

    msg1 = converttostring(gtk_entry_get_text(GTK_ENTRY(entrada)));
	strcpy(msgenviada,msg1);
	strcat(msgenviada,"\n");

	printf("%s&&\n",user1);

    for(i=0;user1[i] != '\n';i++)
    {
    	msg[i] = user1[i];
    	//printf("%c!",user1[i]);
    }
     printf("%s\n",msg);
   	msg[i] = ':';
    i++;
    msg[i] = '\n';

    for(j=0;msgenviada[j] != '\n';j++)
    {
    	msg[i] = msgenviada[j];
    	//printf("%d*\n",j);
    	i++;
    }
  	msg[i] = '\n';
  	printf("%s!!\n",msg);
  	
   	for(i=0;i<strlen(msg);i++)
  	{
   	 	if(msg[i] == '\n') msg[i] = '#';
  	}
  	strcat(msg,"\n");
  	printf("%s!@!\n",msg);
	write(meusocket,msg,strlen(msg));
	

  	//pt.2
  	read(meusocket, msgreceb, 4096);

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
  			newmsg[l]=msgreceb[i];
  			l++;
  			//	printf("< %c >", msgant[i]);
  		}
  	}
  	strcat(newmsg,"\n");

	mensagem = g_convert(newmsg, -1, "UTF-8", "ISO-8859-1", &bytes_read, &bytes_written, &error);
  	gtk_text_buffer_get_iter_at_line_index(saida,&inicio,lcount,0);
  	lcount++;
  	gtk_text_buffer_insert(saida,&inicio,mensagem,-1);

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
  	i=j=0;
  	//printf("%s\n",newmsg);
  	//
		//printf(" %s\n", msgreceb);//printa mensagem recebid
}

char imprimir(GtkWidget *widget,GtkWidget *entrada)
{
	str_cli(stdin,meusocket,widget,entrada);
  	return 0;
}

void clique1( GtkWidget *widget,gpointer data)
{
	GtkWidget *dialog_user;
	GtkWidget *inside;
	GtkWidget *janela1;
	GtkWidget *box2;
	GtkWidget *box3;
	GtkWidget *texto;
	GtkWidget *send;
	GtkAdjustment *hj;
	//GtkIMContext * emo;
	//GtkAdjustment *
	// GtkDialogFlags flags = GTK_DIALOG_MODAL|GTK_DIALOG_DESTROY_WITH_PARENT;
	// const gchar *this;
	// GtkWidget *label_user;

	janela1 = gtk_window_new(GTK_WINDOW_TOPLEVEL); // cria janela
	gtk_container_set_border_width(GTK_CONTAINER(janela1),200);//ajuste de altura e largura
	gtk_window_set_title(GTK_WINDOW(janela1),"Sala"); // nome da janela

	box2 = gtk_vbox_new(FALSE,0);
	gtk_container_add(GTK_CONTAINER(janela1),box2);

	// dialog_user = gtk_dialog_new_with_buttons("Go!",janela1,flags,_("_OK"),_("_Cancel"),NULL);
	// gtk_box_pack_start(GTK_BOX(box2),dialog_user,FALSE,FALSE,FALSE,0);

	inside = gtk_scrolled_window_new(NULL,NULL);
	//hj = gtk_scrolled_window_get_hadjustment(GTK_SCROLLED_WINDOW(inside));
	/*gtk_adjustment_set_value(hj,hj->upper);
	gtk_scrolled_window_set_hadjustment(GTK_SCROLLED_WINDOW(inside),hj);*/
	gtk_box_pack_start(GTK_BOX(box2),inside,FALSE,FALSE,0);

	view = gtk_text_view_new();//cria um novo coiso com proprieades de texto

	saida=gtk_text_view_get_buffer(GTK_TEXT_VIEW(view));// retorna o buffer do view
	gtk_widget_set_size_request(view,500,100); 	
	//gtk_text_view_get_hadjustment (GtkTextView *text_view);
	//gtk_editable_set_editable(GTK_EDITABLE(view),FALSE);
	//gtk_text_mark_new(NULL,0);
	gtk_container_add(GTK_CONTAINER(inside),view); //view dentro do scrolled window

	box3 = gtk_hbox_new(FALSE,0);
	gtk_box_pack_start(GTK_BOX(box2),box3,FALSE,FALSE,0);

	texto = gtk_entry_new();// para entrada de texto
	gtk_entry_set_max_length(GTK_ENTRY(texto),1000);//tamanho do texto
	//g_signal_connect(texto,"activate",G_CALLBACK(imprimir),texto);//chama uma função que vai imprimir o texto
	gtk_box_pack_start(GTK_BOX(box3),texto,FALSE,FALSE,0);//coloca na caixa

	//emo = gtk_im_context_simple_new();
	//gtk_im_context_simple_add_table (GTK_IM_CONTEXT_SIMPLE(emo), guint16 *data,GTK_MAX_COMPOSE_LEN,gint n_seqs);

	//insert_emoji(); 

	send = gtk_button_new_with_label("Enviar");
	g_signal_connect(G_OBJECT(send),"clicked",G_CALLBACK(imprimir),texto);// função
	gtk_box_pack_start(GTK_BOX(box3),send,FALSE,FALSE,0);
	
  	gtk_widget_show_all(janela1);
}

int main(int  argc, char *argv[])
{
	GtkWidget *label;
	GtkWidget *janela; //atribui o widget window
	GtkWidget *fixed;
	GtkWidget *botao1;// atribui um botão
	GtkWidget *botao2;
	GtkWidget *botao3;
	GtkWidget *botao4;
	GtkWidget *botao5; 
	GtkWidget *boxv1; // "caixa" para colocar vários widgets em uma pagina
	GtkWidget *boxh1;
	GtkWidget *boxh2;
	GtkWidget *boxh3;
	GtkWidget *boxh4;
	GtkWidget *boxh5;
	GtkWidget *boxh6;

	meusocket = socket(AF_INET, SOCK_STREAM, 0); // abre o socket

	bzero(&servaddr, sizeof(servaddr));

	servaddr.sin_family = AF_INET; // familia do socket

	servaddr.sin_port = htons(9503); // porta do socket

	inet_pton(AF_INET, argv[1], &servaddr.sin_addr); // 
	
	connect(meusocket, (SA *) &servaddr, sizeof(servaddr)); //conetcando cliente em determidado socket,
															// usando o valore de retorno do socket, a suct do socket e o tamanho 
															// da struct severaddr 

	gtk_init(&argc,&argv); //pointers do gtk_init


	janela = gtk_window_new(GTK_WINDOW_TOPLEVEL); // cria janela
	g_signal_connect(G_OBJECT(janela),"destroy",G_CALLBACK(gtk_main_quit),NULL);// destroi quando clica no botão de fechar
	gtk_container_set_border_width(GTK_CONTAINER(janela),200);//ajuste de altura e largura
	gtk_window_set_title(GTK_WINDOW(janela),"teste 1"); // nome da janela

	fixed = gtk_fixed_new();
	gtk_container_add(GTK_CONTAINER(janela),fixed);

	boxv1 = gtk_vbox_new(FALSE,0); // cria a caixa
	gtk_fixed_put(GTK_FIXED(fixed),boxv1,10,10);

	boxh6 = gtk_hbox_new(FALSE,0);
	gtk_box_pack_start(GTK_BOX(boxv1),boxh6,TRUE,TRUE,0);

	boxh1 = gtk_hbox_new(FALSE,0);
	gtk_box_pack_start(GTK_BOX(boxv1),boxh1,TRUE,TRUE,0);

	/*boxh2 = gtk_hbox_new(FALSE,0);
	gtk_box_pack_start(GTK_BOX(boxv1),boxh2,TRUE,TRUE,0);
	boxh3 = gtk_hbox_new(FALSE,0);
	gtk_box_pack_start(GTK_BOX(boxv1),boxh3,TRUE,TRUE,0);
	boxh4 = gtk_hbox_new(FALSE,0);
	gtk_box_pack_start(GTK_BOX(boxv1),boxh4,TRUE,TRUE,0);
	boxh5 = gtk_hbox_new(FALSE,0);
	gtk_box_pack_start(GTK_BOX(boxv1),boxh5,TRUE,TRUE,0);*/

	user = gtk_entry_new();// para entrada de texto
	gtk_entry_set_max_length(GTK_ENTRY(user),20);
	gtk_box_pack_start(GTK_BOX(boxh1),user,FALSE,FALSE,0);

	label = gtk_label_new("Username:");
	gtk_box_pack_start(GTK_BOX(boxh6),label,TRUE,TRUE,0);

	botao1 = gtk_button_new_with_label("Entrar ?");
	g_signal_connect(G_OBJECT (botao1),"clicked",G_CALLBACK(clique1),NULL);// função
	gtk_box_pack_start(GTK_BOX(boxh1),botao1,FALSE,FALSE,0);// coloca botao na caixa
	
	/*botao2 = gtk_button_new_with_label("Sala 2");
	g_signal_connect(G_OBJECT (botao2),"clicked",G_CALLBACK(clique1),NULL);// função
	gtk_box_pack_start(GTK_BOX(boxh2),botao2,FALSE,FALSE,0);
	botao3 = gtk_button_new_with_label("Sala 3");
	g_signal_connect(G_OBJECT (botao3),"clicked",G_CALLBACK(clique1),NULL);// função
	gtk_box_pack_start(GTK_BOX(boxh3),botao3,FALSE,FALSE,0);
	
	botao4 = gtk_button_new_with_label("Sala 4");
	g_signal_connect(G_OBJECT (botao4),"clicked",G_CALLBACK(clique1),NULL);// função
	gtk_box_pack_start(GTK_BOX(boxh4),botao4,FALSE,FALSE,0);
	botao5 = gtk_button_new_with_label("Sala 5");
	g_signal_connect(G_OBJECT (botao5),"clicked",G_CALLBACK(clique1),NULL);// função
	gtk_box_pack_start(GTK_BOX(boxh5),botao5,FALSE,FALSE,0);*/

	gtk_widget_show_all(fixed);//mostra a box
	gtk_widget_show_all(janela);//mostra a janela
   	gtk_main (); // (loop) espera interações com a interface e executa o que é solicitado
	
	return 0;
}
