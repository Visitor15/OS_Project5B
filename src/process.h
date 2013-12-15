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

#define LOWER_L 108
#define UPPER_I 73

struct segment_t {
	unsigned int 			BASE;
	unsigned int 			LIMIT;
	char					DATA[0];

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
