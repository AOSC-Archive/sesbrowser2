#include "sesbrowser.h"

void BrowserAction::close(GtkWidget* w)
{
	if (w != NULL)
	{
		gtk_window_close ((GtkWindow*) w);
	}
	
	num--;
	printf ("Num of Browser: %d\n", num);
	
	if (num == 0 )
	{
		printf("Exiting..\n");
		gtk_main_quit ();
	}
}

GtkWidget* BrowserAction::signal_create (WebKitWebView* web_view, WebKitNavigationAction *navigation_action, gpointer browser)
{
	printf ("	receive signal 'create'\n");
	SESBrowser* b = (SESBrowser*) browser;
	GtkWidget* foobar = b->newWindow (NULL, (GtkWidget*) web_view);
	return foobar;
}

gboolean BrowserAction::signal_enter_fullscreen (WebKitWebView *web_view, GtkWidget* window)
{
	printf ("	receive signal 'Enter fullscreen'\n");
	gtk_window_fullscreen ((GtkWindow*) window);
	return TRUE;
}

gboolean BrowserAction::signal_leave_fullscreen (WebKitWebView *web_view, GtkWidget* window)
{
	printf ("	receive signal 'Leave fullscreen'\n");
	gtk_window_unfullscreen ((GtkWindow*) window);
	return TRUE;
}

void BrowserAction::signal_close (WebKitWebView* web_view, gpointer data)
{
	printf ("	receive signal 'close'\n");
	MainWindow* win = (MainWindow*) data;
	close (win->window);
}

void BrowserAction::win_signal_close (GtkWidget* win, gpointer data)
{
	printf ("	browser window receive signal 'destroy'\n");
	close (NULL);
}

void BrowserAction::signal_ready_to_show (WebKitWebView* web_view, gpointer data)
{
	printf ("	receive signal 'Ready to show'\n");
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
	g_signal_connect (G_OBJECT (this->view), "close", G_CALLBACK (signal_close), win);
	g_signal_connect (G_OBJECT (win->window), "destroy", G_CALLBACK (win_signal_close), NULL);
	num++;
	printf ("Num of Browser: %d\n", num);
}

int BrowserAction::num;
