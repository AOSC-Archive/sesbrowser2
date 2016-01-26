#include "sesbrowser.h"

void MainWindow::load_uri (char* str)
{
	if (str != NULL)
	{
		printf ("	load uri : %s\n", str);
		webkit_web_view_load_uri ((WebKitWebView*) this->webview, str);
	}
}

GtkWidget* MainWindow::get_View ()
{
	return this->webview;
}

void MainWindow::show_basic ()
{
	gtk_widget_show (this->window);
	gtk_widget_show_all (this->headerbar);
	gtk_widget_show (this->scroll);
}

void MainWindow::create_webview (GtkWidget* old)
{
	WebKitSettings* t = webkit_settings_new ();
	
	webkit_settings_set_auto_load_images (t, TRUE);
	webkit_settings_set_enable_frame_flattening (t, TRUE);
	webkit_settings_set_enable_html5_database (t, TRUE);
	webkit_settings_set_enable_html5_local_storage (t, TRUE);
	webkit_settings_set_enable_hyperlink_auditing (t, FALSE);
	webkit_settings_set_enable_java (t, TRUE);
	webkit_settings_set_enable_javascript (t, TRUE);
	webkit_settings_set_enable_offline_web_application_cache (t, TRUE);
	webkit_settings_set_enable_plugins (t, FALSE);
	webkit_settings_set_enable_xss_auditor (t, FALSE);
	webkit_settings_set_javascript_can_open_windows_automatically (t, TRUE);
	webkit_settings_set_load_icons_ignoring_image_load_setting (t, FALSE);
	webkit_settings_set_default_font_family (t, "Sans Serif");
	webkit_settings_set_monospace_font_family (t, "Monospace");
	webkit_settings_set_serif_font_family (t, "Serif");
	webkit_settings_set_sans_serif_font_family (t, "Sans Serif");
	//webkit_settings_set_cursive_font_family ();
	//webkit_settings_set_fantasy_font_family ()
	//webkit_settings_set_pictograph_font_family ()
	//webkit_settings_set_default_font_size ()
	//webkit_settings_set_default_monospace_font_size ()
	//webkit_settings_set_minimum_font_size ()
	//webkit_settings_set_default_charset ()
	webkit_settings_set_enable_private_browsing (t, FALSE);  // not private
	webkit_settings_set_enable_developer_extras (t, FALSE);  // no develop
	webkit_settings_set_enable_resizable_text_areas (t, TRUE);
	webkit_settings_set_enable_tabs_to_links (t, TRUE);
	webkit_settings_set_enable_dns_prefetching (t, TRUE);  // faster
	webkit_settings_set_enable_caret_browsing (t, FALSE);
	webkit_settings_set_enable_fullscreen (t, TRUE);
	webkit_settings_set_print_backgrounds (t, TRUE);
	webkit_settings_set_enable_webaudio (t, TRUE);
	webkit_settings_set_enable_webgl (t, TRUE);
	webkit_settings_set_zoom_text_only (t, FALSE);
	webkit_settings_set_javascript_can_access_clipboard (t, TRUE);
	webkit_settings_set_media_playback_requires_user_gesture (t, FALSE);
	webkit_settings_set_media_playback_allows_inline (t, TRUE);
	webkit_settings_set_draw_compositing_indicators (t, FALSE);  // no develop
	webkit_settings_set_enable_site_specific_quirks (t, TRUE);
	webkit_settings_set_enable_page_cache (t, TRUE);
	//webkit_settings_set_user_agent ()
	//webkit_settings_set_user_agent_with_application_details ()
	webkit_settings_set_enable_smooth_scrolling (t, TRUE);
	webkit_settings_set_enable_accelerated_2d_canvas (t, TRUE);
	webkit_settings_set_enable_write_console_messages_to_stdout (t, FALSE);
	webkit_settings_set_enable_media_stream (t, TRUE);
	webkit_settings_set_enable_spatial_navigation (t, TRUE);
	webkit_settings_set_enable_mediasource (t, TRUE);
	
	if (old == NULL)
	{
		this->webview = webkit_web_view_new ();
		webkit_web_context_set_process_model (webkit_web_view_get_context((WebKitWebView*) this->webview), WEBKIT_PROCESS_MODEL_SHARED_SECONDARY_PROCESS);
		webkit_web_view_set_settings ((WebKitWebView*) this->webview,t);
	}
	else
	{
		this->webview = webkit_web_view_new_with_related_view ((WebKitWebView*) old);
	}

	SESdotJS js(webkit_web_view_get_javascript_global_context((WebKitWebView*)this->webview)); // used as an accelerator now

}

MainWindow::MainWindow (int width, int height, GtkWidget* old, gpointer b)
{
	// title bar
	gtk_header_bar_set_title ((GtkHeaderBar*) this->headerbar, "SESBrowser");
	gtk_header_bar_set_show_close_button ((GtkHeaderBar*) this->headerbar, TRUE);
	gtk_window_set_titlebar ((GtkWindow*) this->window, this->headerbar);
	
	// webview
	this->create_webview (old);
	
	// gui
	gtk_container_add ((GtkContainer*) this->scroll, this->webview);
	gtk_container_add ((GtkContainer*) this->window, this->scroll);
	
	this->action.init ((WebKitWebView*) this->webview, b, this);
	
	// window
	gtk_window_set_default_size ((GtkWindow*) this->window, width, height);
}

