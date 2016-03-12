/*
 * MainWindow.cpp
 *
 *  Created on: Jan 17, 2016
 *      Author: martin
 */

#include "MainWindow.h"
#include "calls.h"

#include <glibmm/ustring.h>

MainWindow::MainWindow(){
    set_default_size(1024, 768);
    //set_icon_from_file("/usr/share/icons/unity-icon-theme/apps/128/work.svg");
    //Glib::ustring title = get_title();
    //title.assign("Hello");
    //set_title(title);

    box.set_orientation(Gtk::ORIENTATION_VERTICAL);
    add(box);
    plotOnOff.set_label("Plot");
    box.pack_start(plotOnOff, false, false, 1 );
    box.pack_start(drawArea);

    Gdk::RGBA backColor = Gdk::RGBA();
    backColor.set_grey(0.8);
    plotOnOff.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_click));
    //drawArea.signal_scroll_event().connect(  )
    // drawArea.signal_scroll_event().connect(sigc::mem_fun(*this, &MainWindow::on_click_bool));
    show_all_children();
}


void MainWindow::on_click(){
	do_plot(&drawArea);
    drawArea.queue_draw();
}
/*
MainWindow::MainWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refBuilder):Gtk::ApplicationWindow(cobject) {
	// TODO Auto-generated constructor stub

}*/

