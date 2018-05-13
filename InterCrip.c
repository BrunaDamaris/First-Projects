#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
FILE *out;
GtkWidget *p;
GtkWidget *q;
GtkWidget *label_out;

int primo(long int a, long int b)
{
	long int d;
	int achei= 0, achei2=0;
	for(d=2; d*d<=a && !achei;d++)
	{
		if(a%d==0)
		{
			achei = 1;
			break;
		}
	}
	for(d=2; d*d<=b && !achei2;d++)
	{
		if(b%d==0)
		{
			achei2 = 1;
			break;
		}
	}
	if(!achei && !achei2)
	{
		return 1;
	}
	else
	{
		return 0;
	}

}

int firstnumbern(GtkButton *button, gpointer data)
{
	long int firstnumber=0,secondnumber=0,npublickey=0;

	firstnumber=atol(gtk_entry_get_text(GTK_ENTRY(p)));

	secondnumber=atol(gtk_entry_get_text(GTK_ENTRY(q)));

	npublickey=firstnumber*secondnumber;

	/*out = fopen("criptout","w+");
	fwrite(&npublickey,sizeof(long int),1,out);
	fclose(out);*/

	if(npublickey && primo(firstnumber,secondnumber) !=0 )
	{
		char text[10] = "Done!";
		gtk_label_set_text(GTK_LABEL(label_out),text);
		printf("%ld\n",npublickey);
		
	}
	else
	{
		char text1[10] = "Try again";
		gtk_label_set_text(GTK_LABEL(label_out),text1);
	}
	
}

void gerar_chave_publica()
{
	GtkWidget *window;
	GtkWidget *boxv1;
	GtkWidget *label;
	GtkWidget *label1;
	GtkWidget * button;
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_container_set_border_width(GTK_CONTAINER(window),100);
	gtk_window_set_title(GTK_WINDOW(window),"Chave Pública");

	boxv1 = gtk_vbox_new(FALSE,0);
	gtk_container_add(GTK_CONTAINER(window),boxv1);

	label = gtk_label_new("Digite um número primo:");
	gtk_box_pack_start(GTK_BOX(boxv1),label,FALSE,FALSE,0);

	p = gtk_entry_new();
	gtk_entry_set_max_length(GTK_ENTRY(p),10);
	gtk_box_pack_start(GTK_BOX(boxv1),p,FALSE,FALSE,0);

	label = gtk_label_new("Digite outro número primo:");
	gtk_box_pack_start(GTK_BOX(boxv1),label,FALSE,FALSE,0);

	q = gtk_entry_new();
	gtk_entry_set_max_length(GTK_ENTRY(q),10);
	gtk_box_pack_start(GTK_BOX(boxv1),q,FALSE,FALSE,0);

	button = gtk_button_new_with_label("Go!");
	gtk_box_pack_start(GTK_BOX(boxv1),button,FALSE,FALSE,0);
	g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(firstnumbern), NULL);

	label_out = gtk_label_new("Waiting...");
	gtk_box_pack_start(GTK_BOX(boxv1),label_out,FALSE,FALSE,0);

	gtk_widget_show_all(window);
}

/*void criptografar(GtkWidget *widget,gpointer data)
{
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_container_set_border_width(GTK_CONTAINER(window),100);
	gtk_window_set_title(GTK_WINDOW(window),"Criptografia");
}

void descriptografar(GtkWidget *widget,gpointer data)
{
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_container_set_border_width(GTK_CONTAINER(window),100);
	gtk_window_set_title(GTK_WINDOW(window),"Descriptografia");
}*/

int main(int argc, char *argv[])

{
	GtkWidget *window;
	GtkWidget *botao1;
	GtkWidget *botao2;
	GtkWidget *botao3;
	GtkWidget *label;
	GtkWidget *boxv1;
	int n,k=1,e=1;
	char s[200];

	gtk_init(&argc,&argv);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(G_OBJECT(window),"destroy",G_CALLBACK(gtk_main_quit),NULL);
	gtk_container_set_border_width(GTK_CONTAINER(window),200);
	gtk_window_set_title(GTK_WINDOW(window),"RSA");

	boxv1 = gtk_vbox_new(FALSE,0);
	gtk_container_add(GTK_CONTAINER(window),boxv1);

	label = gtk_label_new("Selecione uma opção :");
	gtk_box_pack_start(GTK_BOX(boxv1),label,FALSE,FALSE,0);

	botao1 = gtk_button_new_with_label("Gerar chave pública");
	g_signal_connect(G_OBJECT (botao1),"clicked",G_CALLBACK(gerar_chave_publica),NULL);
	gtk_box_pack_start(GTK_BOX(boxv1),botao1,FALSE,FALSE,0);

	botao2 = gtk_button_new_with_label("Criptografar");
	//g_signal_connect(G_OBJECT (botao2),"clicked",G_CALLBACK(criptografar),NULL);// função
	gtk_box_pack_start(GTK_BOX(boxv1),botao2,FALSE,FALSE,0);

	botao3 = gtk_button_new_with_label("Descriptografar");
	//g_signal_connect(G_OBJECT (botao3),"clicked",G_CALLBACK(descriptografar),NULL);// função
	gtk_box_pack_start(GTK_BOX(boxv1),botao3,FALSE,FALSE,0);

	gtk_widget_show_all(window);

	gtk_main();

	return 0;
}