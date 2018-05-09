#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])

{
	GtkWidget *window;
	GtkWidget *botao1;
	GtkWidget *botao2;
	GtkWidget *botao3;
	GtkWidget *boxv1;


	gtk_init(&argc,&argv);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(G_OBJECT(window),"destroy",G_CALLBACK(gtk_main_quit),NULL);
	gtk_container_set_border_width(GTK_CONTAINER(window),200);
	gtk_window_set_title(GTK_WINDOW(window),"RSA");

	boxv1 = gtk_vbox_new(FALSE,0);
	gtk_container_add(GTK_CONTAINER(window),boxv1);

	botao1 = gtk_button_new_with_label("Gerar chave pública");
	//g_signal_connect(G_OBJECT (botao1),"clicked",G_CALLBACK(gerar_chave_publica),NULL);
	gtk_box_pack_start(GTK_BOX(boxv1),botao1,FALSE,FALSE,0);

	botao2 = gtk_button_new_with_label("Criptografar");
	//g_signal_connect(G_OBJECT (botao2),"clicked",G_CALLBACK(criptogrfar),NULL);// função
	gtk_box_pack_start(GTK_BOX(boxv1),botao2,FALSE,FALSE,0);

	botao3 = gtk_button_new_with_label("Descriptografar");
	//g_signal_connect(G_OBJECT (botao3),"clicked",G_CALLBACK(descriptografar),NULL);// função
	gtk_box_pack_start(GTK_BOX(boxv1),botao3,FALSE,FALSE,0);

	gtk_widget_show_all(window);

	gtk_main();

	return 0;
}