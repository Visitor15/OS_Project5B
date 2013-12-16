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
	for (int i = 0; i < MAX_PROCESSES_P2; i++) {
		process::CREATE_PROC_SEGMENTS(READY_QUEUE.at(i));
	}
	std::cout << "LOLLIPOP" << std::endl;
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
	bool _should_continue = false;
	int _index;
	proc_t* process;
	segment_t* seg;
	if (RUNNING_QUEUE.size() > 0) {
		_index = (rand() % RUNNING_QUEUE.size());

		// Touching random process
		process = &RUNNING_QUEUE.at(_index);
	} else if (READY_QUEUE.size() > 0) {
		_index = (rand() % READY_QUEUE.size());

		// Touching random process
		process = &READY_QUEUE.at(_index);
	}
	// Getting index for subroutine segment
	_index = (rand() % (process->SEGMENTS.size() - SEGMENT_ROUTINE))
			+ SEGMENT_ROUTINE;
	int i = 0;
	do {
		try {

			for (; i < SEGMENT_ROUTINE; i++) {
				seg = &process->SEGMENTS.at(i);
				seg->touch();
			}

			// Touching random subroutine segment
			seg = &process->SEGMENTS.at(_index);
			seg->touch();

			_should_continue = false;

		} catch (PageFaultException &e) {
//			std::cout << "HIT FOR: " << e._index << std::endl;
			if (!request_free_frame(seg->PAGES[e._index])) {
				/* If we couldn't get a free frame, we assume the main memory
				 * is full so we default to removing a random proc's registered
				 * memory frame and use that one.
				 */
				_index = (rand() % RUNNING_QUEUE.size());
				proc_t * _proc = &RUNNING_QUEUE.at(_index);
				_index = (rand() % _proc->SEGMENTS.size());
				segment_t * _segment = &(*_proc).SEGMENTS.at(_index);
				_index = (rand() % _segment->PAGE_COUNT);

				seg->PAGES[e._index].ALLOC_FRAME_INDEX =
						_segment->PAGES[_index].ALLOC_FRAME_INDEX;
				_segment->PAGES[_index].ALLOC_FRAME_INDEX = -1;

				write_to_frame(process->PID, _segment->ID,
						_segment->PAGES[e._index].ALLOC_FRAME_INDEX);
				delete _proc;
				delete _segment;
				std::cout << " LALALA " << std::endl;
			}

			_should_continue = true;
		}
	} while (_should_continue);
}

bool part_two::load_process(proc_t &proc) {
	return true;
}

bool part_two::unload_process(proc_t &proc) {
	return true;
}

bool part_two::request_free_frame(mem_page_t &page) {
	for(int i = 0; i < MAX_FRAMES; i++) {

	}
}

void part_two::write_to_frame(char PID, char segment_ID, int frame_index) {
	MAIN_MEMORY[frame_index].DATA[0] = PID;
	MAIN_MEMORY[frame_index].DATA[1] = segment_ID;
}

void part_two::print_memory_map() {
	for (int i = 0; i < MAX_FRAMES; i++) {
		std::cout << MAIN_MEMORY[i].DATA << std::endl;
	}
}
