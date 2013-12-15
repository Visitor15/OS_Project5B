/*
 * process.cpp
 *
 *  Created on: Dec 10, 2013
 *      Author: visitor15
 */

#include "process.h"

bool process::GENERATE_KERNEL_PROC(proc_t &proc, int segment_count) {
	proc.PID = KERNEL_PROC_ID;
	proc.BURST_TIME = -1;
	proc.SIZE = DEF_KERNEL_SIZE;

	for (int i = 0; i < segment_count; i++) {
		segment_t segment;
		proc.SEGMENTS.push_back(segment);
	}

	return true;
}

bool process::GENERATE_PROCS(std::vector<proc_t> &proc_list, int count) {

	if (!p_instance) {
		static process m_Self;
		p_instance = &m_Self;
		p_instance->init_proc_IDs();
	}

	for (int i = 0; i < count; i++) {
		proc_t proc;
		proc.PID = p_instance->generate_proc_ID();
		proc.SIZE = p_instance->generate_proc_SIZE();
		proc.BURST_TIME = p_instance->generate_proc_BURST_TIME();
		proc.SEGMENTS.push_back(segment_t());

		if (proc.PID != EMPTY) {
			std::cout << "GENERATED PROC: " << proc.PID << " SIZE: "
					<< proc.SIZE << std::endl;

			proc_list.push_back(proc);
		} else {
			return (proc_list.size() > 0);
		}
	}

	return true;
}

void process::init_proc_IDs() {
	int i;
	for (i = 48; i < 58; i++) {
		PROC_ID_LIST.push_back((char) i);
	}

	for (i = 65; i < 91; i++) {
		if ((i != UPPER_I)) {
			PROC_ID_LIST.push_back((char) i);
		}
	}

	for (i = 97; i < 123; i++) {
		if (i != LOWER_L) {
			PROC_ID_LIST.push_back((char) i);
		}
	}
}

char process::generate_proc_ID() {
	char proc_ID = EMPTY;
	if (PROC_ID_LIST.size() > 0) {
		int _index = (rand() & PROC_ID_LIST.size() - 1);
		int _size = PROC_ID_LIST.size();

		proc_ID = PROC_ID_LIST.at(_index);

		// Erasing char from list
		PROC_ID_LIST.erase(PROC_ID_LIST.begin() + _index);
	}

	return proc_ID;
}

unsigned int process::generate_proc_SIZE() {
	return (rand() % (MAX_MEMORY_PER_PROC - MIN_MEMORY_PER_PROC)
			+ MIN_MEMORY_PER_PROC);
}

unsigned int process::generate_proc_BURST_TIME() {
	return (rand() % (MAX_BURST - MIN_BURST) + MIN_BURST);
}

