/*
 * Application.cpp
 *
 *  Created on: Jan 17, 2016
 *      Author: martin
 */

#include "Application.h"
#include <iostream>
#include <cstddef>
#include <gtkmm.h>
//#include <glibmm.h>
//#include <gtkmm/builder.h>
#include <string>
#include "MainWindow.h"

static const char* gladefile = "glade/main_interface.glade";

Application::Application(int argc, char** argv):argc(argc), argv(argv) {

}

using Glib::RefPtr;
using Gtk::Window;

int Application::start(){
	//std::string gladefile = "glade/main_interface.glade";
	  RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv,
	      "se.miun.markje.cudaimages");

	  //RefPtr<Gtk::Builder> xmlBuilder = Gtk::Builder::create_from_file(gladefile);
	  //MainWindow* window = 0;  // get_widget_derived checks for a nullptr
	  //xmlBuilder->get_widget_derived("mainWindow", window);
	  //MainWindow window;
	  MainWindow window;
	  //window.set_title("New titlwe");
	  //window.set_default_size(400, 400);
	  return app->run(window);
}
