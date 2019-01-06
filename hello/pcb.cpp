/*
 * pcb.cpp
 *
 *  Created on: Sep 7, 2017
 *      Author: OS1
 */
#include <iostream.h>
#include "pcb.h"
#include "queue.h"
#include "SCHEDULE.H"
#define lock asm pushf;asm cli;
#define unlock asm popf;

#include "system.h"
#include <stdio.h>

extern void dispatch();


int PCB::lastId=2;
PCB* running = 0;
PCB* dummy = 0;
Queue* threads = 0;


void dummyJob(){
	while (1){}
}

PCB::PCB(){

	id = lastId++;
	threads->add(this);
	timeSlice = 0;
	state = ready;
	stack = 0;
	waitingQueue = 0;
}

PCB::PCB(int dummy) {
	id = 1;
	threads->add(this);
	stackSize = 2048;
	timeSlice = 1;
	state = blocked;
	waitingQueue = 0;



	stack = new unsigned[stackSize/sizeof(unsigned)];
//		stack[stackSize - 1] = FP_SEG(myThread);
//		stack[stackSize - 2] = FP_OFF(myThread);
		stack[stackSize/sizeof(unsigned) - 5] = 0x200;
		stack[stackSize/sizeof(unsigned) - 6] = FP_SEG(dummyJob);//segment
		stack[stackSize/sizeof(unsigned) - 7] = FP_OFF(dummyJob);//offset

		ss = FP_SEG(stack + stackSize/sizeof(unsigned) - 16);
		sp = FP_OFF(stack + stackSize/sizeof(unsigned) - 16);
		bp = sp;




}

PCB::PCB(StackSize ssize, Time ts, Thread* mt) {
	id = lastId++;
	threads->add(this);
	myThread = mt;
	stackSize = ssize;
	timeSlice = ts;
	state = created;
	waitingQueue = new Queue();


	stack = new unsigned[stackSize/sizeof(unsigned)];
	stack[stackSize/sizeof(unsigned) - 1] = FP_SEG(myThread);
	stack[stackSize/sizeof(unsigned) - 2] = FP_OFF(myThread);
	stack[stackSize/sizeof(unsigned) - 5] = 0x200;
	stack[stackSize/sizeof(unsigned) - 6] = FP_SEG(PCB::wrapper);//segment
	stack[stackSize/sizeof(unsigned) - 7] = FP_OFF(PCB::wrapper);//offset

	ss = FP_SEG(stack + stackSize/sizeof(unsigned) - 16);
	sp = FP_OFF(stack + stackSize/sizeof(unsigned) - 16);
	bp = sp;//bp je na pocetku isto sto i sp


}

PCB::~PCB(){

	if (stack !=0) delete stack;
	if (waitingQueue != 0) delete waitingQueue;
	//PCB* tmp = threads->remove(this->id);
	//sredi brisanje delete tmp
	//tmp = 0;


}

int PCB::getId() {
	return id;
}

int PCB::getRunningId() {
	return running->id;
}

Thread* PCB::getThreadById(int id){
	return threads->get(id)->myThread;
}

void PCB::start() {
	if (state == created) {
		state = ready;
		Scheduler::put(this);
	}
}

void PCB::wrapper() {
	PCB* tmp;
	running->myThread->run();

	lock
	while(running->waitingQueue->hasFirst()==1){
		tmp = running->waitingQueue->remove();
		tmp->state = ready;
		Scheduler::put(tmp);
	}
	running->state = done;
	unlock
	dispatch();
}

void PCB::waitToComplete(){
	if (this->state != done && this != running){
		running->state = blocked;
		this->waitingQueue->add(running);
		dispatch();
	}
}

void PCB::sleep(Time timeToSleep){
	if (timeToSleep <= 0) return;
	running->tts = timeToSleep;
	running->state = blocked;
	SQueue::sleepingQueue->add(running);
}




