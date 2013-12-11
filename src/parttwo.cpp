/*
 * parttwo.cpp
 *
 *  Created on: Dec 10, 2013
 *      Author: visitor15
 */

#include "parttwo.h"

int main() {

	parttwo &self;
	self.show_menu();

	return EXIT_SUCCESS;
}

void parttwo::show_menu() {
	int _choice = -1;
	std::cout << "=====================================" << std::endl;
	std::cout << "Project 5" << std::endl;
	std::cout << "=====================================\n" << std::endl;
	std::cout << "\t1. Part A" << std::endl;
	std::cout << "\t2. Part B" << std::endl;
	std::cout << "\n\nOption: ";
	std::cin >> _choice;

	switch(_choice) {
	case 1: {
		show_menu_a();
		break;
	}
	case 2: {
		show_menu_b();
		break;
	}
	default: {
		std::cout << "ERROR: Wrong option chosen\n\n" << std::endl;
		show_menu();
	}
	}
}

void parttwo::show_menu_a() {
	int _choice = -1;

	std::cout << "\n\n\n=====================================" << std::endl;
	std::cout << "Part A" << std::endl;
	std::cout << "=====================================\n" << std::endl;
	std::cout << "\t1. First-fit" << std::endl;
	std::cout << "\t2. Best-fit" << std::endl;
	std::cout << "\t3. Worst-fit" << std::endl;
	std::cout << "\n\nOption: ";
	std::cin >> _choice;

	switch(_choice) {
	case 1: {
		break;
	}
	case 2: {
		break;
	}
	case 3: {
		break;
	}
	default: {
		std::cout << "ERROR: Wrong option chosen\n\n" << std::endl;
		show_menu_a();
	}
	}
}

void parttwo::show_menu_b() {
	int _choice = -1;

	std::cout << "\n\n\n=====================================" << std::endl;
	std::cout << "Part A" << std::endl;
	std::cout << "=====================================\n" << std::endl;
	std::cout << "\t1. FIFO" << std::endl;
	std::cout << "\t2. LRU" << std::endl;
	std::cout << "\t3. Second Chance" << std::endl;
	std::cout << "\n\nOption: ";
	std::cin >> _choice;

	switch(_choice) {
	case 1: {
		break;
	}
	case 2: {
		break;
	}
	case 3: {
		break;
	}
	default: {
		std::cout << "ERROR: Wrong option chosen\n\n" << std::endl;
		show_menu_b();
	}
	}
}

void parttwo::start() {

}

