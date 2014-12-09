#include <gtk/gtk.h>
static void next_handler( GtkWidget *widget,gpointer data);
static void previous_handler( GtkWidget *widget,gpointer data);
static gboolean delete_event( GtkWidget *widget,GdkEvent  *event,gpointer data);
static void destroy( GtkWidget *widget,gpointer data);
static void createWindow();
static void createButtons();
static void layoutWidgets();
static void show();
static void draw_brush (GtkWidget *widget, gdouble x, gdouble y);
static gboolean expose_event( GtkWidget *widget, GdkEventExpose *event );
static gboolean configure_event( GtkWidget *widget, GdkEventConfigure *event );
static gboolean button_press_event( GtkWidget *widget, GdkEventButton *event );
static gboolean motion_notify_event( GtkWidget *widget, GdkEventMotion *event );
static void createDrawingArea();
static void createMenus();

GtkWidget *window;
GtkWidget *previous;
GtkWidget *next;
GtkWidget *graphNavigationPanel;
GtkWidget *mainPanel;
GtkWidget *drawingArea;
GdkPixmap *pixMap;	

GtkWidget *fixed;
GtkWidget *menubar;
GtkWidget *filemenu;
GtkWidget *file;
GtkWidget *newfile;
GtkWidget *savefile;
GtkWidget *separator;
GtkWidget *quit;
GtkWidget *vbox;


int main( int   argc, char *argv[])
{
    gtk_init (&argc, &argv);
	
    createWindow();
	//createMenus();
    createButtons();
    createDrawingArea();
    layoutWidgets();
    show();
	
    gtk_main ();
	
    return 0;
}


static void next_handler( GtkWidget *widget,gpointer data)
{
    g_print ("next %s \n", (gchar *) data);
}

static void previous_handler( GtkWidget *widget,gpointer data)
{
    g_print ("previous %s \n", (gchar *) data);
}

static gboolean delete_event( GtkWidget *widget,GdkEvent  *event,gpointer data)
{
    return FALSE;
}

static void destroy( GtkWidget *widget,gpointer data)
{
    gtk_main_quit ();
}


static void createWindow() {
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_container_set_border_width (GTK_CONTAINER (window), 10);
    gtk_window_set_title (GTK_WINDOW (window), "CNSilva Project v0.2b");
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	
	fixed = gtk_fixed_new();
	gtk_container_add(GTK_CONTAINER(window), fixed);
	
	vbox = gtk_vbox_new(FALSE, 0);
	gtk_fixed_put(GTK_FIXED(fixed), vbox, 0, 0);	
	gtk_widget_set_size_request(vbox, 600, 400);
	
    g_signal_connect (G_OBJECT (window), "delete_event",G_CALLBACK (delete_event), NULL);
	
    g_signal_connect (G_OBJECT (window), "destroy",G_CALLBACK (destroy), NULL);
	
	
}

static void createMenus(){
	
	
	
	
	menubar = gtk_menu_bar_new();
	filemenu = gtk_menu_new();
	
	file = gtk_menu_item_new_with_mnemonic("_File");
	newfile = gtk_image_menu_item_new_from_stock(GTK_STOCK_NEW, NULL);
	savefile = gtk_menu_item_new_with_label("Save File");
	separator=gtk_separator_menu_item_new();
	quit = gtk_menu_item_new_with_label("Quit");
	
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(file), filemenu);
	gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), newfile);
	gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), savefile);
	gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), separator);
	gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), quit);
	gtk_menu_shell_append(GTK_MENU_SHELL(menubar), file);
	gtk_box_pack_start(GTK_BOX(vbox), menubar, FALSE, FALSE, 3);
	
	g_signal_connect(G_OBJECT(quit), "activate",G_CALLBACK(gtk_main_quit), NULL);
	//g_signal_connect(G_OBJECT(newfile), "activate",G_CALLBACK(PrintAction), NULL);
}

static void createButtons() {
    next = gtk_button_new_with_label ("Next");
    previous = gtk_button_new_with_label ("Previous");
	
    g_signal_connect (G_OBJECT (next), "clicked", G_CALLBACK (next_handler), NULL);
    g_signal_connect (G_OBJECT (previous), "clicked", G_CALLBACK (previous_handler), NULL);
	
}

