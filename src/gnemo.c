/*
 * gnemo.c
 *
 * Copyright (C) 2013 - david
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "gnemo.h"

MAINWINDOW mw;

//==================Initialize Gnemo==================//
void gnemoInit ()
{
	mw.tabCount = 0;
	
	mw.init = mainWindowInit;
	mw.cw.init = closeWindowInit;
	mw.newDocument = newDocument;
}

//====================Close Window====================//
gboolean closeWindowInit (GtkWidget *widget, gpointer data)
{
	mw.cw.window = gtk_message_dialog_new (GTK_WINDOW (mw.window), GTK_DIALOG_DESTROY_WITH_PARENT,
											GTK_MESSAGE_WARNING, GTK_BUTTONS_YES_NO,
											"Are you sure you would like to quit?");
	gint ret = gtk_dialog_run (GTK_DIALOG (mw.cw.window));
	gtk_widget_destroy (mw.cw.window);
	
	if (ret == GTK_RESPONSE_YES)
		return FALSE;
	else
		return TRUE;
}

//====================Main Window====================//
void mainWindowInit (void)
{	
	mw.window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_default_size (GTK_WINDOW (mw.window), 500, 320);
	gtk_window_set_title (GTK_WINDOW (mw.window), "Hello World!\n");
	gtk_container_set_border_width (GTK_CONTAINER (mw.window), 10);
	
	mw.button = gtk_button_new_with_label ("New Page.");
	
	mw.textEditor[mw.tabCount] = gtk_text_view_new ();
	gtk_text_view_set_accepts_tab (GTK_TEXT_VIEW (mw.textEditor[mw.tabCount]), TRUE);
	
	mw.notebook = gtk_notebook_new ();
	gtk_notebook_append_page (GTK_NOTEBOOK (mw.notebook), mw.textEditor[mw.tabCount], NULL);
	
	mw.overallPaned = gtk_paned_new (GTK_ORIENTATION_HORIZONTAL);
	mw.leftPaned = gtk_paned_new (GTK_ORIENTATION_VERTICAL);
	mw.rightPaned = gtk_paned_new (GTK_ORIENTATION_VERTICAL);

	gtk_paned_set_position (GTK_PANED (mw.overallPaned), 50);
	gtk_paned_set_position (GTK_PANED (mw.leftPaned), 50);
	gtk_paned_set_position (GTK_PANED (mw.rightPaned), 50);
	
	gtk_paned_pack1 (GTK_PANED (mw.rightPaned), mw.notebook, TRUE, TRUE);
	gtk_paned_pack2 (GTK_PANED (mw.rightPaned), mw.button, TRUE, TRUE);
	gtk_paned_pack1 (GTK_PANED (mw.overallPaned), mw.leftPaned, TRUE, TRUE);
	gtk_paned_pack2 (GTK_PANED (mw.overallPaned), mw.rightPaned, TRUE, TRUE);
	gtk_widget_set_size_request (mw.leftPaned, 50, -1);
	gtk_widget_set_size_request (mw.rightPaned, 50, -1);
	gtk_container_add (GTK_CONTAINER (mw.window), mw.overallPaned);
	
	g_signal_connect (mw.button, "pressed", G_CALLBACK (mw.newDocument), NULL);
	g_signal_connect (mw.window, "delete-event", G_CALLBACK (mw.cw.init), NULL);
	g_signal_connect (mw.window, "destroy", G_CALLBACK (gtk_main_quit), NULL);

	gtk_widget_show_all (mw.window);
}

//====================Callbacks====================//
gint newDocument (GtkWidget *widget, gpointer data)
{
	//Only allow 15 tabs right now.
	if (mw.tabCount >= 14)
		return -1;
	
	mw.tabCount++;
	mw.textEditor[mw.tabCount] = gtk_text_view_new ();
	gtk_notebook_append_page (GTK_NOTEBOOK (mw.notebook), mw.textEditor[mw.tabCount], NULL);
	
	gtk_widget_show_all (mw.notebook);
	
	return mw.tabCount;
}
