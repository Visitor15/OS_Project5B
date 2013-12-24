/*
 * process.h
 *
 *  Created on: Dec 10, 2013
 *      Author: visitor15
 */

#ifndef PROCESS_H_
#define PROCESS_H_

#include "global.h"
#include "memory.h"
#include "page_fault_exception.h"

#define LOWER_L 108
#define UPPER_I 73

struct segment_t {
	char					ID;
	char					DATA[0];
	unsigned int 			BASE;
	unsigned int 			LIMIT;
	unsigned int			SEGMENT_TYPE;
	bool					IS_LOADED;

	std::vector<mem_page_t>	PAGES;
	unsigned int			PAGE_COUNT;

	void add_pages(mem_page_t pages[], int page_count) {
		PAGE_COUNT = page_count;
		for(int i = 0; i < page_count; i++) {
			PAGES.push_back(pages[i]);
		}
	}

	void touch() {
		for(int i = 0; i < PAGE_COUNT; i++) {
			std::cout << "TOUCH FRAME INDEX: " << PAGES.at(i).ALLOC_FRAME_INDEX << std::endl;
			if(PAGES.at(i).ALLOC_FRAME_INDEX == -1) {
				throw PageFaultException(i);
			}
		}
	}
};

struct proc_t {
	char 					PID;
	unsigned int 			SIZE;
	unsigned int 			BURST_TIME;

	std::vector<segment_t>	SEGMENTS;

};

class process {
public:
	static bool GENERATE_KERNEL_PROC(proc_t &proc, int segment_count);
	static bool GENERATE_PROCS(std::vector<proc_t> &proc_list, int count);
	static void CREATE_PROC_SEGMENTS(proc_t &proc);

private:
	std::vector<char> PROC_ID_LIST;

	process() {};
	~process() {};

	void init_proc_IDs();
	char generate_proc_ID();
	unsigned int generate_proc_SIZE();
	unsigned int generate_proc_BURST_TIME();
};

static process* p_instance;

#endif /* PROCESS_H_ */
