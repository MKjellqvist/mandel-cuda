/*
 * MainWindow.h
 *
 *  Created on: Jan 17, 2016
 *      Author: martin
 */

#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/builder.h>
#include "DrawArea.h"

class MainWindow:public Gtk::Window {
public:
	MainWindow();
	//MainWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refBuilder);
    Gtk::Box box; // Layout
    Gtk::Button plotOnOff;
    DrawArea drawArea;
    void on_click();
};

#endif /* MAINWINDOW_H_ */
