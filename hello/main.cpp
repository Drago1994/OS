/*
 * main.cpp
 *
 *  Created on: Sep 12, 2017
 *      Author: OS1
 */
#include "pcb.h"
//#include "squeue.h"
#include "queue.h"
#include <iostream.h>
#include "ivtent.h"

extern void inic();
extern void restore();

#define lock asm pushf;asm cli;
#define unlock asm popf;


int userMain(int argc, char**argv);



int main(int argc, char* argv[])
{

	inic();
	int a = userMain(argc, argv);
    restore();

 for (int i = 0; i < 256; i++)
  if (IVTEntry::entries[i] != 0)
   delete IVTEntry::entries[i];

    return a;
}

