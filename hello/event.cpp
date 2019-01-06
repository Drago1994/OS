/*
 * event.cpp
 *
 *  Created on: Jan 22, 2018
 *      Author: OS1
 */

#include "event.h"
#include "kerev.h"
#include "system.h"
#include <stdio.h>




Event::Event(IVTNo ivtno){

	lock
	myImpl = new KernelEv(ivtno);
	unlock
	if (switchRequested) dispatch();
}

Event::~Event(){
	lock
	delete myImpl;
	unlock
	if (switchRequested) dispatch();
}

void Event::wait(){
	lock
	myImpl->wait();
	unlock
	if (switchRequested) dispatch();
}

void Event::signal(){
	lock
	myImpl->signal();
	unlock
	if (switchRequested) dispatch();
}
