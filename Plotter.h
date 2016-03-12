/*
 * Plotter.h
 *
 *  Created on: Jan 17, 2016
 *      Author: martin
 */

#ifndef PLOTTER_H_
#define PLOTTER_H_

class Plotter {
public:
    virtual void plot(unsigned int x, unsigned int y, unsigned int color) = 0;
    virtual ~Plotter();
    virtual int get_buffer_height() = 0;
    virtual int get_buffer_width() = 0;
    virtual void set_buffer(unsigned int* buffer) = 0;
    virtual double* get_view() = 0;
};

#endif /* PLOTTER_H_ */
