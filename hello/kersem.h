/*
 * kersem.h
 *
 *  Created on: Sep 12, 2017
 *      Author: OS1
 */

#ifndef KERSEM_H_
#define KERSEM_H_

#include "queue.h"
#include "semaphor.h"
//#include "system.h"

#define lock asm pushf;asm cli;
#define unlock asm popf;

class KernelSem {
public:

	KernelSem (int init=1);

	virtual ~KernelSem ();

	virtual int wait (int toBlock);

	virtual void signal();

	int val (); // Returns the current value of the semaphore

	Queue* blockedPCB;

	friend void interrupt timer();

	int value;

};



#endif /* KERSEM_H_ */
