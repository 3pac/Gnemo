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
	mw.init = mainWindowInit;
	mw.cw.init = closeWindowInit;
}

//==================Drawing Surface===================//
static void clearSurface (GtkWidget *widget, gpointer data)
{
	//cairo_t cr;
	//cr = cairo_create ()
}


//====================Close Window====================//
static gboolean closeWindowInit (GtkWidget *widget, gpointer data)
{
	mw.cw.window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (mw.cw.window), "Close Window");
	gtk_container_set_border_width (GTK_CONTAINER (mw.cw.window), 10);

	mw.cw.grid = gtk_grid_new ();
	gtk_container_add (GTK_CONTAINER (mw.cw.window), mw.cw.grid);

	mw.cw.label = gtk_label_new ("Are You Sure You Want To Quit?");
	gtk_grid_attach (GTK_GRID (mw.cw.grid), mw.cw.label, 0, 0, 2, 1);
	
	mw.cw.button = gtk_button_new_with_label ("No");
	g_signal_connect_swapped (mw.cw.button, "clicked", G_CALLBACK (gtk_widget_destroy), mw.cw.window);
	gtk_grid_attach (GTK_GRID (mw.cw.grid), mw.cw.button, 0, 1, 1, 1);

	mw.cw.button = gtk_button_new_with_label ("Yes");
	g_signal_connect_swapped (mw.cw.button, "clicked", G_CALLBACK (gtk_widget_destroy), mw.window);
	gtk_grid_attach (GTK_GRID (mw.cw.grid), mw.cw.button, 1, 1, 1, 1);

	gtk_widget_show_all (mw.cw.window);

	return TRUE;
}

//====================Main Window====================//
void mainWindowInit (void)
{
	mw.window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_default_size (GTK_WINDOW (mw.window), 500, 320);
	gtk_window_set_title (GTK_WINDOW (mw.window), "Hello World!\n");
	gtk_container_set_border_width (GTK_CONTAINER (mw.window), 10);

	mw.grid = gtk_grid_new ();
	gtk_container_add (GTK_CONTAINER (mw.window), mw.grid);

	g_signal_connect (mw.window, "delete-event", G_CALLBACK (mw.cw.init), NULL);
	g_signal_connect (mw.window, "destroy", G_CALLBACK (gtk_main_quit), NULL);

	gtk_widget_show_all (mw.window);
}