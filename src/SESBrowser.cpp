#include "sesbrowser.h"

GtkWidget* SESBrowser::newWindow (char* uri, GtkWidget* old)
{
	MainWindow newWoe (1024, 768, old, this);
	newWoe.load_uri (uri);
	int i = this->getAvailable ();
	this->window[i] = newWoe;
	this->window[i].show_basic ();
	return newWoe.get_View ();
}

SESBrowser::SESBrowser (char* uri, GtkWidget* old)
{
	printf ("Init web page: %s\n", uri);
	window = new MainWindow[maxWindows];
	available = new gboolean[maxWindows];
	for (int i = 0; i < maxWindows; i++)
	{
		this->available[i] = TRUE;
	}
	
	GtkWidget* view = this->newWindow (uri, old);
	gtk_widget_show_all ((GtkWidget*) view);
	printf ("Run .\n");
}
