/*
 * kersem.cpp
 *
 *  Created on: Sep 12, 2017
 *      Author: OS1
 */
#include "kersem.h"
//#include "squeue.h"
#include "SCHEDULE.H"
#include <iostream.h>



KernelSem::KernelSem(int init){
	value = init;
	blockedPCB = new Queue();
}

KernelSem::~KernelSem(){
	delete blockedPCB;
}

int KernelSem::val() {
	return value;
}

int KernelSem::wait(int toBlock) {
	lock
	if ((toBlock == 0) && (value <= 0)) {
		unlock
		return -1;
	}
	if (--value < 0) {

		//running->tts = maxTimeToWait;
		running->state = blocked;
		running->blockedOn = this;
		this->blockedPCB->add(running);
		//if (running->tts > 0)
			//SQueue::sleepingQueue->add(running);
		unlock
		dispatch();
		return 1;
	}
	unlock
	return 0;
}

void KernelSem::signal(){
	PCB* pcb;
	lock
	if (++value <= 0){
		pcb = blockedPCB->remove();
		//SQueue::sleepingQueue->remove(pcb->id);
		pcb->state = ready;
		pcb->blockedOn = 0;
		//pcb->tts = 0;
		Scheduler::put(pcb);
	}
	unlock
}




