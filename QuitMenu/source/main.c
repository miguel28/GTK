#include "main.h"
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

GtkWidget *vbox;

GtkWidget *menubar;
GtkWidget *filemenu;
GtkWidget *file;
GtkWidget *newfile;
GtkWidget *separator;
GtkWidget *checkbutton;
GtkWidget *quit;

GtkWidget *statusbar;


unsigned int turno=1;


void Init_GUI()
{
  
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), WIN_TITLE);
	gtk_window_set_default_size(GTK_WINDOW(window), 600,400);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

	fixed = gtk_fixed_new();
	gtk_container_add(GTK_CONTAINER(window), fixed);
	
	
	vbox = gtk_vbox_new(FALSE, 0);
	gtk_fixed_put(GTK_FIXED(fixed), vbox, 0, 0);	
	gtk_widget_set_size_request(vbox, 600, 400);
	
	
	menubar = gtk_menu_bar_new();
	filemenu = gtk_menu_new();
	
	file = gtk_menu_item_new_with_mnemonic("_File");
	newfile = gtk_image_menu_item_new_from_stock(GTK_STOCK_NEW, NULL);
	quit = gtk_menu_item_new_with_label("Quit");
	separator=gtk_separator_menu_item_new();
	checkbutton = gtk_check_menu_item_new_with_label("View Statusbar");
	gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(checkbutton), TRUE);
	
	statusbar = gtk_statusbar_new();
	gtk_box_pack_end(GTK_BOX(vbox), statusbar, FALSE, TRUE, 1);
	
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(file), filemenu);
	gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), newfile);
	gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), checkbutton);
	gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), separator);
	gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), quit);
	gtk_menu_shell_append(GTK_MENU_SHELL(menubar), file);
	gtk_box_pack_start(GTK_BOX(vbox), menubar, FALSE, FALSE, 3);
	
	g_signal_connect(G_OBJECT(quit), "activate",G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(G_OBJECT(newfile), "activate",G_CALLBACK(PrintAction), NULL);
	
	label = gtk_label_new("no one button clicked");
	gtk_fixed_put(GTK_FIXED(fixed), label, 230, 58);	

	

	g_signal_connect_swapped(G_OBJECT(window), "destroy", 
      G_CALLBACK(gtk_main_quit), NULL);

	gtk_widget_show_all(window);
}
void PrintAction(){
	//g_print("New File Created");
	gtk_label_set_text(label,"New File Created");
}