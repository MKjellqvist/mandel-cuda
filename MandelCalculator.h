/*
 * MandelCalculator.h
 *
 *  Created on: Jan 17, 2016
 *      Author: martin
 */

#ifndef MANDELCALCULATOR_H_
#define MANDELCALCULATOR_H_
#include <exception>
#include <thrust/host_vector.h>
struct CUDAException:std::exception{};
struct NoDevice:CUDAException{};

typedef unsigned int color_type;

typedef thrust::host_vector<color_type> color_vector;

class MandelCalculator {
public:
	MandelCalculator(int height, int width);
    color_vector calc(double* view);
	virtual ~MandelCalculator();
private:
	int width;
	int height;
};

#endif /* MANDELCALCULATOR_H_ */
