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

#define MAX_PROCESSES			60
#define PROCESS_COUNT			60
#define MIN_BURST				10
#define MAX_BURST				200
#define MIN_MEMORY_PER_PROC 	10
#define MAX_MEMORY_PER_PROC 	250
#define MAX_MEMORY 				1040
#define MAX_BLOCK_PROC_RATIO 	0.5
#define PRINT_INTERVAL 			500
#define MAX_QUANTA				50000
#define SLEEP_LENGTH			250
#define ENABLE_COMPACTION		1

static const char			EMPTY			= ' ';
static const char 			KERNEL_PROC_ID 	= '@';
static const unsigned int 	DEF_KERNEL_SIZE = 120;


#endif /* GLOBAL_H_ */
