/*
 * parttwo.h
 *
 *  Created on: Dec 10, 2013
 *      Author: visitor15
 */

#ifndef PARTTWO_H_
#define PARTTWO_H_

#include "global.h"

class parttwo {
public:
	parttwo() {}
	~parttwo() {}

	void show_menu();
	void show_menu_a();
	void show_menu_b();
	void start();

private:
	process 				MAIN_MEMORY[MAX_MEMORY];
	std::vector<process> 	BACKING_STORE;
};

#endif /* PARTTWO_H_ */
