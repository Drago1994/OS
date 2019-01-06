/*
 * pcb.h
 *
 *  Created on: Sep 7, 2017
 *      Author: OS1
 */

#ifndef PCB_H_
#define PCB_H_

#include <dos.h>

#include "thread.h"



class Thread;
class Queue;
class KernelSem;

enum enumState {blocked=0, done=1, ready=2, created=3};

class PCB{
public:
	int id;
	enumState state;

	unsigned sp;	//stack pointer
	unsigned ss;	//stack segment
	unsigned bp;	//base pointer
	int tts;	//time to sleep
	int timeSlice; // time til dispatch
	KernelSem* blockedOn;



	static void wrapper();
	static int getRunningId();
	static Thread* getThreadById(int id);
	static void sleep(Time timeToSleep);

	PCB();
	PCB(int dummy);
	PCB(StackSize stackSize, Time tts, Thread* myThread);
	PCB::~PCB();
	void start();
	void waitToComplete();
	int getId();
	Queue* waitingQueue; // queue for all threads that have to wait for this to finish
	unsigned* stack;
	StackSize stackSize;
	Thread* myThread;


private:
	static int lastId;


};


extern PCB* running;
extern PCB* dummy;
extern  Queue* threads; // all threads

#endif /* PCB_H_ */
