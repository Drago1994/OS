/*
 * thread.cpp
 *
 *  Created on: Sep 12, 2017
 *      Author: OS1
 */

#include "thread.h"
//#include "pcb.h"
#include "queue.h"
#include <iostream.h>

#define lock asm pushf; asm cli;
#define unlock asm popf;

extern int swLocked;
extern int switchRequested;

void Thread::start(){
	swLocked = 1;
	myPCB->start();
	swLocked=0;
	if (switchRequested) dispatch();
}

void Thread::waitToComplete(){
	swLocked = 1;
	myPCB->waitToComplete();
	swLocked=0;
	if (switchRequested) dispatch();
}

Thread::~Thread() {
	swLocked = 1;
    delete myPCB;
	swLocked=0;
	if (switchRequested) dispatch();
}

//ID Thread::getId(){
//	swLocked = 1;
//	ID tmp = myPCB->getId();
//	swLocked=0;
//	if (switchRequested) dispatch();
//	return tmp;
//}
//
//ID Thread::getRunningId(){
//	swLocked = 1;
//	ID tmp = running->getId();
//	swLocked=0;
//	if (switchRequested) dispatch();
//	return tmp;
//}
//
//Thread * Thread::getThreadById(ID id){
//	swLocked = 1;
//	Thread* tmp = PCB::getThreadById(id);
//	swLocked=0;
//	if (switchRequested) dispatch();
//	return tmp;
//}

Thread::Thread(StackSize ss,Time ts) {
	lock
	swLocked = 1;
	myPCB = new PCB(ss, ts, this);
	swLocked = 0;

	if (switchRequested) dispatch();
	unlock
}

void Thread::sleep(Time timeToSleep){
	lock
	swLocked = 1;
    PCB::sleep(timeToSleep);
	swLocked=0;
	unlock
	dispatch();

}




