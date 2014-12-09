#include "main.h"

unsigned int i;
int main(int argc,char *argv[])
{
    
	gtk_init (&argc, &argv);
	Init_GUI();
    gtk_main ();
    
    return 0;
}

unsigned int value[9];

GtkWidget *window;
GtkWidget *fixed;
GtkWidget *label;

  GtkWidget *button1;
  GtkWidget *button2;
  GtkWidget *button3;
  
  GtkWidget *button4;
  GtkWidget *button5;
  GtkWidget *button6;
  
  GtkWidget *button7;
  GtkWidget *button8;
  GtkWidget *button9;
  
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
 
  label = gtk_label_new("Turno O");
  gtk_fixed_put(GTK_FIXED(fixed), label, 230, 58); 	
	
  button1= gtk_button_new_with_label(" ");
  gtk_fixed_put(GTK_FIXED(fixed), button1, 20,20);
  gtk_widget_set_size_request(button1, 50, 50);
  g_signal_connect (button1, "clicked",G_CALLBACK (funbutton1), NULL);

  button2= gtk_button_new_with_label(" ");
  gtk_fixed_put(GTK_FIXED(fixed), button2, 90,20);
  gtk_widget_set_size_request(button2, 50, 50);
  g_signal_connect (button2, "clicked",G_CALLBACK (funbutton2), NULL);

  button3= gtk_button_new_with_label(" ");
  gtk_fixed_put(GTK_FIXED(fixed), button3, 160,20);
  gtk_widget_set_size_request(button3, 50, 50);
  g_signal_connect (button3, "clicked",G_CALLBACK (funbutton3), NULL);
  
  button4= gtk_button_new_with_label(" ");
  gtk_fixed_put(GTK_FIXED(fixed), button4, 20,90);
  gtk_widget_set_size_request(button4, 50, 50);
  g_signal_connect (button4, "clicked",G_CALLBACK (funbutton4), NULL);
  
  button5= gtk_button_new_with_label(" ");
  gtk_fixed_put(GTK_FIXED(fixed), button5, 90,90);
  gtk_widget_set_size_request(button5, 50, 50);
  g_signal_connect (button5, "clicked",G_CALLBACK (funbutton5), NULL);
  
  button6= gtk_button_new_with_label(" ");
  gtk_fixed_put(GTK_FIXED(fixed), button6, 160,90);
  gtk_widget_set_size_request(button6, 50, 50);
  g_signal_connect (button6, "clicked",G_CALLBACK (funbutton6), NULL);
  
  button7= gtk_button_new_with_label(" ");
  gtk_fixed_put(GTK_FIXED(fixed), button7, 20,160);
  gtk_widget_set_size_request(button7, 50, 50);
  g_signal_connect (button7, "clicked",G_CALLBACK (funbutton7), NULL);

  button8= gtk_button_new_with_label(" ");
  gtk_fixed_put(GTK_FIXED(fixed), button8, 90,160);
  gtk_widget_set_size_request(button8, 50, 50);
  g_signal_connect (button8, "clicked",G_CALLBACK (funbutton8), NULL);

  button9= gtk_button_new_with_label(" ");
  gtk_fixed_put(GTK_FIXED(fixed), button9, 160,160);
  gtk_widget_set_size_request(button9, 50, 50);
  g_signal_connect (button9, "clicked",G_CALLBACK (funbutton9), NULL);

  g_signal_connect_swapped(G_OBJECT(window), "destroy", 
      G_CALLBACK(gtk_main_quit), NULL);

  gtk_widget_show_all(window);
}

void funbutton1()
{
	if(value[0]==0)
	{
		value[0]=turno;
		RenderButtons();
	}
}
void funbutton2()
{
	if(value[1]==0)
	{
		value[1]=turno;
		RenderButtons();
	}
}
void funbutton3()
{
	if(value[2]==0)
	{
		value[2]=turno;
		RenderButtons();
	}
}
void funbutton4()
{
	if(value[3]==0)
	{
		value[3]=turno;
		RenderButtons();
	}
}
void funbutton5()
{
	if(value[4]==0)
	{
		value[4]=turno;
		RenderButtons();
	}
}
void funbutton6()
{
	if(value[5]==0)
	{
		value[5]=turno;
		RenderButtons();
	}
}
void funbutton7()
{
	if(value[6]==0)
	{
		value[6]=turno;
		RenderButtons();
	}
}
void funbutton8()
{
	if(value[7]==0)
	{
		value[7]=turno;
		RenderButtons();
	}
}
void funbutton9()
{
	g_print("hjajaja");
	if(value[8]==0)
	{
		value[8]=turno;
		RenderButtons();
	}
}

void RenderButtons()
{
	if (turno==1)
	{
		gtk_label_set_text(label,"Turno O");
		turno=2;
	}
	else
	{
		gtk_label_set_text(label,"Turno X");
		turno=1;
	}
	
	if(value[0]==1)gtk_button_set_label(button1,"X");
	else if(value[0]==2) gtk_button_set_label(button1,"O");
	
	if(value[1]==1)gtk_button_set_label(button2,"X");
	else if(value[1]==2) gtk_button_set_label(button2,"O");

	if(value[2]==1)gtk_button_set_label(button3,"X");
	else if(value[2]==2) gtk_button_set_label(button3,"O");
	
	if(value[3]==1)gtk_button_set_label(button4,"X");
	else if(value[3]==2) gtk_button_set_label(button4,"O");
	
	if(value[4]==1)gtk_button_set_label(button5,"X");
	else if(value[4]==2) gtk_button_set_label(button5,"O");
	
	if(value[5]==1)gtk_button_set_label(button6,"X");
	else if(value[5]==2) gtk_button_set_label(button6,"O");
	
	if(value[6]==1)gtk_button_set_label(button7,"X");
	else if(value[6]==2) gtk_button_set_label(button7,"O");
	
	if(value[7]==1)gtk_button_set_label(button8,"X");
	else if(value[7]==2) gtk_button_set_label(button8,"O");
	
	if(value[8]==1)gtk_button_set_label(button9,"X");
	else if(value[8]==2) gtk_button_set_label(button9 ,"O");
	
}
