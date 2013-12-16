/*
 * memory.h
 *
 *  Created on: Dec 15, 2013
 *      Author: visitor15
 */

#ifndef MEMORY_H_
#define MEMORY_H_

/*
 *	STRUCT
 */
struct mem_frame_t {
	char DATA[2];
};

/*
 *	STRUCT
 */
struct mem_page_t {
	int ALLOC_FRAME_INDEX;

	mem_page_t() :
		ALLOC_FRAME_INDEX(-1) {};
};



#endif /* MEMORY_H_ */
