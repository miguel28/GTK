
/* A simple example of using SDL with GTk */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include <gtk/gtk.h>
//#include <gdk/gdkx.h>
/*
#ifdef USE_XSHAPE
#include <X11/Xlib.h>
#include <X11/extensions/shape.h>
#endif
*/
#include <SDL.h>

#define WINSIZEX 320
#define WINSIZEY 200

/* The main display surface */
GtkWidget *mainwin;
SDL_Surface *screen = NULL;


#ifdef USE_XSHAPE
int use_shape = 0;
Pixmap shape_mask = 0;
GC shape_gc;
int shape_x = 0;
int shape_y = 0;
int shape_dx = 0;
int shape_dy = 0;

void ResizeShape(void)
{
	Display *dpy;
	XGCValues GCvalue;
	
	if ( ! use_shape ) {
		return;
	}
	dpy = GDK_WINDOW_XDISPLAY(mainwin->window);
	if ( shape_mask ) {
		XFreePixmap(dpy, shape_mask);
		XFreeGC(dpy, shape_gc);
	}
	shape_mask = XCreatePixmap(dpy, DefaultRootWindow(dpy),
	                           screen->w, screen->h, 1);
	GCvalue.function = GXcopy;
	shape_gc = XCreateGC(dpy, shape_mask, GCFunction, &GCvalue);
	XSync(dpy, False);
}

void ShapeWindow(void)
{
#ifdef SQUARE_HOLE
#define RADIUS 16
#else
#define RADIUS 24
#endif
	Display *dpy;
	Window win;
	int x, y, i;
	void (*set_bit)(XImage *image, int x, int y);
	int (*get_bit)(XImage *image, int x, int y);
	
	if ( ! use_shape ) {
		return;
	}
	
	/* Only move the shape every 100'th time through */
	{ static int step = 0;
		if ( (step++)%100 != 0 ) {
			return;
		}
	}
	
	/* Set the window and display */
	dpy = GDK_WINDOW_XDISPLAY(mainwin->window);
	win = GDK_WINDOW_XWINDOW(mainwin->window);
	
	/* Bounce the hole when it hits the edge */
	if ( shape_x == 0 ) {
		shape_dx = 1;
	}
	if ( shape_x >= (screen->w-(2*RADIUS)) ) {
		shape_x = (screen->w-(2*RADIUS));
		shape_dx = -1;
	}
	if ( shape_y == 0 ) {
		shape_dy = 1;
	}
	if ( shape_y >= (screen->h-(2*RADIUS)) ) {
		shape_y = (screen->h-(2*RADIUS));
		shape_dy = -1;
	}
	
	/* Move the hole around */
	shape_x += shape_dx;
	shape_y += shape_dy;
	
	/* Now put the hole in the mask
	 Note: you can also set the mask directly by getting an XImage
	 of it, and modifying the data member and then putting
	 the image to the mask pixmap.  You have to think about
	 the bit ordering in the image though.  Using X calls is
	 better for simple shapes because the X server will take
	 care of the bit ordering, and possibly use hardware
	 acceleration when possible.
	 */
	dpy = GDK_WINDOW_XDISPLAY(mainwin->window);
	XSetForeground(dpy, shape_gc, ~0);
	XFillRectangle(dpy, shape_mask, shape_gc, 0, 0, screen->w, screen->h);
	XSetForeground(dpy, shape_gc, 0);
#ifdef SQUARE_HOLE
	XFillRectangle(dpy, shape_mask, shape_gc, shape_x, shape_y, 2*RADIUS, 2*RADIUS);
#else
	XFillArc(dpy, shape_mask, shape_gc, shape_x, shape_y, 2*RADIUS, 2*RADIUS, 0, 360*64);
#endif
	
	/* Set the mask on the window */
	XShapeCombineMask(dpy, win, ShapeBounding, 0, 0, shape_mask, ShapeSet);
	
	/* Update the whole screen */
	SDL_UpdateRect(screen, 0, 0, screen->w, screen->h);
}

/* Check for the X shaped window extension */
void CheckShape(void)
{
	int ev_base, er_base;
	Display *dpy;
	
	use_shape = 0;
	dpy = GDK_WINDOW_XDISPLAY(mainwin->window);
	if ( XShapeQueryExtension(dpy, &ev_base, &er_base) ) {
		use_shape = 1;
	}
	ResizeShape();
	printf("Shape extension%s available\n", use_shape ? "" : " not");
}

#endif /* USE_SHAPE */


/* Event handlers -- the configure_event handler is very important! */

gint
button_press_event (GtkWidget *widget,  GdkEventButton *event)
{
	SDL_Rect rect;
	
	rect.x = event->x-1;
	rect.y = event->y-1;
	rect.w = 2;
	rect.h = 2;
	SDL_FillRect(screen, &rect, SDL_MapRGB(screen->format, 255, 255, 255));
	SDL_UpdateRects(screen, 1, &rect);
	
	return TRUE ;
}

