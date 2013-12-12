/*
 * parttwo.cpp
 *
 *  Created on: Dec 10, 2013
 *      Author: visitor15
 */

#include "partone.h"

int main() {

	part_one self;
	self.show_menu();

	return EXIT_SUCCESS;
}

void part_one::show_menu() {
	int _choice = -1;

	std::cout << "\n\n\n=====================================" << std::endl;
	std::cout << "Part A" << std::endl;
	std::cout << "=====================================\n" << std::endl;
	std::cout << "\t1. First-fit" << std::endl;
	std::cout << "\t2. Best-fit" << std::endl;
	std::cout << "\t3. Worst-fit" << std::endl;
	std::cout << "\n\nOption: ";
	std::cin >> _choice;

	switch (_choice) {
	case 1: {
		run_type = FIRST_FIT;
		break;
	}
	case 2: {
		run_type = BEST_FIT;
		break;
	}
	case 3: {
		run_type = WORST_FIT;
		break;
	}
	default: {
		std::cout << "ERROR: Wrong option chosen\n\n" << std::endl;
		show_menu();
	}
	}

	start();
}

void part_one::start() {
	init_mem(true);

	proc_t kernel;
	process::GENERATE_KERNEL_PROC(kernel, 1);
	load_process(kernel);
	print_memory_map();

	process::GENERATE_PROCS(BACKING_STORE, MAX_PROCESSES);

	for(int i = 0; i < BACKING_STORE.size(); i++) {
		load_process(BACKING_STORE.at(i));
	}

	print_memory_map();
}

void part_one::init_mem(bool load_kernel) {
	for (int i = 0; i < MAX_MEMORY; i++) {
		MAIN_MEMORY[i] = EMPTY;
	}
}

void part_one::print_memory_map() {
	std::cout << "\n";
	for (int i = 0; i < MAX_MEMORY; i++) {
		std::cout << " " << i << MAIN_MEMORY[i] << " ";
		if ((i > 0) && (i % 20 == 0)) {
			std::cout << "\n";
		}
	}
}

bool part_one::load_process(proc_t proc) {

	if (request_free_memory(proc)) {
		for (int i = 0; i < proc.SEGMENTS.size(); i++) {
			segment_t seg = proc.SEGMENTS.at(i);
			for (int k = seg.BASE; k < seg.LIMIT; k++) {
				MAIN_MEMORY[k] = proc.PID;
			}
		}
		return true;
	}

	return false;
}

bool part_one::request_free_memory(proc_t &proc) {

	switch (run_type) {
	case FIRST_FIT: {
		return request_mem_first_fit(proc);
	}
	case BEST_FIT: {
		return request_mem_best_fit(proc);
	}
	case WORST_FIT: {
		return request_mem_worst_fit(proc);
	}
	}

	return false;
}

bool part_one::request_mem_first_fit(proc_t &proc) {
	std::vector<std::pair<int, int> > holes;
	if (get_available_holes(holes)) {
		for (int i = 0; i < holes.size(); i++) {
			std::pair<int, int> hole = holes.at(i);
			if ((hole.second - hole.first) >= proc.SIZE) {
				proc.SEGMENTS.at(0).BASE = hole.first;
				proc.SEGMENTS.at(0).LIMIT = hole.first + proc.SIZE;

				return true;
			}
		}
	}
	return false;
}

bool part_one::request_mem_best_fit(proc_t &proc) {
	int index = 0;
	std::vector<std::pair<int, int> > holes;
	if (get_available_holes(holes)) {
		for (int i = 0; i < holes.size(); i++) {
			std::pair<int, int> hole = holes.at(i);
			if ((hole.second - hole.first) >= proc.SIZE) {
				int diff1 = (hole.second - hole.first) - proc.SIZE;
				int diff2 = (holes.at(index).second - holes.at(index).first)
						- proc.SIZE;
				if (diff1 < diff2) {
					index = i;
				}
			}
		}
		if (index) {
			std::pair<int, int> hole = holes.at(index);
			proc.SEGMENTS.at(0).BASE = hole.first;
			proc.SEGMENTS.at(0).LIMIT = hole.second;
			return true;
		}
	}

	return false;
}

bool part_one::request_mem_worst_fit(proc_t &proc) {
	int index = -1;
	std::vector<std::pair<int, int> > holes;
	if (get_available_holes(holes)) {
		for (int i = 0; i < holes.size(); i++) {
			std::pair<int, int> hole = holes.at(i);
			if ((hole.second - hole.first) >= proc.SIZE) {
				int diff1 = (hole.second - hole.first) - proc.SIZE;
				int diff2 = (holes.at(index).second - holes.at(index).first)
						- proc.SIZE;
				if (diff1 > diff2) {
					index = i;
				}
			}
		}
		if (index) {
			std::pair<int, int> hole = holes.at(index);
			proc.SEGMENTS.at(0).BASE = hole.first;
			proc.SEGMENTS.at(0).LIMIT = hole.second;
			return true;
		}
	}

	return false;
}

bool part_one::get_available_holes(std::vector<std::pair<int, int> > &list) {

	for (int i = 0; i < MAX_MEMORY; i++) {
		if (MAIN_MEMORY[i] == EMPTY) {
			int j;
			for (j = i; j < MAX_MEMORY; j++) {
				if (MAIN_MEMORY[j] == EMPTY) {
					continue;
				} else {
					break;
				}

			}
			list.push_back(std::make_pair(i, j));
			break;
		}
	}

	return (list.size() > 0);
}