static void layoutWidgets() {
    /* Create the graph navigation panel and add it to the window. 
    graphNavigationPanel = gtk_hbox_new (FALSE, 0);
    mainPanel = gtk_vbox_new(FALSE, 0);
	
    gtk_container_add  (GTK_CONTAINER (window), mainPanel);
	
	
    /* Add the buttons to the graph navigation panel. 
    gtk_box_pack_start (GTK_BOX(graphNavigationPanel), previous, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX(graphNavigationPanel), next,     TRUE, TRUE, 0);
	
	
    /*Add the graph navigation panel to the main panel. 
    gtk_box_pack_start (GTK_BOX(mainPanel), graphNavigationPanel, TRUE, TRUE, 0);
    /* Add the draw-able area to the main panel. 
    gtk_box_pack_start (GTK_BOX(mainPanel), drawingArea, TRUE, TRUE, 0);*/
	gtk_fixed_put(GTK_FIXED(fixed), drawingArea, 0, 0);	
}

static void show() {
    gtk_widget_show (drawingArea);
    gtk_widget_show (mainPanel);
    gtk_widget_show (next);
    gtk_widget_show (previous);
    gtk_widget_show (graphNavigationPanel);
    gtk_widget_show (window);
}

/* Draw a rectangle on the screen */
static void draw_brush (GtkWidget *widget, gdouble x, gdouble y)
{
	GdkRectangle update_rect;
	
	update_rect.x = x - 5;
	update_rect.y = y - 5;
	update_rect.width = 5;
	update_rect.height = 5;
	gdk_draw_rectangle (pixMap,
						widget->style->black_gc,
						TRUE,
						update_rect.x, update_rect.y,
						update_rect.width, update_rect.height);
	gtk_widget_queue_draw_area (widget,
								update_rect.x, update_rect.y,
								update_rect.width, update_rect.height);
}

/* Redraw the screen from the backing pixmap */
static gboolean expose_event( GtkWidget *widget, GdkEventExpose *event )
{
	gdk_draw_drawable(widget->window,
					  widget->style->fg_gc[GTK_WIDGET_STATE (widget)],
					  pixMap,
					  event->area.x, event->area.y,
					  event->area.x, event->area.y,
					  event->area.width, event->area.height);
	
	return FALSE;
}
/* Create a new backing pixmap of the appropriate size */
static gboolean configure_event( GtkWidget *widget, GdkEventConfigure *event )
{
	if (pixMap)
		g_object_unref(pixMap);
	
	pixMap = gdk_pixmap_new(widget->window,
								 widget->allocation.width,
								 widget->allocation.height,
								 -1);
	
	gdk_draw_rectangle (pixMap,
						widget->style->white_gc,
						TRUE,
						0, 0,
						widget->allocation.width,
						widget->allocation.height);
	
	return TRUE;
}

static gboolean button_press_event( GtkWidget *widget, GdkEventButton *event )
{
	if (event->button == 1 && pixMap != NULL)
		draw_brush (widget, event->x, event->y);
	
	return TRUE;
}

static gboolean motion_notify_event( GtkWidget *widget, GdkEventMotion *event )
{
	int x, y;
	GdkModifierType state;
	
	if (event->is_hint)
		gdk_window_get_pointer (event->window, &x, &y, &state);
	else
    {
		x = event->x;
		y = event->y;
		state = event->state;
    }
	
	if (state & GDK_BUTTON1_MASK && pixMap != NULL)
		draw_brush (widget, x, y);
	
	return TRUE;
}

static void createDrawingArea() {
    drawingArea = gtk_drawing_area_new();
	
    gtk_signal_connect (GTK_OBJECT (drawingArea), "expose_event",
						(GtkSignalFunc) expose_event, NULL);
    gtk_signal_connect (GTK_OBJECT(drawingArea),"configure_event",
						(GtkSignalFunc) configure_event, NULL);
    gtk_signal_connect (GTK_OBJECT (drawingArea), "motion_notify_event",
						(GtkSignalFunc) motion_notify_event, NULL);
    gtk_signal_connect (GTK_OBJECT (drawingArea), "button_press_event",
						(GtkSignalFunc) button_press_event, NULL);
	
    gtk_widget_set_events (drawingArea, GDK_EXPOSURE_MASK
						   | GDK_LEAVE_NOTIFY_MASK
						   | GDK_BUTTON_PRESS_MASK
						   | GDK_POINTER_MOTION_MASK
						   | GDK_POINTER_MOTION_HINT_MASK);
	
    gtk_drawing_area_size(drawingArea, 500, 500);
}


