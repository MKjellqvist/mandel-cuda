/*
 * DrawArea.cpp
 *
 *  Created on: Jan 17, 2016
 *      Author: martin
 */

#include "DrawArea.h"
#include <gdkmm.h>

DrawArea::DrawArea():SCROLL_SCALE_ZOOM(1.8) {
	// TODO Auto-generated constructor stub
	add_events(Gdk::SCROLL_MASK);
	view[RTOP] = -2.0;
	view[RLEFT] = -2.0;
	view[RWIDTH] = 4.0;
	view[RHEIGHT] = 0.0;
}

DrawArea::~DrawArea() {
	// TODO Auto-generated destructor stub
}
void DrawArea::plot(unsigned int x, unsigned int y, unsigned int color) {
    if (!pixBuf) return;
    size_t height = pixBuf->get_height();
    size_t width = pixBuf->get_width();
    // check bounds
    if (x < 0 || x >= width || y < 0 || y >= height) {
        return;
    }
    guint8* pixData = pixBuf->get_pixels();

    int stride = pixBuf->get_rowstride();

    pixData[x * 3 + stride * y ] = color&0xFF;
    pixData[x * 3 + stride * y + 1] = (color>>8)&0xFF;
    pixData[x * 3 + stride * y + 2] = (color>>16)&0xFF;
}
void DrawArea::adjustViewAspect(){
	view[RHEIGHT] = view[RWIDTH] * double(get_height()) / get_width();
}
bool DrawArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr) {
    if (!pixBuf) {
    	if ( get_width() > 0 && get_height() > 0){
    		pixBuf = Gdk::Pixbuf::create(Gdk::COLORSPACE_RGB, false, 8, get_width(), get_height());
    		pixBuf->fill(0xffffffff);
    		adjustViewAspect();
    	}else{
    		return false;
    	}
    }

    oldWindow = get_allocation();
    const int width = oldWindow.get_width();
    const int height = oldWindow.get_height();

    // Draw the image in the middle of the drawing area, or (if the image is
    // larger than the drawing area) draw the middle part of the image.
    // https://developer.gnome.org/gtkmm-tutorial/unstable/sec-draw-images.html
    Gdk::Cairo::set_source_pixbuf(cr, pixBuf,
            (width - pixBuf->get_width()) / 2, (height - pixBuf->get_height()) / 2);
    cr->paint();

    return true;

}

bool DrawArea::on_configure_event (GdkEventConfigure* conf){
	if ( get_width() > 0 && get_height() > 0){
		pixBuf = Gdk::Pixbuf::create(Gdk::COLORSPACE_RGB, false, 8, get_width(), get_height());
		pixBuf->fill(0xffffffff);
		adjustViewAspect();
	}
	return false;
}
#include "calls.h"
#include <iostream>

bool DrawArea::on_scroll_event(GdkEventScroll* scroll_event){
		// click in view
	double rx = double(scroll_event->x)/get_width();
	double ry = double(scroll_event->y)/get_height();

	std::clog << rx << ", " << ry << "\n";
	std::clog << "Was " << view[RLEFT] << ", " << view[RWIDTH] << "\n";
	std::clog << "Check: old click was at " << (view[RLEFT] + rx * view[RWIDTH]) << "\n";

	// new width and height
	// Zoom in
	if(scroll_event->direction == GDK_SCROLL_UP){
		// new top and left, zoom around rx/ry
		double newWidth = view[RWIDTH] / SCROLL_SCALE_ZOOM;
		view[RLEFT] += view[RWIDTH] * rx - rx * newWidth;
		view[RTOP] += view[RHEIGHT] * ry - view[RHEIGHT] * ry / SCROLL_SCALE_ZOOM;
		view[RWIDTH] /= SCROLL_SCALE_ZOOM;
		std::clog << "Is" << view[RLEFT] << ", " << view[RWIDTH] << "\n";
		std::clog << "Check: new click is at " << (view[RLEFT] + rx * view[RWIDTH]) << "\n";

	} else
	// Zoom out
	if(scroll_event->direction == GDK_SCROLL_DOWN){
		view[RLEFT] += view[RWIDTH] * rx - view[RWIDTH] * SCROLL_SCALE_ZOOM / 2;
		view[RTOP] += view[RHEIGHT] * ry - view[RHEIGHT] * SCROLL_SCALE_ZOOM/ 2;
		view[RWIDTH] *= SCROLL_SCALE_ZOOM;
	}
	adjustViewAspect();
	do_plot(this);
	plot(scroll_event->x, scroll_event->y, 0xFF7F7F);
	queue_draw();
	return true;
}

int DrawArea::get_buffer_width(){
	if (pixBuf)
		return pixBuf->get_width();
	return 0;
}

int DrawArea::get_buffer_height(){
	if (pixBuf)
		return pixBuf->get_height();
	return 0;
}
void DrawArea::set_buffer(unsigned int* buffer){
	int w = get_buffer_width();
	int buffer_size = get_buffer_height()*get_buffer_width();
	for(int idx = 0; idx < buffer_size; idx++){
	    guint8* pixData = pixBuf->get_pixels();

	    int stride = pixBuf->get_rowstride();
	    int x = idx % w;
	    int y = idx / w;
	    int color = buffer[idx];
	    pixData[x * 3 + stride * y ] = color&0xFF;
	    pixData[x * 3 + stride * y + 1] = (color>>8)&0xFF;
	    pixData[x * 3 + stride * y + 2] = (color>>16)&0xFF;
	}
}

double* DrawArea::get_view(){
	return view;
}
