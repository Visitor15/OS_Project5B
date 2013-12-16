/*
 * parttwo.h
 *
 *  Created on: Dec 15, 2013
 *      Author: visitor15
 */

#ifndef PARTTWO_H_
#define PARTTWO_H_

#include "global.h"
#include "process.h"
#include "memory.h"
#include "page_fault_exception.h"

class part_two {
public:
	START_VALUE run_type;

	part_two() { run_type = FIFO; }
	~part_two() {}

	void show_menu();
	void start();

private:
	mem_frame_t				MAIN_MEMORY[MAX_FRAMES];
	mem_page_t				BACKING_STORE[MAX_PAGES];
	std::vector<proc_t>		READY_QUEUE;
	std::vector<proc_t>		RUNNING_QUEUE;

	void init_memory();

	void execute_cycle();

	bool load_process(proc_t &proc);

	bool unload_process(proc_t &proc);

	void write_to_frame(char PID, char segment_ID, int frame_index);

	bool request_free_frame(mem_page_t &page);

	bool has_cycle();

	void print_memory_map();
};

#endif /* PARTTWO_H_ */
