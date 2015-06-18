#include <webkit2/webkit2.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

class BrowserAction
{
	private:
	WebKitWebView* view;
	
	public:
	static GtkWidget* signal_create (WebKitWebView* web_view, WebKitNavigationAction *navigation_action, gpointer browser);
	static void signal_ready_to_show (WebKitWebView* web_view, gpointer data);
	static gboolean signal_enter_fullscreen (WebKitWebView *web_view, GtkWidget* window);
	static gboolean signal_leave_fullscreen (WebKitWebView *web_view, GtkWidget* window);
	
	void init (WebKitWebView* view, gpointer b, gpointer w);
};

class MainWindow
{
	public:
	GtkWidget* window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	GtkWidget* scroll = gtk_scrolled_window_new (NULL, NULL);
	GtkWidget* headerbar = gtk_header_bar_new ();
	GtkWidget* webview;
	BrowserAction action;
	
	void load_uri (char* str);
	void show_basic ();
	GtkWidget* get_View ();
	
	void create_webview (GtkWidget* old);
	
	MainWindow (int width, int height, GtkWidget* old, gpointer b);
};

class SESBrowser
{
	private:
	MainWindow* 	window;
	gboolean*		available;
	int				windowcount;
	
	int getAvailable ();
	
	public:
	GtkWidget* newWindow (char* uri, GtkWidget* old);
	
	SESBrowser (char* uri, GtkWidget* old);
};

