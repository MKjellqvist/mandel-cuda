/*
 * calls.cu
 *
 *  Created on: Jan 17, 2016
 *      Author: martin
 */

#include "calls.h"
#include "MandelCalculator.h"

void do_plot(Plotter* plotter){

	MandelCalculator calculator(plotter->get_buffer_height(), plotter->get_buffer_width());

	color_vector result = calculator.calc(plotter->get_view());

	plotter->set_buffer(thrust::raw_pointer_cast(result.data()));
}


