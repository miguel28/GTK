#include <gtk/gtk.h>
#define WIN_TITLE "Minus Plus"
void Init_GUI();
void SetLabel();
void Plus1();
void Minus1();

unsigned int i;
int main(int argc,char *argv[])
{
    
	gtk_init (&argc, &argv);
	Init_GUI();
    gtk_main ();
    
    return 0;
}

int value;

GtkWidget *window;
GtkWidget *fixed;
GtkWidget *label;

GtkWidget *button1;
GtkWidget *button2;
  
GtkWidget *Salir;
GtkWidget *Restaurar;
unsigned int turno=1;


void Init_GUI()
{
  
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window), WIN_TITLE);
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

  fixed = gtk_fixed_new();
  gtk_container_add(GTK_CONTAINER(window), fixed);
 
  label = gtk_label_new("0");
  gtk_fixed_put(GTK_FIXED(fixed), label, 230, 58); 	

  button1= gtk_button_new_with_label("+");
  gtk_fixed_put(GTK_FIXED(fixed), button1, 20,20);
  gtk_widget_set_size_request(button1, 80, 50);
  g_signal_connect (button1, "clicked",G_CALLBACK (Plus1), NULL);
  

  button2= gtk_button_new_with_label("-");
  gtk_fixed_put(GTK_FIXED(fixed), button2, 20,120);
  gtk_widget_set_size_request(button2, 80, 50);
  g_signal_connect (button2, "clicked",G_CALLBACK (Minus1), NULL);


  g_signal_connect_swapped(G_OBJECT(window), "destroy", 
      G_CALLBACK(gtk_main_quit), NULL);

  gtk_widget_show_all(window);
}

void SetLabel(){
	char tempchar[10];
	sprintf(tempchar,"%d",value);
	gtk_label_set_text(label,tempchar);
	
}

void Plus1(){
	value++;
	SetLabel();
}

void Minus1(){
	value--;
	SetLabel();
}
