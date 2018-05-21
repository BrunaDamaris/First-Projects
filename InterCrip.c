#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max 100000

// Global
FILE *out;
FILE *out1;
FILE *out2;
FILE *out_d;
GtkWidget *p;
GtkWidget *q;
GtkWidget *e;
GtkWidget *en;
GtkWidget *n;
GtkWidget *label_out;
GtkWidget *text;
GtkWidget *text3;
GtkWidget *label1;
GtkWidget *label2;
GdkColor color;
GdkColor color1;

long long int enumber;
long long int npublickey;
long long int phi=0;
long long int num_m[max];
long long int dnumber;
long int len,inde,letter,countlen=0,l=0;
char *rt;
char cripto[max];
const char *realtext;

//Global

void converttolongint(char *str)
{
    long long int num, i = 0;
    int l;
    while(sscanf(str, "%Ld%n", &num, &l) == 1)
    {
	    num_m[i]=num;
	    str+=l;
	    i++;
    }
}
int inverso(long long int ex)
{
	long long int x;
	for(x=1;x<=phi;x++)
	{
		if((ex*x)%phi==1) return x;
	}
}
char *converttostring(const char *s) 
{
    char *rt = malloc (strlen (s) + 1);
    if (rt == NULL) return NULL;
    strcpy (rt,s);
    return rt;
}
long long int fastexpmod(long long int a,long long int x,long long int m1)
{
    if(x==0) return 1;
    else if(x%2==0)
    {
    	long int x1 = fastexpmod(a,x/2,m1);
    	return (x1*x1)%m1; 
    }
    else return(a%m1*fastexpmod(a,x-1,m1))%m1;
}
//euclides function says if the number E and (p-1)(q-1) are co-prime, if x= 1, so they are
//else, function reads another number E and send again to euclides
long long int euclides(long long int x,long long int phi)
{
    if(phi==0)
    {
       return x;
    }
    return euclides(phi, x%phi);
}
long long int primo(long long int a,long long int b)
{
	long long int d;
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
void criptografar(GtkWidget *widget,gpointer data)
{
	long long int numeric_m[max];
	long long int enr,nkey;

	nkey  = atol(gtk_entry_get_text(GTK_ENTRY(n)));

	enr = atol(gtk_entry_get_text(GTK_ENTRY(en)));
	
	rt = converttostring(gtk_entry_get_text(GTK_ENTRY(text)));
	strcpy(cripto,rt);
	len = strlen(cripto);

	for(inde=0;inde<len;inde++)
	{
		letter = cripto[inde];
		numeric_m[inde] = letter;
	}
	for(inde=0;inde<len;inde++)
	{
		out1 = fopen("criptografado.txt","a+");
		numeric_m[inde] = fastexpmod(numeric_m[inde],enr,nkey);
		fprintf(out1,"%Ld ",numeric_m[inde]);
		fclose(out1);
	}
	countlen++;

	char text1[100] = "Criptografado!!";
	gtk_label_set_text(GTK_LABEL(label1),text1);
}
void wcriptografar(GtkWidget *widget,gpointer data)
{
	GtkWidget *window;
	GtkWidget *boxv1;
	GtkWidget *label;
	GtkWidget *label_e;
	GtkWidget *label_n;
	GtkWidget * button;

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_container_set_border_width(GTK_CONTAINER(window),100);
	gtk_window_set_title(GTK_WINDOW(window),"Criptografia");

	boxv1 = gtk_vbox_new(FALSE,0);
	gtk_container_add(GTK_CONTAINER(window),boxv1);

	label_n = gtk_label_new("Type the user public key:");
	gtk_box_pack_start(GTK_BOX(boxv1),label_n,FALSE,FALSE,0);

	n = gtk_entry_new();
	gtk_entry_set_max_length(GTK_ENTRY(n),10000);
	gtk_box_pack_start(GTK_BOX(boxv1),n,FALSE,FALSE,0);

	label_e = gtk_label_new("Type the user public key:");
	gtk_box_pack_start(GTK_BOX(boxv1),label_e,FALSE,FALSE,0);

	en = gtk_entry_new();
	gtk_entry_set_max_length(GTK_ENTRY(en),10000);
	gtk_box_pack_start(GTK_BOX(boxv1),en,FALSE,FALSE,0);

	label = gtk_label_new("Type something!!:");
	gtk_box_pack_start(GTK_BOX(boxv1),label,FALSE,FALSE,0);

	text = gtk_entry_new();
	gtk_entry_set_max_length(GTK_ENTRY(text),100000);
	gtk_box_pack_start(GTK_BOX(boxv1),text,FALSE,FALSE,0);

	g_signal_connect(text,"activate",G_CALLBACK(criptografar),text);

	label1 = gtk_label_new("waiting...");
	gtk_box_pack_start(GTK_BOX(boxv1),label1,FALSE,FALSE,0);

	gdk_color_parse ("black", &color);
	gtk_widget_modify_bg( GTK_WIDGET(window), GTK_STATE_NORMAL, &color);

	gdk_color_parse ("lime", &color1);
    gtk_widget_modify_fg(label, GTK_STATE_NORMAL, &color1);

    gdk_color_parse ("lime", &color1);
    gtk_widget_modify_fg(label1, GTK_STATE_NORMAL, &color1);

    gdk_color_parse ("lime", &color1);
    gtk_widget_modify_fg(label_e, GTK_STATE_NORMAL, &color1);

    gdk_color_parse ("lime", &color1);
    gtk_widget_modify_fg(label_n, GTK_STATE_NORMAL, &color1);
	
	gtk_widget_show_all(window);
}
void fromfile(GtkWidget *widget,gpointer data)
{
	char letter1,msg[max],n_m[max];
	char *numc;
	FILE *f_in;
	long long int ind=0,i,letter;
	f_in = fopen ("decrypted.txt", "r"); 
  	while (!feof (f_in)) 
  	{
  		fscanf(f_in, "%Ld", &num_m[ind]); 
  		ind++;    
  	}
   	fclose (f_in);
   	
   	for(i=0;i < ind;i++)
	{
		num_m[i] = fastexpmod(num_m[i],dnumber,npublickey);
		letter = num_m[i];
		msg[i] = letter;
	}

	out2 = fopen("descriptografado.txt","a+");
	fprintf(out2,"%s",msg);
	fclose(out2);

	char text1[100] = "Descriptografado!!";
	gtk_label_set_text(GTK_LABEL(label2),text1);
}
void gogo(GtkWidget *widget,gpointer data)
{
	char letter1,msg[max],n_m[max];
	char *numc;

	numc = converttostring(gtk_entry_get_text(GTK_ENTRY(text3)));
	strcpy(n_m,numc);

	if(countlen == 0)
	{
		len = strlen(n_m);
		len = len/3;
	}
	for(inde=0;inde < len;inde++)
	{
		converttolongint(numc);
	}
	for(inde=0;inde < len;inde++)
	{
		num_m[inde] = fastexpmod(num_m[inde],dnumber,npublickey);
		letter1 = num_m[inde];
		msg[inde] = letter1;
	}
	strcpy(numc,msg);
	out2 = fopen("descriptografado.txt","a");
	fprintf(out2,"%s",numc);
	fclose(out2);

	char text1[100] = "Descriptografado!!";
	gtk_label_set_text(GTK_LABEL(label2),text1);
}
void descriptografar(GtkWidget *widget,gpointer data)
{
	GtkWidget *window;
	GtkWidget *boxv1;
	GtkWidget *button;
	GtkWidget *label;

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_container_set_border_width(GTK_CONTAINER(window),100);
	gtk_window_set_title(GTK_WINDOW(window),"Descrypt");

	boxv1 = gtk_vbox_new(FALSE,0);
	gtk_container_add(GTK_CONTAINER(window),boxv1);

	button = gtk_button_new_with_label("Read from file");
	gtk_box_pack_start(GTK_BOX(boxv1),button,FALSE,FALSE,0);
	g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK(fromfile), NULL);

	label = gtk_label_new("Or, type the encrypted message:");
	gtk_box_pack_start(GTK_BOX(boxv1),label,FALSE,FALSE,0);

	text3 = gtk_entry_new();
	gtk_entry_set_max_length(GTK_ENTRY(text3),1000000);
	gtk_box_pack_start(GTK_BOX(boxv1),text3,FALSE,FALSE,0);

	label2 = gtk_label_new("waiting...");
	g_signal_connect(text3,"activate",G_CALLBACK(gogo),text3);
	gtk_box_pack_start(GTK_BOX(boxv1),label2,FALSE,FALSE,0);

	gdk_color_parse ("black", &color);
	gtk_widget_modify_bg( GTK_WIDGET(window), GTK_STATE_NORMAL, &color);
	
	gdk_color_parse ("lime", &color1);
    gtk_widget_modify_fg(label, GTK_STATE_NORMAL, &color1);

    gdk_color_parse ("lime", &color1);
    gtk_widget_modify_fg(label2, GTK_STATE_NORMAL, &color1);

    if(GTK_IS_BIN(button))
    {
        GtkWidget *children = gtk_bin_get_child(GTK_BIN(button));
        gdk_color_parse ("green", &color1);
        gtk_widget_modify_fg(children,GTK_STATE_NORMAL,&color1);
    }

	gtk_widget_show_all(window);
}
int firstnumbern(GtkButton *button, gpointer data)
{
	long long int firstnumber=0,secondnumber=0,m=0,validate=0;

	firstnumber = atol(gtk_entry_get_text(GTK_ENTRY(p)));

	secondnumber = atol(gtk_entry_get_text(GTK_ENTRY(q)));

	npublickey = firstnumber*secondnumber;

	phi = (firstnumber-1)*(secondnumber-1);

	while(m!=1)
	{ 
		enumber = atol(gtk_entry_get_text(GTK_ENTRY(e)));
		m = euclides(enumber,phi);
		if(m == 1)
		{
			dnumber = inverso(enumber);
			validate++;
			break;
		}
		else
		{ 
			printf("Didn't work\n");
			break;
		}
	}

	out_d = fopen("Private Key.txt","a+");
	fprintf(out_d,"%Ld",dnumber);
	fclose(out_d);

	if(npublickey && (primo(firstnumber,secondnumber) != 0) && validate != 0)
	{
		char text2[100] = "Valid numbers!\n";
		gtk_label_set_text(GTK_LABEL(label_out),text2);
		out = fopen("chave_publica.txt","a+");
		fprintf(out,"N: %Ld E: %Ld\n",npublickey,enumber); 
		fclose(out);
		
	}
	else
	{
		char text1[100] = "Invalid number!!!\n";
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
	gtk_entry_set_max_length(GTK_ENTRY(p),10000);
	gtk_box_pack_start(GTK_BOX(boxv1),p,FALSE,FALSE,0);

	label1 = gtk_label_new("Enter a prime number Q:");
	gtk_box_pack_start(GTK_BOX(boxv1),label1,FALSE,FALSE,0);

	q = gtk_entry_new();
	gtk_entry_set_max_length(GTK_ENTRY(q),10000);
	gtk_box_pack_start(GTK_BOX(boxv1),q,FALSE,FALSE,0);

	label2 = gtk_label_new("Enter a number that will be E:");
	gtk_box_pack_start(GTK_BOX(boxv1),label2,FALSE,FALSE,0);

	e = gtk_entry_new();
	gtk_entry_set_max_length(GTK_ENTRY(e),10000);
	gtk_box_pack_start(GTK_BOX(boxv1),e,FALSE,FALSE,0);

	button = gtk_button_new_with_label("Go!");
	gtk_box_pack_start(GTK_BOX(boxv1),button,FALSE,FALSE,0);
	g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK(firstnumbern), NULL);

	label_out = gtk_label_new("Waiting...");
	gtk_box_pack_start(GTK_BOX(boxv1),label_out,FALSE,FALSE,0);

	gdk_color_parse ("black",&color);
	gtk_widget_modify_bg( GTK_WIDGET(window), GTK_STATE_NORMAL, &color);

	gdk_color_parse ("lime", &color1);
    gtk_widget_modify_fg(label,GTK_STATE_NORMAL,&color1);

    gdk_color_parse ("lime", &color1);
    gtk_widget_modify_fg(label1, GTK_STATE_NORMAL, &color1);

    gdk_color_parse ("lime", &color1);
    gtk_widget_modify_fg(label2, GTK_STATE_NORMAL, &color1);

    gdk_color_parse ("lime", &color1);
    gtk_widget_modify_fg(label_out, GTK_STATE_NORMAL, &color1);

    if(GTK_IS_BIN(button))
    {
        GtkWidget *children = gtk_bin_get_child(GTK_BIN(button));
        gdk_color_parse ("green", &color1);
        gtk_widget_modify_fg(children,GTK_STATE_NORMAL,&color1);
    }


	gtk_widget_show_all(window);
}
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
	g_signal_connect(G_OBJECT(botao3),"clicked",G_CALLBACK(descriptografar),NULL);
	gtk_box_pack_start(GTK_BOX(boxv1),botao3,FALSE,FALSE,0);

	gdk_color_parse ("black", &color);
	gtk_widget_modify_bg( GTK_WIDGET(window), GTK_STATE_NORMAL, &color);

    gdk_color_parse ("lime", &color1);
    gtk_widget_modify_fg(label, GTK_STATE_NORMAL, &color1);

    if(GTK_IS_BIN(botao1)) 
    {
        GtkWidget *children = gtk_bin_get_child(GTK_BIN(botao1));
        gdk_color_parse ("green", &color1);
        gtk_widget_modify_fg (children, GTK_STATE_NORMAL, &color1);
    }

    if(GTK_IS_BIN(botao2))
    {
        GtkWidget *children = gtk_bin_get_child(GTK_BIN(botao2));
        gdk_color_parse ("green", &color1);
        gtk_widget_modify_fg (children, GTK_STATE_NORMAL, &color1);
    }

    if(GTK_IS_BIN(botao3))
    {
        GtkWidget *children = gtk_bin_get_child(GTK_BIN(botao3));
        gdk_color_parse ("green", &color1);
        gtk_widget_modify_fg (children, GTK_STATE_NORMAL, &color1);
    }

	gtk_widget_show_all(window);

	gtk_main();

	return 0;
}
