/*
 * Application.h
 *
 *  Created on: Jan 17, 2016
 *      Author: martin
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_

class Application {
	int argc;
	char** argv;
public:
	Application(int argc, char** argv);
	int start();
};

#endif /* APPLICATION_H_ */
