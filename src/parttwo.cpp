/*
 * parttwo.cpp
 *
 *  Created on: Dec 15, 2013
 *      Author: visitor15
 */

#include "parttwo.h"

int main() {
	srand(time(0));

	part_two self;
	self.show_menu();

	return EXIT_SUCCESS;
}

void part_two::show_menu() {
	int _choice = -1;

	std::cout << "\n\n\n=====================================" << std::endl;
	std::cout << "Part B" << std::endl;
	std::cout << "=====================================\n" << std::endl;
	std::cout << "\t1. FIFO" << std::endl;
	std::cout << "\t2. LRU" << std::endl;
	std::cout << "\t3. Second Chance" << std::endl;
	std::cout << "\n\nOption: ";
	std::cin >> _choice;

	switch (_choice) {
	case 1: {
		run_type = FIFO;
		break;
	}
	case 2: {
		run_type = LRU;
		break;
	}
	case 3: {
		run_type = SECOND_CHANCE;
		break;
	}
	default: {
		std::cout << "ERROR: Wrong option chosen\n\n" << std::endl;
		show_menu();
	}
	}

	start();
}

void part_two::start() {
	init_memory();

	proc_t kernel;
	process::GENERATE_KERNEL_PROC(kernel, 1);
	load_process(kernel);

	process::GENERATE_PROCS(READY_QUEUE, MAX_PROCESSES_P2);

	/*
	 * MAIN LOOP
	 */
	do {
		sleep(1);
		execute_cycle();
		print_memory_map();

	} while (has_cycle());

	std::cout << "\n\nFINISHED!\n\n" << std::endl;
}

bool part_two::has_cycle() {
	return (RUNNING_QUEUE.size() > 0);
}

void part_two::init_memory() {

}

void part_two::execute_cycle() {

}

bool part_two::load_process(proc_t &proc) {
	return true;
}

bool part_two::unload_process(proc_t &proc) {
	return true;
}

void part_two::print_memory_map() {

}