gint
configure_event (GtkWidget *widget, GdkEventConfigure *event)
{
	screen = SDL_SetVideoMode(event->width, event->height, 0, 0);
#ifdef USE_XSHAPE
	ResizeShape();
#endif
	return TRUE ;
}

gint
delete_event (GtkWidget *widget, GdkEventConfigure *event)
{
	gtk_main_quit();
	return TRUE ;
}

/* Idle function -- called when GTk isn't busy */
gint
idle_loop (gpointer data)
{
	int x, y;
	
	/* Make a random spot black (well, color 0 anyway :) */
	x = rand()%screen->w;
	y = rand()%screen->h;
	switch (screen->format->BytesPerPixel) {
		case 1:
			*((Uint8 *)screen->pixels+y*screen->pitch+x) = 0;
			break;
		case 2:
			*((Uint16 *)screen->pixels+y*screen->pitch/2+x) = 0;
			break;
		case 3:  /* Yuck... */
			((Uint8 *)screen->pixels+y*screen->pitch+x)[0] = 0;
			((Uint8 *)screen->pixels+y*screen->pitch+x)[1] = 0;
			((Uint8 *)screen->pixels+y*screen->pitch+x)[2] = 0;
			break;
		case 4:
			*((Uint32 *)screen->pixels+y*screen->pitch/4+x) = 0;
			break;
	}
#ifdef USE_XSHAPE
	ShapeWindow();
#endif
	SDL_UpdateRect(screen, x, y, 1, 1);
	return TRUE ;
}

/* Menu callbacks */

void NewScreen(gpointer cb_data, guint cb_action, GtkWidget *widget)
{
	SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));
	SDL_UpdateRect(screen, 0, 0, 0, 0);
}

void QuitGame(gpointer callback_data, guint callback_action, GtkWidget *widget)
{
	gtk_main_quit();
}


static GtkItemFactoryEntry menu_items[] = {
	{"/_File",			NULL,		0,		0, "<Branch>" },
	{"/_File/_New",		NULL,		NewScreen,	0 },
	{"/_File/_Quit",		"<control>Q",	QuitGame,	0 },
};

void CreateMenus(GtkWidget *window)
{
	GtkAccelGroup *accel_group;
	GtkItemFactory *item_factory;
	GtkWidget *box1;
	
	accel_group = gtk_accel_group_new();
	item_factory = gtk_item_factory_new(GTK_TYPE_MENU_BAR, "<menu>", accel_group);
	gtk_item_factory_create_items(item_factory, 3, menu_items, NULL);
	gtk_accel_group_attach(accel_group, GTK_OBJECT(window));
	gtk_window_set_title(GTK_WINDOW(window), "Star Field");
	gtk_container_border_width(GTK_CONTAINER(window), 0);
	box1 = gtk_vbox_new(FALSE, 0);
	gtk_container_add(GTK_CONTAINER(window), box1);
	gtk_box_pack_start(GTK_BOX(box1), gtk_item_factory_get_widget(item_factory, "<menu>"), FALSE, FALSE, 0);
	gtk_widget_show_all(window);
}

int main(int argc, char *argv[])
{
	gtk_init(&argc, &argv);
	
	/* Create a main window */
	mainwin = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_widget_set_usize(mainwin, WINSIZEX, WINSIZEY);
	gtk_widget_realize(mainwin);
	
	/* Add event handlers -- the configure_event handler is important! */
	gtk_widget_add_events(mainwin, GDK_BUTTON_PRESS_MASK);
	gtk_signal_connect(GTK_OBJECT(mainwin), "configure_event", GTK_SIGNAL_FUNC(configure_event), 0);
	gtk_signal_connect(GTK_OBJECT(mainwin), "button_press_event", GTK_SIGNAL_FUNC(button_press_event), 0);
	gtk_signal_connect(GTK_OBJECT(mainwin), "delete_event", GTK_SIGNAL_FUNC(delete_event), 0);
	
	/* Hack to get SDL to use GTK window */
	{ char SDL_windowhack[32];
		sprintf(SDL_windowhack,"SDL_WINDOWID=%ld",
				GDK_WINDOW_XWINDOW(mainwin->window));
		putenv(SDL_windowhack);
	}
	
	/* Initialize SDL */
	if ( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
		fprintf(stderr,"Couldn't initialize SDL: %s\n",SDL_GetError());
		gtk_main_quit();
	}
	
	screen = SDL_SetVideoMode(WINSIZEX, WINSIZEY, 0, 0);
	
#ifdef USE_XSHAPE
	/* Check for the X shaped window extension */
	CheckShape();
#endif
	
	/* Create menus for the main window */
	CreateMenus( mainwin );
	
	/* Add an idle function -- game main loop? */
	srand(time(NULL));
	gtk_idle_add(idle_loop, mainwin);
	
	/* The last thing to get called */
	gtk_main();
	SDL_Quit();
	return 0;
}
