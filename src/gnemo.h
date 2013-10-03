/*
 * gnemo.h
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

#ifndef GNEMO_H
#define GNEMO_H

#include <gtk/gtk.h>

struct CLOSEWINDOW;
struct MAINWINDOW;

typedef struct 
{
	GtkWidget 			*window;
	GtkWindowPosition 	windowPos;
	
	gboolean 			(*init) 				(GtkWidget*, gpointer);
} CLOSEWINDOW;

typedef struct 
{
	int					tabCount;
	GtkWidget 			*button;
	GtkWidget 			*notebook;
	GtkWidget 			*overallPaned;
	GtkWidget 			*leftPaned;
	GtkWidget 			*rightPaned;
	GtkWidget 			*tabs;
	GtkWidget 			*textEditor[15];
	GtkWidget			*grid;
	GtkWidget 			*window;
	
	void 				(*init) 				(void);
	gint	 			(*newDocument)			(GtkWidget*, gpointer);
	CLOSEWINDOW 		cw;
} MAINWINDOW;

void 			gnemoInit 				(void);
void 			mainWindowInit 			(void);
gboolean		closeWindowInit 		(GtkWidget*, gpointer);
gint 			newDocument				(GtkWidget*, gpointer);
#endif