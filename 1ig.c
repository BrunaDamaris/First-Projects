#include <gtk/gtk.h>

void clique1( GtkWidget *widget,gpointer data)
{
	GtkWidget *janela1;

	janela1 = gtk_window_new (GTK_WINDOW_TOPLEVEL); // cria janela
	gtk_container_set_border_width(GTK_CONTAINER(janela1),200);//ajuste de altura e largura
	gtk_window_set_title(GTK_WINDOW(janela1),"Sala 1"); // nome da janela
	
  	gtk_widget_show_all(janela1);
}
void clique2( GtkWidget *widget,gpointer data)
{
	GtkWidget *janela1;

	janela1 = gtk_window_new (GTK_WINDOW_TOPLEVEL); // cria janela
	gtk_container_set_border_width(GTK_CONTAINER(janela1),200);//ajuste de altura e largura
	gtk_window_set_title(GTK_WINDOW(janela1),"Sala 2"); // nome da janela
 
  	gtk_widget_show_all(janela1);
}
void clique3( GtkWidget *widget,gpointer data)
{
	GtkWidget *janela1;

	janela1 = gtk_window_new (GTK_WINDOW_TOPLEVEL); // cria janela
	gtk_container_set_border_width(GTK_CONTAINER(janela1),200);//ajuste de altura e largura
	gtk_window_set_title(GTK_WINDOW(janela1),"Sala 3"); // nome da janela
 
  	gtk_widget_show_all(janela1);
}

int main(int  argc, char *argv[])
{
	GtkWidget *janela; //atribui o widget window
	GtkWidget *botao;// atribui um botão
	GtkWidget *botao1;
	GtkWidget *botao2; 
	GtkWidget *box1; // "caixa" para colocar vários gadgets em uma pagina

	gtk_init(&argc,&argv); //pointers do gtk_init

	janela = gtk_window_new (GTK_WINDOW_TOPLEVEL); // cria janela
	g_signal_connect(G_OBJECT(janela),"destroy",G_CALLBACK(gtk_main_quit),NULL);// destroi quando clica no botão de fechar
	gtk_container_set_border_width(GTK_CONTAINER(janela),300);//ajuste de altura e largura
	gtk_window_set_title(GTK_WINDOW(janela),"teste 1"); // nome da janela

	box1 = gtk_vbox_new(FALSE,0); // cria a caixa
	gtk_container_add(GTK_CONTAINER(janela),box1); //coloca caixa na janela

	botao = gtk_button_new_with_label("Sala 1");
	g_signal_connect(G_OBJECT (botao),"clicked",G_CALLBACK(clique1),NULL);// função
	gtk_box_pack_start(GTK_BOX(box1),botao,FALSE,FALSE,0);// coloca botao na caixa
	
	botao1 = gtk_button_new_with_label("Sala 2");
	g_signal_connect(G_OBJECT (botao1),"clicked",G_CALLBACK(clique2),NULL);// função
	gtk_box_pack_start(GTK_BOX(box1),botao1,FALSE,FALSE,0);

	botao2 = gtk_button_new_with_label("Sala 3");
	g_signal_connect(G_OBJECT (botao2),"clicked",G_CALLBACK(clique3),NULL);// função
	gtk_box_pack_start(GTK_BOX(box1),botao2,FALSE,FALSE,0);

	gtk_widget_show_all(box1);//mostra a box
	gtk_widget_show_all(janela);//mostra a janela
   	gtk_main (); // (loop) espera interações com a interface e executa o que é solicitado
	
	return 0;
}