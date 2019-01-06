/*
 * kerev.cpp
 *
 *  Created on: Jan 21, 2018
 *      Author: OS1
 */
#include "kerev.h"
#include "system.h"
#include <iostream.h>



KernelEv::KernelEv(IVTNo ivtno){
	number = ivtno;
	threadId = running->id;
	pcb = 0;

	IVTEntry* entry = IVTEntry::entries[number];

	if (entry) {
		entry->kerEv = this;
		entry->init();
	}
}



KernelEv::~KernelEv(){
	IVTEntry* entry = IVTEntry::entries[number];
	if (entry){
		entry->kerEv = 0;
		entry->restore();
	}
}




void KernelEv::signal(){

	if ( pcb ){
		pcb->state = ready;
		Scheduler::put(pcb);
		pcb = 0;
		dispatch();
	}

}

void KernelEv::wait(){

	if(threadId == running->id && pcb != 0){ 
		pcb = running;
		pcb->state = blocked;
		dispatch();
	}


}




