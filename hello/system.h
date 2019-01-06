/*
 * system.h
 *
 *  Created on: Sep 11, 2017
 *      Author: OS1
 */

#ifndef SYSTEM_H_
#define SYSTEM_H_

#include "pcb.h"
#include "queue.h"

#include "squeue.h"
#include "SCHEDULE.H"
#include "kersem.h"

#include "ivtent.h"


#define lock asm pushf;asm cli;
#define unlock asm popf;

extern int switchRequested;
extern int swLocked;

void interrupt timer();
void inic();
void restore();
void dispatch();

void tick();


#endif /* SYSTEM_H_ */
