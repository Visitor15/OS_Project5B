/*
 * parttwo.h
 *
 *  Created on: Dec 10, 2013
 *      Author: visitor15
 */

#ifndef PARTTWO_H_
#define PARTTWO_H_

#define MIN_BURST				10
#define MAX_BURST				200
#define MIN_MEMORY_PER_PROC 	10
#define MAX_MEMORY_PER_PROC 	250
#define MAX_MEMORY 				140
#define MAX_BLOCK_PROC_RATIO 	0.5
#define PRINT_INTERVAL 			500
#define MAX_QUANTA				50000
#define SLEEP_LENGTH			250
#define ENABLE_COMPACTION		1

class parttwo {
public:
	parttwo();
	virtual ~parttwo();
};

#endif /* PARTTWO_H_ */
