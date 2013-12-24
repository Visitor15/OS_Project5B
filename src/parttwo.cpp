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

	process::GENERATE_PROCS(RUNNING_QUEUE, MAX_PROCESSES_P2);
	for (int i = 0; i < MAX_PROCESSES_P2; i++) {
		process::CREATE_PROC_SEGMENTS(RUNNING_QUEUE.at(i));
	}
//	std::cout << "LOLLIPOP" << std::endl;
	/*
	 * MAIN LOOP
	 */
	do {
//		sleep(1);
		execute_cycle();
//		print_memory_map();

	} while (has_cycle());

	std::cout << "\n\nFINISHED!\n\n" << std::endl;
}

bool part_two::has_cycle() {
	return (RUNNING_QUEUE.size() > 0);
}

void part_two::init_memory() {

}

void part_two::execute_cycle() {
	bool _should_continue = true;
	int _index;
	proc_t* process;
	segment_t* seg;

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

		if (RUNNING_QUEUE.at(_index).PID == KERNEL_PROC_ID) {
			// We'll just recursively call
			execute_cycle();
		}

		// Touching random process
		process = &RUNNING_QUEUE.at(_index);

//	else if (READY_QUEUE.size() > 0) {
//		_index = (rand() % READY_QUEUE.size());
//
//		// Touching random process
//		process = &READY_QUEUE.at(_index);
//	}
		// Getting index for subroutine segment
		_index = (rand() % (process->SEGMENTS.size() - SEGMENT_ROUTINE))
				+ SEGMENT_ROUTINE;
//	do {
		std::cout << " HIT HIT HIT " << std::endl;

		for (int i = 0; i < SEGMENT_ROUTINE; i++) {
			seg = &process->SEGMENTS.at(i);
			try {
				seg->touch();

				// Touching random subroutine segment
				seg = &process->SEGMENTS.at(_index);
				seg->touch();
				seg->IS_LOADED = true;
			} catch (PageFaultException &e) {
				std::cout << "HIT FOR: " << e._index << " ON PROC: "
						<< process->PID << std::endl;
				if (!request_free_frame(seg->PAGES[e._index])) {
//			std::cout << " 'MERICA!" << std::endl;
					/* If we couldn't get a free frame, we assume the main memory
					 * is full so we default to removing a random proc's registered
					 * memory frame and use that one.
					 */
					int _index = 0;
//			do {
					std::cout << " LALA : " << RUNNING_QUEUE.size()
							<< std::endl;
					for (int num = 0; num < RUNNING_QUEUE.size(); num++) {
//					std::cout << " JINKA: " << num << " PROC: "
//							<< RUNNING_QUEUE.at(num).PID << std::endl;
						if (RUNNING_QUEUE.at(num).PID != KERNEL_PROC_ID) {
							_index = num;
							proc_t * _proc = &RUNNING_QUEUE.at(num);

							std::cout << "PROC: " << _proc->PID << std::endl;

							for (int k = 0; k < _proc->SEGMENTS.size(); k++) {
//						std::cout << "SEG: " << _proc->SEGMENTS.at(k).ID
//								<< std::endl;
								if (_proc->SEGMENTS.at(k).IS_LOADED) {
									segment_t * _segment = &_proc->SEGMENTS.at(
											k);
									std::cout << " DOOKIE : " << _segment->ID
											<< " PAGE COUNT: "
											<< _segment->PAGE_COUNT
											<< std::endl;
									for (int j = 0; j < _segment->PAGE_COUNT;
											j++) {
										std::cout << "THINGS: "
												<< _segment->PAGES.at(j).ALLOC_FRAME_INDEX
												<< std::endl;
										if (_segment->PAGES.at(j).ALLOC_FRAME_INDEX
												!= -1) {
											seg->PAGES.at(e._index).ALLOC_FRAME_INDEX =
													_segment->PAGES.at(j).ALLOC_FRAME_INDEX;

											_segment->PAGES.at(j).ALLOC_FRAME_INDEX =
													-1;

											std::cout << " WRITING PROC: "
													<< process->PID
													<< " AT INDEX: "
													<< seg->PAGES.at(e._index).ALLOC_FRAME_INDEX
													<< std::endl;
											write_to_frame(process->PID,
													seg->ID,
													seg->PAGES.at(e._index).ALLOC_FRAME_INDEX);

											_segment->PAGES.at(j).clear_page();

											_should_continue = false;

											// Checking if any pages are currently loaded for the segment.
											// Setting param.
											bool is_loaded = false;
											for (int i = 0;
													i < _segment->PAGE_COUNT;
													i++) {
												if (_segment->PAGES.at(i).ALLOC_FRAME_INDEX
														!= -1) {
//												std::cout
//														<< "SETTING TO TRUE FOR INDEX: "
//														<< _segment->PAGES.at(i).ALLOC_FRAME_INDEX
//														<< std::endl;
													is_loaded = true;
												} else {
													is_loaded = false;
												}
											}
											_segment->IS_LOADED = is_loaded;

											for (int i = 0;
													i < _proc->SEGMENTS.size();
													i++) {

												for (int k = 0;
														k
																< _proc->SEGMENTS.at(
																		i).PAGE_COUNT;
														k++) {
													if (_proc->SEGMENTS.at(i).PAGES.at(
															k).ALLOC_FRAME_INDEX
															!= -1) {
//													std::cout << "HIT BITCHES"
//															<< std::endl;
														is_loaded = true;
													}

												}

											}

											if (!is_loaded) {
												READY_QUEUE.push_back(*_proc);
												std::cout
														<< "ERASING AT INDEX: "
														<< num << " PROC: "
														<< RUNNING_QUEUE.at(num).PID
														<< " RUNNING SIZE: "
														<< RUNNING_QUEUE.size()
														<< std::endl;

												RUNNING_QUEUE.erase(
														RUNNING_QUEUE.begin()
																+ num);

												std::cout
														<< "AFTER ERASE - SIZE: "
														<< RUNNING_QUEUE.size()
														<< std::endl;

											}

											std::cout << "BREAKING LOOP!"
													<< std::endl;
											_should_continue = false;
											break;

//										execute_cycle();

										}
									}
								}

								if (!_should_continue) {
									break;
								}
							}
							if (!_should_continue) {
								break;
							}
						}
						if (!_should_continue) {
							break;
						}
					}

//			} while (_should_continue);
				} else {
					write_to_frame(process->PID, seg->ID,
							seg->PAGES.at(e._index).ALLOC_FRAME_INDEX);

					std::cout << "WROTE AT INDEX: "
							<< seg->PAGES.at(e._index).ALLOC_FRAME_INDEX
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

	return false;
}

void part_two::write_to_frame(char PID, char segment_ID, int frame_index) {
//	std::cout << "WRITING! PID: " << PID << " SEG ID: " << segment_ID
//			<< " FRAME INDEX: " << frame_index << std::endl;
	MAIN_MEMORY[frame_index].DATA[0] = PID;
	MAIN_MEMORY[frame_index].DATA[1] = segment_ID;
}

void part_two::print_memory_map() {
	for (int i = 0; i < MAX_FRAMES; i++) {
		std::cout << MAIN_MEMORY[i].DATA[0] << MAIN_MEMORY[i].DATA[1]
				<< std::endl;
	}
}
