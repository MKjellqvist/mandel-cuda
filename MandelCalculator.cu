/*
 * MandelCalculator.cpp
 *
 *  Created on: Jan 17, 2016
 *      Author: martin
 */

#include "MandelCalculator.h"

#include <thrust/device_vector.h>
#include <thrust/complex.h>

MandelCalculator::MandelCalculator(int height, int width):width(width), height(height) {
	int count;
	cudaGetDeviceCount(&count);
	if ( !count )
		throw NoDevice();
	cudaSetDevice(0);
}

MandelCalculator::~MandelCalculator() {
	cudaDeviceSynchronize();
}

typedef thrust::complex<double> complex;

__device__ void abs_squared(const complex& value, double* return_value){
	*return_value = value.imag() * value.imag() + value.real() * value.real();
}
__device__ void iterations_until_divergence(double x, double y, int* result){
	const double DIVERGE_LIMIT = 100.0;
	const int MAX_ITERATIONS = 250;
	complex start(x, y);
	complex current(start);
	*result = 20;
	for(int iterations = 0;iterations < MAX_ITERATIONS; iterations++){
		current *= current;
		current += start;
		double abs;
		abs_squared(current, &abs);
		if( abs > DIVERGE_LIMIT){
			*result = iterations;
			return;
		}
	}
	return;
}
#define N_MANDEL_THREADS 256
__global__ void mandel_calc(color_type* data, int width, int height, double window_height,
		double window_width, double window_top, double window_left){
	int imgIdx  = blockIdx.x * N_MANDEL_THREADS + threadIdx.x;
	int x = imgIdx % width;
	int y = imgIdx / width;

	double dx = window_width * double(x) / width + window_left;
	double dy = window_height * double(y) / height + window_top;
	int iter;
	iterations_until_divergence(dx, dy, &iter);
	data[imgIdx] =  iter * 0x020306;
}

color_vector MandelCalculator::calc(double* view){
	thrust::device_vector<color_type> data(width*height);

	color_type* data_ptr = thrust::raw_pointer_cast(data.data());

	mandel_calc<<<width*height/N_MANDEL_THREADS, N_MANDEL_THREADS>>>(data_ptr, width, height, view[2], view[3], view[0], view[1]);

	color_vector result = data;
	data.clear();
	return result;
}
