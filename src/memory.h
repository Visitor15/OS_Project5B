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
	bool ALLOCATED;

	mem_frame_t() :
		ALLOCATED(false) {
		DATA[0] = EMPTY;
		DATA[1] = EMPTY;
	}
};

/*
 *	STRUCT
 */
struct mem_page_t {
	char DATA[2];
	int ALLOC_FRAME_INDEX;

	mem_page_t() :
		ALLOC_FRAME_INDEX(-1) {
		DATA[0] = EMPTY;
		DATA[1] = EMPTY;
	};

	void clear_page() {
		ALLOC_FRAME_INDEX = -1;
		DATA[0] = EMPTY;
		DATA[1] = EMPTY;
	}
};



#endif /* MEMORY_H_ */
