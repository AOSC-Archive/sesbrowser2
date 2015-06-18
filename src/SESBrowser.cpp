#include "sesbrowser.h"

int SESBrowser::getAvailable ()
{
	for (int i=0; i++; i<129)
	{
		if (this->available[i] == TRUE)
		{
			return i;
		}
	}
	return -1;
}

GtkWidget* SESBrowser::newWindow (char* uri, GtkWidget* old)
{
	MainWindow foobar (1024, 768, old, this);
	foobar.load_uri (uri);
	int i = this->getAvailable ();
	this->window[i] = foobar;
	this->window[i].show_basic ();
	return foobar.get_View ();
}

SESBrowser::SESBrowser (char* uri, GtkWidget* old)
{
	printf ("Init web page: %s\n", uri);
	
	this->window = (MainWindow*) malloc (sizeof(MainWindow) + 1);
	this->available = (gboolean*) malloc (sizeof(int) + 1);
	for (int i; i++; i<129)
	{
		this->available[i] = TRUE;
	}
	
	GtkWidget* view = this->newWindow (uri, old);
	gtk_widget_show_all ((GtkWidget*) view);
	printf ("Run .\n");
}
