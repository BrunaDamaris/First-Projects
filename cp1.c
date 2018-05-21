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

void str_cli(FILE *fp, int meusocket,GtkWidget *widget,GtkWidget *entrada)
{
	char msgreceb[4096],msgenviada[4096],user1[500]; // dois chars
	int i,p;
	int lcount=0;
  	char *msg;
  	const char *mensagem;
  	gsize bytes_read = 0;
  	gsize bytes_written = 0;
	GError *error = NULL;

  	u = converttostring(gtk_entry_get_text(GTK_ENTRY(user)));;

  	strcpy(user1,u);
  	//printf("%s!\n",user1);
	
	write(meusocket, user1, strlen(user1));

	read(meusocket, msgreceb, 4096);


	//bzero(msgenviad,sizeof(msgenviad));
 	
	msg = converttostring(gtk_entry_get_text(GTK_ENTRY(entrada)));
	strcpy(msgenviada,msg);
	//printf("%s\n",msgenviada);

	strcat(user1,msgenviada);

	//printf("<%s>%s\n", user,msgenviad);
	for(i=0;i<strlen(user1)+1;i++)
  	{
  		user1[strlen(user1)-1]= ':';

   	 	if(user1[i] == '\n') user1[i] = '#';
  	}
		
	write(meusocket, msgenviada, strlen(msgenviada));
	
  	read(meusocket, msgreceb, 4096);

  	for(i=0;i<strlen(msgreceb);i++)
  	{
   	 	if(msgreceb[i] == '#') msgreceb[i] = '\n';
  	}
  	mensagem = g_convert (msgreceb, -1, "UTF-8", "ISO-8859-1", &bytes_read, &bytes_written, &error);
  	gtk_text_buffer_get_iter_at_line_index(saida,&inicio,lcount,0);
  	lcount++;
  	gtk_text_buffer_insert(saida,&inicio,mensagem,-1);
}

char imprimir( GtkWidget *widget,GtkWidget *entrada)
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
	hj = gtk_scrolled_window_get_hadjustment(GTK_SCROLLED_WINDOW(inside));
	gtk_adjustment_set_value(hj,hj->upper);
	gtk_scrolled_window_set_hadjustment(GTK_SCROLLED_WINDOW(inside),hj);
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
	gtk_entry_set_max_length(GTK_ENTRY(texto),180);//tamanho do texto
	//g_signal_connect(texto,"activate",G_CALLBACK(imprimir),texto);//chama uma função que vai imprimir o texto
	gtk_box_pack_start(GTK_BOX(box3),texto,FALSE,FALSE,0);//coloca na caixa

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
