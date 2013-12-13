/*
 * parttwo.cpp
 *
 *  Created on: Dec 10, 2013
 *      Author: visitor15
 */

#include "partone.h"

int main() {
	srand(time(0));

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
//
//	for (int i = 0; i < BACKING_STORE.size(); i++) {
//		usleep(250);
//		load_process(BACKING_STORE.at(i));
//
//		print_memory_map();
//
//
//	}

	do {
		sleep(1);
		execute_cycle();
		print_memory_map();

	} while (has_cycle());

	std::cout << "\n\nFINISHED!\n\n" << std::endl;

	print_memory_map();
}

void part_one::init_mem(bool load_kernel) {
	for (int i = 0; i < MAX_MEMORY; i++) {
		MAIN_MEMORY[i] = EMPTY;
	}
}

void part_one::execute_cycle() {
	std::vector<proc_t> TMP;
	int _size;
	int i = 0;
	std::cout << "RUNNING QUEUE SIZE: " << RUNNING_QUEUE.size() << std::endl;
	for (i = 0; i < RUNNING_QUEUE.size(); i++) {
		int _burst_time = RUNNING_QUEUE.at(i).BURST_TIME;
		std::cout << "CURRENT BURST TIME 1: " << RUNNING_QUEUE.at(i).BURST_TIME
				<< std::endl;
		RUNNING_QUEUE.at(i).BURST_TIME = (_burst_time - 1);
		std::cout << "CURRENT BURST TIME 2: " << RUNNING_QUEUE.at(i).BURST_TIME
				<< std::endl;

		if (RUNNING_QUEUE.at(i).BURST_TIME == 0) {
			if (unload_process(RUNNING_QUEUE.at(i))) {

				RUNNING_QUEUE.erase(RUNNING_QUEUE.begin() + i);
			}
		}
	}

	if (BACKING_STORE.size() > 0) {
		if (load_process(BACKING_STORE.at(0))) {
			std::cout << "PUSHING BACK PROC AT (" << BACKING_STORE.at(0).SEGMENTS.at(0).BASE << ", " << BACKING_STORE.at(0).SEGMENTS.at(0).LIMIT << ")" << std::endl;
			RUNNING_QUEUE.push_back(BACKING_STORE.at(0));
			BACKING_STORE.erase(BACKING_STORE.begin());
		}
	}
}

int i = 0;
int _print_state = 0;
void part_one::print_memory_map() {
//	formatDetails();

	i = 0;
	for (; i <= MAX_MEMORY; i++) {
		switch (_print_state) {
		case 0: {

			if (i > 0) {
				if (i % 5 == 0) {
					if (i % 10 == 0) {
						if (i < 100) {
							std::cout << "        " << i;
						} else if (i < 1000) {
							std::cout << "       " << i;
						} else {
							std::cout << "      " << i;
						}
					}
				}
			}

			if ((i > 0) && (i % 80 == 0)) {
				_print_state += 1;
				std::cout << "\n";
				i = (i - 80);
			}

			continue;
		}
		case 1: {

			if (i % 5 == 0) {
				if (i % 10 == 0) {
					std::cout << "|";
				} else {
					std::cout << "+";
				}
			} else {
				std::cout << "-";
			}

			if ((i > 0) && (i % 80 == 0)) {
				_print_state += 1;
				std::cout << std::endl;
				i = (i - 80);
			}

			continue;
		}
		case 2: {
			std::cout << MAIN_MEMORY[i - 1];

			if ((i > 0) && (i % 80 == 0)) {
				_print_state = 0;
				std::cout << "" << std::endl;
			}

			continue;
		}
		}
	}

	std::cout
			<< "================================================================================"
			<< std::endl;
}

bool part_one::has_cycle() {
	return (RUNNING_QUEUE.size() > 0);
}

bool part_one::load_process(proc_t &proc) {

	if (request_free_memory(proc)) {
		std::cout << "LOADING PROC: " << proc.PID << std::endl;
		for (int i = 0; i < proc.SEGMENTS.size(); i++) {
			segment_t seg = proc.SEGMENTS.at(i);
			for (int k = seg.BASE; k <= seg.LIMIT; k++) {

				MAIN_MEMORY[k] = proc.PID;
			}
		}
		return true;
	}

	return false;
}

bool part_one::unload_process(proc_t &proc) {
	int _base = proc.SEGMENTS.at(0).BASE;
	int _limit = proc.SEGMENTS.at(0).LIMIT;

	std::cout << "UNLOADING PROC: " << proc.PID << " AT: (" << _base << ", " << _limit << std::endl;

	for (int i = _base; i <= _limit; i++) {
		MAIN_MEMORY[i] = EMPTY;
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
				std::cout << "SETTING: " << hole.first << " AND " << hole.second
						<< std::endl;

				proc.SEGMENTS.at(0).BASE = hole.first;
				proc.SEGMENTS.at(0).LIMIT = hole.first + proc.SIZE;

//				std::cout << "S"

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
			for (j = (i + 1); j < MAX_MEMORY; j++) {
				if (MAIN_MEMORY[j] == EMPTY) {
					continue;
				} else {
					break;
				}

			}

			std::cout << "PAIRING: " << i << " AND " << j << std::endl;

			list.push_back(std::make_pair(i, j));
			break;
		}
	}

	return (list.size() > 0);
}

