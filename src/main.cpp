#include "sesbrowser.h"

int main (int argc, char** argv)
{
	gtk_init (&argc, &argv);
	
	char* uri = (char*) (argc > 1 ? argv[1] : "http://www.baidu.com/");
	SESBrowser b(uri, NULL);
	
	gtk_main ();
	return 0;
}

