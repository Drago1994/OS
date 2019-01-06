/*
 * semaphor.cpp
 *
 *  Created on: Sep 12, 2017
 *      Author: OS1
 */
#include "semaphor.h"
#include "kersem.h"
//#include "system.h"
#include <iostream.h>

#define lock asm pushf;asm cli;
#define unlock asm popf;

extern int swLocked;
extern int switchRequested;

Semaphore::Semaphore(int init) {
	lock
	myImpl = new KernelSem(init);
	unlock
	if (switchRequested) dispatch();
}

Semaphore::~Semaphore() {
	lock
	delete myImpl;
	unlock
	if (switchRequested) dispatch();
}

int Semaphore::val() const {
	lock
	int ret = myImpl->val();
	unlock
	if (switchRequested) dispatch();
	return ret;
}

int Semaphore::wait(int toBlock) {
	lock
	int ret = myImpl->wait(toBlock);
	unlock
	if (switchRequested) dispatch();
	return ret;
}

void Semaphore::signal() {
	lock
	myImpl->signal();
	unlock
	if (switchRequested) dispatch();
}



