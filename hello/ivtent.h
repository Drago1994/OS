/*
 * ivtent.h
 *
 *  Created on: Jan 21, 2018
 *      Author: OS1
 */

#ifndef IVTENT_H_
#define IVTENT_H_


#include <dos.h>
#include <stdio.h>
#include "system.h"
#include "kerev.h"

class KernelEv;



class IVTEntry {

public:

	static IVTEntry* entries[]; //

	IVTNo number;
	void interrupt (*routine)(...);
	void interrupt (*oldRoutine)(...);
	int doOld;

	int ready;

	KernelEv* kerEv;

	IVTEntry(IVTNo ivtno, void interrupt (*ivtroutine)(...),int old);

	void signal();

	void init();

	void restore();

};




#define PREPAREENTRY(IVTNO,OLD)\
	void interrupt intr##IVTNO(...){\
		IVTEntry::entries[IVTNO]->signal();\
	}\
	IVTEntry entryNo##IVTNO(IVTNO,intr##IVTNO,OLD);\



#endif /* IVTENT_H_ */
