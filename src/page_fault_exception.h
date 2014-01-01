/*
 * CS3242 Operating Systems
 * Fall 2013
 * Project 5: Swapping and Paging
 * Nick Champagne & John Mutabazi
 * Date: 11/22/2013
 * File: page_fault_exception.h
 */

#ifndef PAGE_FAULT_EXCEPTION_H_
#define PAGE_FAULT_EXCEPTION_H_

#include <exception>
#include <vector>
#include <stdarg.h>

/*
 * 		CLASS		-Custom exception designed to deliver the
 * 					index of the faulty memory page.
 */
class PageFaultException: public std::exception {
public:
//	int _index;
	std::vector<int> indices;
//	PageFaultException(int index) {
//		_index = index;
//
//		indices.resize(0);
//	}

	PageFaultException(std::vector<int> list) {
		indices.swap(list);
	}

	~PageFaultException() throw() {}


//	PageFaultException(const char *fmt, ...) {
//		_index = -1;
//
//	    va_list args;
//	    va_start(args, fmt);
//
//	    while (*fmt != '\0') {
//	        if (*fmt == 'i') {
//	            int i = va_arg(args, int);
//	            indices.push_back(i);
//	            std::cout << i << '\n';
//	        }
//	        ++fmt;
//	    }
//
//	    va_end(args);
//	}

	virtual const char* what() const throw () {
		return "Invalid memory access!";
	}

};

#endif /* PAGE_FAULT_EXCEPTION_H_ */
