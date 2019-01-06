/*
 * kerev.h
 *
 *  Created on: Jan 21, 2018
 *      Author: OS1
 */

#ifndef KEREV_H_
#define KEREV_H_

#include "pcb.h"
#include "event.h"
#include "ivtent.h"


class KernelEv{
public:

	int threadId;

	IVTNo number;

	PCB* pcb;


	KernelEv(IVTNo ivtno);
	~KernelEv();

	void wait();
	void signal();



};


#endif /* KEREV_H_ */
