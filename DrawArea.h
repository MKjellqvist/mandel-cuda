/*
 * DrawArea.h
 *
 *  Created on: Jan 17, 2016
 *      Author: martin
 */

#ifndef DRAWAREA_H_
#define DRAWAREA_H_
#include <glibmm/refptr.h>
#include <gtkmm/drawingarea.h>
#include <gdkmm/pixbuf.h>
//#include <gdkmm/event.h>
#include <cairomm/refptr.h>
#include <cairomm/context.h>
#include "Plotter.h"

class DrawArea:public Gtk::DrawingArea, public Plotter {
public:
	DrawArea();
	virtual ~DrawArea();
    void plot(unsigned int x, unsigned int y, unsigned int color);
    virtual int get_buffer_height();
    virtual int get_buffer_width();
    virtual void set_buffer(unsigned int* buffer);
    virtual double* get_view();
    const double SCROLL_SCALE_ZOOM;
protected:
    virtual bool on_scroll_event(GdkEventScroll* scroll_event);
    virtual bool on_configure_event(GdkEventConfigure* configure_event);
    virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr);
    Glib::RefPtr< Gdk::Pixbuf > pixBuf;
private:
    double view[4];
    Gdk::Rectangle oldWindow;
    void adjustViewAspect();
    enum {RTOP, RLEFT, RHEIGHT, RWIDTH};
};

#endif /* DRAWAREA_H_ */
