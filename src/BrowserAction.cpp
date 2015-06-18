#include "sesbrowser.h"

GtkWidget* BrowserAction::signal_create (WebKitWebView* web_view, WebKitNavigationAction *navigation_action, gpointer browser)
{
	printf ("	receive signal 'create'");
	SESBrowser* b = (SESBrowser*) browser;
	GtkWidget* foobar = b->newWindow (NULL, (GtkWidget*) web_view);
	return foobar;
}

gboolean BrowserAction::signal_enter_fullscreen (WebKitWebView *web_view, GtkWidget* window)
{
	printf ("	receive signal 'Enter fullscreen'");
	gtk_window_fullscreen ((GtkWindow*) window);
	return TRUE;
}

gboolean BrowserAction::signal_leave_fullscreen (WebKitWebView *web_view, GtkWidget* window)
{
	printf ("	receive signal 'Leave fullscreen'");
	gtk_window_unfullscreen ((GtkWindow*) window);
	return TRUE;
}
/*
void BrowserAction::signal_close (WebKitWebView* web_view, gpointer data)
{
	printf ("	receive signal 'close'");
	gtk_widget_destroy ();
}
*/
void BrowserAction::signal_ready_to_show (WebKitWebView* web_view, gpointer data)
{
	printf ("	receive signal 'Ready to show'");
	gtk_widget_show_all ((GtkWidget*) web_view);
}

void BrowserAction::init (WebKitWebView* webview, gpointer b, gpointer w)
{
	this->view = webview;
	MainWindow* win = (MainWindow*) w;
	g_signal_connect (G_OBJECT (this->view), "create", G_CALLBACK (signal_create), b);
	g_signal_connect (G_OBJECT (this->view), "ready-to-show", G_CALLBACK (signal_ready_to_show), NULL);
	g_signal_connect (G_OBJECT (this->view), "enter-fullscreen", G_CALLBACK (signal_enter_fullscreen), win->window);
	g_signal_connect (G_OBJECT (this->view), "leave-fullscreen", G_CALLBACK (signal_leave_fullscreen), win->window);
}

