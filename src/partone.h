/*
 * parttwo.h
 *
 *  Created on: Dec 10, 2013
 *      Author: visitor15
 */

#ifndef PARTTWO_H_
#define PARTTWO_H_

#include "global.h"
#include "process.h"

enum START_VALUE {
	FIRST_FIT = 0,
	BEST_FIT = 1,
	WORST_FIT = 2
};

class part_one {
public:
	START_VALUE run_type;

	part_one() { run_type = FIRST_FIT; }
	~part_one() {}

	void show_menu();
	void start();

private:
	char 					MAIN_MEMORY[MAX_MEMORY];
	std::vector<proc_t> 	BACKING_STORE;

	void init_mem(bool init_kernel);

	bool load_process(proc_t proc);

	bool request_free_memory(proc_t &proc);

	bool request_mem_first_fit(proc_t &proc);

	bool request_mem_best_fit(proc_t &proc);

	bool request_mem_worst_fit(proc_t &proc);

	bool get_available_holes(std::vector<std::pair<int, int> > &list);




	void print_memory_map();
};

#endif /* PARTTWO_H_ */
