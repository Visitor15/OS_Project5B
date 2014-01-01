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

	process::GENERATE_PROCS(RUNNING_QUEUE, MAX_PROCESSES_P2, true);
	for (int i = 0; i < MAX_PROCESSES_P2; i++) {
		process::CREATE_PROC_SEGMENTS(RUNNING_QUEUE.at(i));

		for (int j = 0; j < RUNNING_QUEUE.at(i).SEGMENTS.size(); j++) {
			std::cout << "GENERATED SEG ID: "
					<< RUNNING_QUEUE.at(i).SEGMENTS.at(j).ID << std::endl;
		}
	}
//	std::cout << "LOLLIPOP" << std::endl;
	/*
	 * MAIN LOOP
	 */
	do {
//		sleep(1);
		cycle();
//		print_memory_map();

//		print_memory_map();
//			sleep(1);

	} while (has_cycle());

	std::cout << "\n\nFINISHED!\n\n" << std::endl;
	print_memory_map();
}

bool part_two::has_cycle() {
	return (RUNNING_QUEUE.size() > 0);
}

void part_two::init_memory() {
}

void part_two::cycle() {
	int _index;
	proc_t* process;

	for (int i = 0; i < RUNNING_QUEUE.size(); i++) {
		int _burst_time = RUNNING_QUEUE.at(i).BURST_TIME;
		RUNNING_QUEUE.at(i).BURST_TIME = (_burst_time - 1);

		if (RUNNING_QUEUE.at(i).BURST_TIME == 0) {
			if (unload_process(RUNNING_QUEUE.at(i))) {

				std::cout << "Erasing at " << i << std::endl;
				RUNNING_QUEUE.erase(RUNNING_QUEUE.begin() + i);
			}
		}
	}

	if (RUNNING_QUEUE.size() > 0) {
		_index = (rand() % RUNNING_QUEUE.size());
		// Touching random process
		process = &RUNNING_QUEUE.at(_index);

		if (RUNNING_QUEUE.at(_index).PID == KERNEL_PROC_ID) {
			// We'll just recursively call
			cycle();
		}

		execute_cycle(process);
	}
}

void part_two::execute_cycle(proc_t* process) {
	int _index = (rand() % (process->SEGMENTS.size() - SEGMENT_ROUTINE))
			+ (SEGMENT_ROUTINE);

	segment_t* seg;
	for (int i = 0; i < SEGMENT_ROUTINE;) {
		std::cout << "i is: " << i << std::endl;
		seg = &process->SEGMENTS.at(i);
		try {
			std::cout << "1 TOUCHING SEG INDEX: " << i << " FOR SEG LIST SIZE: "
					<< process->SEGMENTS.size() << std::endl;
			seg->touch();

			// Touching random subroutine segment
			std::cout << "2 TOUCHING SEG INDEX: " << _index
					<< " FOR SEG LIST SIZE: " << process->SEGMENTS.size()
					<< std::endl;
			seg = &process->SEGMENTS.at(_index);
			seg->touch();
			seg->IS_LOADED = true;

			i++;
		} catch (PageFaultException &e) {
			std::cout << "PAGE FAULT" << std::endl;
			bool _should_continue = true;

			// Request memory pages from BACKING_STORE here.

			for (int j = 0; j < e.indices.size(); j++) {
				std::cout << "HIT! FOR LIST SIZE: " << e.indices.size()
						<< " AND j: " << j << std::endl;
				int _index = e.indices.at(j);
				if (!request_free_frame(seg->PAGES[_index])) {
					int _page_index = e.indices.at(j);
					int _mem_index;
					do {

						_mem_index = (rand() % MAX_FRAMES);
					} while (MAIN_MEMORY[_mem_index].DATA[0] == KERNEL_PROC_ID);

					proc_t proc;
					bool _has_proc;
					int tmp_index = -1;
					char PID = MAIN_MEMORY[_mem_index].DATA[0];
					for (int i = 0; i < RUNNING_QUEUE.size(); i++) {
						if (RUNNING_QUEUE.at(i).PID == PID) {
							proc = RUNNING_QUEUE.at(i);
							tmp_index = i;
							_has_proc = true;
							break;
						}
					}

					if (_has_proc) {
						_should_continue = true;
						for (int j = 0; j < proc.SEGMENTS.size(); j++) {
							segment_t segment = proc.SEGMENTS.at(j);
							for (int k = 0; k < segment.PAGE_COUNT; k++) {
								if (segment.PAGES.at(k).ALLOC_FRAME_INDEX
										== _mem_index) {
									segment.PAGES.at(k).ALLOC_FRAME_INDEX = -1;

									RUNNING_QUEUE.at(tmp_index).SEGMENTS.at(j).PAGES.at(
											k).ALLOC_FRAME_INDEX = -1;

									std::cout << "GIVING INDEX: " << _mem_index
											<< std::endl;
									seg->PAGES.at(_page_index).ALLOC_FRAME_INDEX =
											_mem_index;

									_should_continue = false;

									break;
								}
							}

							if (!_should_continue) {
								break;
							}
						}
					} else {
						std::cout << "GIVING INDEX: " << _mem_index
								<< std::endl;
						seg->PAGES.at(_page_index).ALLOC_FRAME_INDEX =
								_mem_index;
					}

					write_to_frame(process->PID, seg->ID,
							seg->PAGES.at(_page_index).ALLOC_FRAME_INDEX);
					std::cout << "WROTE AT INDEX: "
							<< seg->PAGES.at(_index).ALLOC_FRAME_INDEX
							<< std::endl;

				} else {
					write_to_frame(process->PID, seg->ID,
							seg->PAGES.at(_index).ALLOC_FRAME_INDEX);

					std::cout << "WROTE AT INDEX: "
							<< seg->PAGES.at(_index).ALLOC_FRAME_INDEX
							<< std::endl;
				}
			}
		}
	}
}

