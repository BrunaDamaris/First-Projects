#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>

GtkWidget *view;
GtkTextBuffer *saida;

char imprimir( GtkWidget *widget,GtkWidget *entrada)
{
	int lcount;
  	const gchar *mensagem;
  	mensagem = gtk_entry_get_text(GTK_ENTRY(entrada));
  	gtk_text_buffer_set_text(saida,mensagem,-1);
  	return FALSE;
}

void clique1( GtkWidget *widget,gpointer data)
{
	GtkWidget *inside;
	GtkWidget *janela1;
	GtkWidget *box2;
	GtkWidget *box3;
	GtkWidget *texto;
	GtkWidget *send;
	GtkTextIter inicio,fim;
	//gchar *this;
	//int i=0;

	janela1 = gtk_window_new (GTK_WINDOW_TOPLEVEL); // cria janela
	gtk_container_set_border_width(GTK_CONTAINER(janela1),200);//ajuste de altura e largura
	gtk_window_set_title(GTK_WINDOW(janela1),"Sala i"); // nome da janela

	box2 = gtk_vbox_new(FALSE,0);
	gtk_container_add(GTK_CONTAINER(janela1),box2);

	inside = gtk_scrolled_window_new(NULL,NULL);
	gtk_box_pack_start(GTK_BOX(box2),inside,FALSE,FALSE,0);// swindow dentro da caixa

	view = gtk_text_view_new();//cria um novo coiso com proprieades de texto

	saida=gtk_text_view_get_buffer(GTK_TEXT_VIEW(view));// retorna o buffer do view
	gtk_widget_set_size_request(view,500,100);
	//gtk_text_mark_new(NULL,0);
	gtk_text_buffer_get_bounds(saida,&inicio,&fim);
	gtk_container_add(GTK_CONTAINER(inside),view);//view dentro do scrolled window

	texto = gtk_entry_new();// para entrada de texto
	gtk_entry_set_max_length(GTK_ENTRY(texto),50);//tamanho do texto
	g_signal_connect(texto,"activate",G_CALLBACK(imprimir),texto);//chama uma função que vai imprimir o texto
	gtk_box_pack_start(GTK_BOX(box2),texto,FALSE,FALSE,0);//coloca na caixa

	send = gtk_button_new_with_label("Enviar");
	//g_signal_connect(G_OBJECT (send),"clicked",G_CALLBACK(cc),NULL);// função
	gtk_box_pack_start(GTK_BOX(box2),send,FALSE,FALSE,0);
	
  	gtk_widget_show_all(janela1);
}

int main(int  argc, char *argv[])
{
	GtkWidget *label;
	GtkWidget *janela; //atribui o widget window
	GtkWidget *botao;// atribui um botão
	GtkWidget *botao1;
	GtkWidget *botao2; 
	GtkWidget *box1; // "caixa" para colocar vários widgets em uma pagina

	gtk_init(&argc,&argv); //pointers do gtk_init

	janela = gtk_window_new (GTK_WINDOW_TOPLEVEL); // cria janela
	g_signal_connect(G_OBJECT(janela),"destroy",G_CALLBACK(gtk_main_quit),NULL);// destroi quando clica no botão de fechar
	gtk_container_set_border_width(GTK_CONTAINER(janela),300);//ajuste de altura e largura
	gtk_window_set_title(GTK_WINDOW(janela),"teste 1"); // nome da janela

	box1 = gtk_vbox_new(FALSE,0); // cria a caixa
	gtk_container_add(GTK_CONTAINER(janela),box1); //coloca caixa na janela

	label = gtk_label_new("Salas Disponiveis");
	gtk_box_pack_start(GTK_BOX(box1),label,FALSE,FALSE,0);

	botao = gtk_button_new_with_label("Sala 1");
	g_signal_connect(G_OBJECT (botao),"clicked",G_CALLBACK(clique1),NULL);// função
	gtk_box_pack_start(GTK_BOX(box1),botao,FALSE,FALSE,0);// coloca botao na caixa
	
	botao1 = gtk_button_new_with_label("Sala 2");
	g_signal_connect(G_OBJECT (botao1),"clicked",G_CALLBACK(clique1),NULL);// função
	gtk_box_pack_start(GTK_BOX(box1),botao1,FALSE,FALSE,0);

	botao2 = gtk_button_new_with_label("Sala 3");
	g_signal_connect(G_OBJECT (botao2),"clicked",G_CALLBACK(clique1),NULL);// função
	gtk_box_pack_start(GTK_BOX(box1),botao2,FALSE,FALSE,0);

	gtk_widget_show_all(box1);//mostra a box
	gtk_widget_show_all(janela);//mostra a janela
   	gtk_main (); // (loop) espera interações com a interface e executa o que é solicitado
	
	return 0;
}
