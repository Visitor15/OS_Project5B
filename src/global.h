/*
 * global.h
 *
 *  Created on: Dec 10, 2013
 *      Author: visitor15
 */

#ifndef GLOBAL_H_
#define GLOBAL_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <cstdio>
#include <unistd.h>
#include <string.h>
#include <sstream>

/*
 *	PART ONE VARIABLES
 */
#define MAX_PROCESSES_P1		200
#define PROCESS_COUNT_P1		60
#define MIN_BURST				5
#define MAX_BURST				15
#define MIN_MEMORY_PER_PROC 	10
#define MAX_MEMORY_PER_PROC 	250
#define MAX_MEMORY 				1040
#define MAX_BLOCK_PROC_RATIO 	0.5
#define PRINT_INTERVAL 			500
#define MAX_QUANTA				50000
#define SLEEP_LENGTH_P1			250
#define ENABLE_COMPACTION		1
/*
 *	END PART ONE
 */

/*
 *	PART TWO VARIABLES
 */
#define MAX_PROCESSES_P2		52
#define PROCESS_COUNT_P2		23
#define MIN_DEATH_INTERVAL		20
#define MAX_DEATH_INTERVAL		300
#define MAX_FRAMES				280
#define MAX_PAGES				720
#define SHIFT_INTERVAL			10
#define PRINT_INTERVAL			500
#define MAX_QUANTA				50000
#define SLEEP_LENGTH_P2			2500
/*
 *	END PART TWO
 */

static const char			EMPTY			= ' ';
static const char 			KERNEL_PROC_ID 	= '@';
static const unsigned int 	DEF_KERNEL_SIZE = 120;
static const unsigned int	SEGMENT_CODE	= 0;
static const unsigned int	SEGMENT_STACK	= 1;
static const unsigned int	SEGMENT_HEAP	= 2;
static const unsigned int	SEGMENT_ROUTINE	= 3;

enum START_VALUE {
	FIRST_FIT		= 0,
	BEST_FIT		= 1,
	WORST_FIT		= 2,
	FIFO			= 3,
	LRU				= 4,
	SECOND_CHANCE	= 5
};



#endif /* GLOBAL_H_ */
