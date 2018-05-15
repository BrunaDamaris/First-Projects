#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
FILE *out;
GtkWidget *p;
GtkWidget *q;
GtkWidget *e;
GtkWidget *label_out;
GtkWidget *text;

long int enumber;
long int npublickey;
char *cripto;
const gchar *realtext;

char *strdup (const char *s) 
{
    char *d = malloc (strlen (s) + 1);   // Space for length plus nul
    if (d == NULL) return NULL;          // No memory
    strcpy (d,s);                        // Copy the characters
    return d;                            // Return the new string
}
//euclides function says if the number E and (p-1)(q-1) are co-prime, if x= 1, so they are
//else, function reads another number E and send again to euclides
int euclides(int x, int y)
{
    if(y==0)
    {
       return x;
    }
    return euclides(y, x%y);
}
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
	long int firstnumber=0,secondnumber=0,y=0,m=0,validate;

	firstnumber=atol(gtk_entry_get_text(GTK_ENTRY(p)));

	secondnumber=atol(gtk_entry_get_text(GTK_ENTRY(q)));

	enumber=atol(gtk_entry_get_text(GTK_ENTRY(e)));

	npublickey=firstnumber*secondnumber;
	y= (firstnumber-1)*(secondnumber-1);
	while(m!=1)
	{
		m = euclides(enumber,y);
		if(m==1)
		{
			validate++;
			break;
		}
	}
	out = fopen("chave_publica.txt","w+");
	fprintf(out,"N: %ld E: %ld\n",npublickey,enumber); 
	fclose(out);
	if(npublickey && primo(firstnumber,secondnumber) !=0 && validate)
	{
		char text[100] = "Valid numbers!";
		gtk_label_set_text(GTK_LABEL(label_out),text);
		printf("%ld\n",npublickey);
		
	}
	else
	{
		char text1[100] = "Hint: Enter a prime number next to a multiple of %d\n";
		gtk_label_set_text(GTK_LABEL(label_out),text1);
	}
	
}
void gerar_chave_publica()
{
	GtkWidget *window;
	GtkWidget *boxv1;
	GtkWidget *label;
	GtkWidget *label1;
	GtkWidget *label2;
	GtkWidget * button;
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_container_set_border_width(GTK_CONTAINER(window),100);
	gtk_window_set_title(GTK_WINDOW(window),"Chave Pública");

	boxv1 = gtk_vbox_new(FALSE,0);
	gtk_container_add(GTK_CONTAINER(window),boxv1);

	label = gtk_label_new("Enter a prime number P:");
	gtk_box_pack_start(GTK_BOX(boxv1),label,FALSE,FALSE,0);

	p = gtk_entry_new();
	gtk_entry_set_max_length(GTK_ENTRY(p),10);
	gtk_box_pack_start(GTK_BOX(boxv1),p,FALSE,FALSE,0);

	label = gtk_label_new("Enter a prime number Q:");
	gtk_box_pack_start(GTK_BOX(boxv1),label,FALSE,FALSE,0);

	q = gtk_entry_new();
	gtk_entry_set_max_length(GTK_ENTRY(q),10);
	gtk_box_pack_start(GTK_BOX(boxv1),q,FALSE,FALSE,0);

	label2 = gtk_label_new("Enter a number that will be E:");
	gtk_box_pack_start(GTK_BOX(boxv1),label2,FALSE,FALSE,0);

	e = gtk_entry_new();
	gtk_entry_set_max_length(GTK_ENTRY(e),10);
	gtk_box_pack_start(GTK_BOX(boxv1),e,FALSE,FALSE,0);

	button = gtk_button_new_with_label("Go!");
	gtk_box_pack_start(GTK_BOX(boxv1),button,FALSE,FALSE,0);
	g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(firstnumbern), NULL);

	label_out = gtk_label_new("Waiting...");
	gtk_box_pack_start(GTK_BOX(boxv1),label_out,FALSE,FALSE,0);

	gtk_widget_show_all(window);
}
void criptografar(GtkWidget *widget,gpointer data)
{
	cripto = strdup(realtext);
	printf("%s\n",cripto);
}
void wcriptografar(GtkWidget *widget,gpointer data)
{
	GtkWidget *window;
	GtkWidget *boxv1;
	GtkWidget *label;
	GtkWidget *label1;
	GtkWidget * button;


	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_container_set_border_width(GTK_CONTAINER(window),100);
	gtk_window_set_title(GTK_WINDOW(window),"Criptografia");

	boxv1 = gtk_vbox_new(FALSE,0);
	gtk_container_add(GTK_CONTAINER(window),boxv1);

	label = gtk_label_new("Type something!!:");
	gtk_box_pack_start(GTK_BOX(boxv1),label,FALSE,FALSE,0);

	text = gtk_entry_new();
	gtk_entry_set_max_length(GTK_ENTRY(text),10);
	gtk_box_pack_start(GTK_BOX(boxv1),text,FALSE,FALSE,0);

	realtext = (gtk_entry_get_text(GTK_ENTRY(text)));
	g_signal_connect(text,"activate",G_CALLBACK(criptografar),text);
	
	gtk_widget_show_all(window);
}	
/*void descriptografar(GtkWidget *widget,gpointer data)
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

	gtk_init(&argc,&argv);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(G_OBJECT(window),"destroy",G_CALLBACK(gtk_main_quit),NULL);
	gtk_container_set_border_width(GTK_CONTAINER(window),200);
	gtk_window_set_title(GTK_WINDOW(window),"RSA");

	boxv1 = gtk_vbox_new(FALSE,0);
	gtk_container_add(GTK_CONTAINER(window),boxv1);

	label = gtk_label_new("Select an option:");
	gtk_box_pack_start(GTK_BOX(boxv1),label,FALSE,FALSE,0);

	botao1 = gtk_button_new_with_label("Gerar chave pública");
	g_signal_connect(G_OBJECT (botao1),"clicked",G_CALLBACK(gerar_chave_publica),NULL);
	gtk_box_pack_start(GTK_BOX(boxv1),botao1,FALSE,FALSE,0);

	botao2 = gtk_button_new_with_label("Criptografar");
	g_signal_connect(G_OBJECT (botao2),"clicked",G_CALLBACK(wcriptografar),NULL);// função
	gtk_box_pack_start(GTK_BOX(boxv1),botao2,FALSE,FALSE,0);

	botao3 = gtk_button_new_with_label("Descriptografar");
	//g_signal_connect(G_OBJECT (botao3),"clicked",G_CALLBACK(descriptografar),NULL);// função
	gtk_box_pack_start(GTK_BOX(boxv1),botao3,FALSE,FALSE,0);

	gtk_widget_show_all(window);

	gtk_main();

	return 0;
}
