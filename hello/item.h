/*
 * item.h
 *
 *  Created on: Sep 10, 2017
 *      Author: OS1
 */

#ifndef ITEM_H_
#define ITEM_H_

#include "pcb.h"

struct Item{
	PCB* info;
	Item* next;
	Item* prev;
	Item(PCB* pcb){
		info = pcb;
		next = prev = 0;
	}
};


#endif /* ITEM_H_ */