bool part_two::load_process(proc_t &proc) {
	return true;
}

bool part_two::unload_process(proc_t &proc) {

	for (int i = 0; i < proc.SEGMENTS.size(); i++) {
		segment_t seg = proc.SEGMENTS.at(i);
		for (int j = 0; j < seg.PAGES.size(); j++) {
			mem_page_t mem_page = seg.PAGES.at(j);
			if (mem_page.ALLOC_FRAME_INDEX != -1) {
				write_to_frame(EMPTY, EMPTY, mem_page.ALLOC_FRAME_INDEX);
			}
		}
	}

	return true;
}

bool part_two::request_free_frame(mem_page_t &page) {
	for (int i = 0; i < MAX_FRAMES; i++) {
		if (!(MAIN_MEMORY[i].ALLOCATED)) {
			std::cout << "RETURNING INDEX: " << i << std::endl;
			page.ALLOC_FRAME_INDEX = i;
			MAIN_MEMORY[i].ALLOCATED = true;
			return true;
		}
	}

	std::cout << "NOT RETURNING INDEX" << std::endl;

	return false;
}

void part_two::write_to_frame(char PID, char segment_ID, int frame_index) {
//	std::cout << "WRITING! PID: " << PID << " SEG ID: " << segment_ID
//			<< " FRAME INDEX: " << frame_index << std::endl;
	MAIN_MEMORY[frame_index].DATA[0] = PID;
	MAIN_MEMORY[frame_index].DATA[1] = segment_ID;

	print_memory_map();
	sleep(1);
}

//void part_two::print_memory_map() {
//	for (int i = 0; i < MAX_FRAMES; i++) {
//		std::cout << MAIN_MEMORY[i].DATA[0] << MAIN_MEMORY[i].DATA[1]
//				<< std::endl;
//	}
//}

int i = 0;
int _print_state = 0;
void part_two::print_memory_map() {
//	formatDetails();

	i = 0;
	for (; i <= MAX_FRAMES; i++) {
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
					} else {

						std::cout << "          ";
					}
				}
			}

			if ((i > 0) && (i % 40 == 0)) {
				_print_state += 1;
				std::cout << "\n";
				i = (i - 40);
			}

			continue;
		}
		case 1: {

			if (i % 5 == 0) {
				if (i % 10 == 0) {
					std::cout << "||";
				} else {
					std::cout << "++";
				}
			} else {
				std::cout << "--";
			}

			if ((i > 0) && (i % 40 == 0)) {
				_print_state += 1;
				std::cout << std::endl;
				i = (i - 40);
			}

			continue;
		}
		case 2: {
			std::cout << MAIN_MEMORY[i - 1].DATA[0]
					<< MAIN_MEMORY[i - 1].DATA[1];

			if ((i > 0) && (i % 40 == 0)) {
				_print_state = 0;
				std::cout << "" << std::endl;
			}

			continue;
		}
		}
	}

	std::cout
			<< "\n================================================================================"
			<< std::endl;
}

void part_two::print_backing_store() {
	//	formatDetails();

	i = 0;
	for (; i <= MAX_FRAMES; i++) {
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
					} else {

						std::cout << "          ";
					}
				}
			}

			if ((i > 0) && (i % 40 == 0)) {
				_print_state += 1;
				std::cout << "\n";
				i = (i - 40);
			}

			continue;
		}
		case 1: {

			if (i % 5 == 0) {
				if (i % 10 == 0) {
					std::cout << "||";
				} else {
					std::cout << "++";
				}
			} else {
				std::cout << "--";
			}

			if ((i > 0) && (i % 40 == 0)) {
				_print_state += 1;
				std::cout << std::endl;
				i = (i - 40);
			}

			continue;
		}
		case 2: {
			std::cout << BACKING_STORE[i - 1].DATA[0]
					<< BACKING_STORE[i - 1].DATA[1];

			if ((i > 0) && (i % 40 == 0)) {
				_print_state = 0;
				std::cout << "" << std::endl;
			}

			continue;
		}
		}
	}

	std::cout
			<< "\n================================================================================"
			<< std::endl;
}
