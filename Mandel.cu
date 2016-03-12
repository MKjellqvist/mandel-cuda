/*
 * Mandel.cu
 *
 *  Created on: Jan 17, 2016
 *      Author: martin
 *
 *      Trying to setup a window in gtk to show random data produced by the GPU
 */

#include <thrust/device_vector.h>

#include "Application.h"

int main(int argc, char** argv){
	Application app(argc, argv);

	app.start();
	cudaDeviceReset();
}


