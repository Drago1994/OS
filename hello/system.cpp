/*
 * system.cpp
 *
 *  Created on: Sep 11, 2017
 *      Author: OS1
 */

#include "system.h"
#include <iostream.h>
#include "queue.h"



int counter = 0;
unsigned oldTimerSEGment;
unsigned oldTimerOFFset;
unsigned tsp,tss,tbp;

int swLocked = 0;
int switchRequested = 0;

//void tick();

void dispatch(){
	lock
	switchRequested = 1;
	timer();
	unlock
}

void interrupt timer() {
	PCB* tmp;



	if (switchRequested == 0 ) {

		SQueue::sleepingQueue->timeUpdate();

		while(SQueue::sleepingQueue->readyToLeave()==1) {

			tmp = SQueue::sleepingQueue->remove();
			//tmp->blockedOn->value++;
			//tmp->blockedOn->blockedPCB->remove(tmp->id);
			//tmp->blockedOn = 0;
			tmp->state = ready;
			Scheduler::put(tmp);
		}

	}


	if (switchRequested == 0 && counter != -1 ) {
		counter--;
	}
	if (counter == 0 || switchRequested == 1) {

		if (swLocked == 1){
			switchRequested = 1;
			return;
		}
		switchRequested = 0;
		asm {
				mov tsp, sp
				mov tss, ss
				mov tbp, bp
		}
		running->sp = tsp;
		running->ss = tss;
		running->bp = tbp;

		if (running->state == ready){
			Scheduler::put(running);
		}
		running = Scheduler::get();
		if (running == 0){
			running = dummy;
		}

		tsp = running->sp;
		tss = running->ss;
		tbp = running->bp;

		counter = running->timeSlice;

		if (counter == 0) counter = -1;
		asm {
			mov sp, tsp
			mov ss, tss
			mov bp, tbp
		}
	}
	if (switchRequested == 0){

		tick();
		asm int 60h;
	}

}








//void inic(){
//
//	asm{
//		cli
//		push es
//		push ax
//
//		mov ax,0   //  ; inicijalizuje rutinu za tajmer
//		mov es,ax
//
//		mov ax, word ptr es:0022h //; pamti staru rutinu
//		mov word ptr oldTimerSEGment, ax
//		mov ax, word ptr es:0020h
//		mov word ptr oldTimerOFFset, ax
//
//		mov word ptr es:0022h, seg timer	 //postavlja
//		mov word ptr es:0020h, offset timer //novu rutinu
//
//		mov ax, oldTimerSEGment	 //	postavlja staru rutinu
//		mov word ptr es:0182h, ax //; na int 60h
//		mov ax, oldTimerOFFset
//		mov word ptr es:0180h, ax
//
//		pop ax
//		pop es
//		sti
//	}
//
//	running = new PCB();
//	dummy = new PCB(1);
//	threads = new Queue();
//	//dispatch();
//	//timer();
//}
//
//void restore() {
//
//	asm {
//			cli
//			push es
//			push ax
//
//			mov ax,0
//			mov es,ax
//
//
//			mov ax, word ptr oldTimerSEGment
//			mov word ptr es:0022h, ax
//			mov ax, word ptr oldTimerOFFset
//			mov word ptr es:0020h, ax
//
//			pop ax
//			pop es
//			sti
//	}
//
//
//
//	delete running;
//	delete dummy;
//	delete threads;
//	delete SQueue::sleepingQueue;
//
//}



void inic(){
	running = new PCB();
	dummy = new PCB(1);
	threads = new Queue();

	asm{
		cli
		push es
		push ax

		mov ax,0   //  ; inicijalizuje rutinu za tajmer
		mov es,ax

		mov ax, word ptr es:0022h //; pamti staru rutinu
		mov word ptr oldTimerSEGment, ax
		mov ax, word ptr es:0020h
		mov word ptr oldTimerOFFset, ax

		mov word ptr es:0022h, seg timer	 //postavlja
		mov word ptr es:0020h, offset timer //novu rutinu

		mov ax, oldTimerSEGment	 //	postavlja staru rutinu
		mov word ptr es:0182h, ax //; na int 60h
		mov ax, oldTimerOFFset
		mov word ptr es:0180h, ax

		pop ax
		pop es
		sti
	}

}

void restore(){
	asm {
		cli
		push es
		push ax

		mov ax,0
		mov es,ax


		mov ax, word ptr oldTimerSEGment
		mov word ptr es:0022h, ax
		mov ax, word ptr oldTimerOFFset
		mov word ptr es:0020h, ax

		pop ax
		pop es
		sti
	}

	delete running;
	delete dummy;
	delete threads;
    delete SQueue::sleepingQueue;

}
