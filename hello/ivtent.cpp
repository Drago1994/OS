/*
 * ivtent.cpp
 *
 *  Created on: Jan 21, 2018
 *      Author: OS1
 */

#include <ivtent.h>

IVTEntry* IVTEntry::entries[256] = {0};

void IVTEntry::signal(){
		if (oldRoutine && doOld){
			oldRoutine();
		}
		if (!kerEv) return;
		kerEv->signal();

	}

IVTEntry::IVTEntry(IVTNo ivtno, void interrupt (*ivtroutine)(...),int old){
		number = ivtno;
		routine = ivtroutine;
		doOld = old;
		ready = 0;
		kerEv = 0;

		entries[ivtno]= this;
	}


void IVTEntry::init(){
	if (ready==0){
	oldRoutine = getvect(number);
	setvect(number, routine);
	ready = 1;

	}


}

void IVTEntry::restore(){
		setvect(number, oldRoutine);
		oldRoutine = 0;
		ready = 0;

	}
