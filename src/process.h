/*
 * process.h
 *
 *  Created on: Dec 10, 2013
 *      Author: visitor15
 */

#ifndef PROCESS_H_
#define PROCESS_H_

#include "global.h"

struct segment_t {
	unsigned int 			BASE;
	unsigned int 			LIMIT;
	char					DATA[0];

} segment;

struct proc_t {
	char 					PID;
	unsigned int 			SIZE;
	unsigned int 			BURST_TIME;

	std::vector<segment>	SEGMENTS;

} process;

class process {
public:
	static process* p_instance;

	static bool GENERATE_KERNEL_PROC(process &proc);
	static bool GENERATE_PROCS(process &proc_list[], unsigned int count);

private:


	process() {};
	~process() {};

	void init_proc_IDs();
};

#endif /* PROCESS_H_ */
