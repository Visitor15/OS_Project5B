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

bool process::GENERATE_PROCS(std::vector<proc_t> &proc_list, int count, bool filter_num_PIDs) {

	if (!p_instance) {
		static process m_Self;
		p_instance = &m_Self;
		p_instance->init_proc_IDs();
	}

	for (int i = 0; i < count; i++) {
		proc_t proc;
		proc.PID = p_instance->generate_proc_ID(filter_num_PIDs);
		proc.SIZE = p_instance->generate_proc_SIZE();
		proc.BURST_TIME = p_instance->generate_proc_BURST_TIME();

		if (proc.PID != EMPTY) {
			std::cout << "GENERATED PROC " << i << ": " << proc.PID << " SIZE: "
					<< proc.SIZE << std::endl;

			proc_list.push_back(proc);
		} else {
			return (proc_list.size() > 0);
		}
	}

	return true;
}

void process::CREATE_PROC_SEGMENTS(proc_t &proc) {
	segment_t code_segment;
	code_segment.ID = '0';
	mem_page_t code_pages[2];
	code_segment.add_pages(code_pages, 2);
	proc.SEGMENTS.push_back(code_segment);

	segment_t stack_segment;
	stack_segment.ID = '1';
	mem_page_t stack_pages[3];
	stack_segment.add_pages(stack_pages, 3);
	proc.SEGMENTS.push_back(stack_segment);

	segment_t heap_segment;
	heap_segment.ID = '2';
	mem_page_t heap_pages[5];
	heap_segment.add_pages(heap_pages, 5);
	proc.SEGMENTS.push_back(heap_segment);

	char _id[1];
	int _count = ((rand() % 5) + 1);
	std::cout << "COUNT: " << _count << std::endl;
	for(int i = 0; i < _count; ++i) {
		segment_t routine_seg;
		std::string tmp_str = "";
		std::stringstream str_stream;
		str_stream << (i + 3);
		tmp_str = str_stream.str().c_str();
		strcpy(&routine_seg.ID, tmp_str.c_str());

		std::cout << "MADE ID: " << routine_seg.ID << std::endl;
		if(routine_seg.ID == EMPTY) {
			int input;
			std::cin >> input;
		}

		mem_page_t routine_pages[2];
		routine_seg.add_pages(routine_pages, 2);

		proc.SEGMENTS.push_back(routine_seg);
	}
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

char process::generate_proc_ID(bool filter_nums) {
	int _index = -1;
	int _size;
	char proc_ID = EMPTY;
	do {
		if (PROC_ID_LIST.size() > 0) {
			_index = (rand() & PROC_ID_LIST.size() - 1);
			_size = PROC_ID_LIST.size();
			proc_ID = PROC_ID_LIST.at(_index);
		}
	} while((filter_nums && isdigit(proc_ID)));

	if(proc_ID != EMPTY && (_index > -1)) {
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

