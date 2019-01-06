/*
 * queue.cpp
 *
 *  Created on: Sep 10, 2017
 *      Author: OS1
 */
#include "queue.h"
#include <iostream.h>

Queue::Queue() {
	first = 0;
	last = 0;
}

Queue::~Queue() {
	while(first != 0) {
		last = first;
		first = first->next;
		delete last;
	}
	last = 0;
}

void Queue::add(PCB* pcb) {
	if (pcb == 0) return;
	if (first == 0){
		 first = last = new Item(pcb);
		 return;
	 }
	 Item* tmp = new Item(pcb);
	 last->next = tmp;
	 tmp->prev = last;
	 last = last->next;

	 return;
}

PCB* Queue::remove() {
	if (first == 0) return 0;

	Item* tmp = first;
	first = first->next;
	tmp->next = 0;
	if (first != 0) first->prev = 0;


	PCB* retPCB = tmp->info;
	tmp->info=0;
	delete tmp;

	return retPCB;
}

PCB*  Queue::get(int id){
	Item* tmp = first;
		while (tmp != 0) {
			if (tmp->info->id == id) return tmp->info;
			tmp=tmp->next;
		}
		return 0;

}

PCB* Queue::remove(int id) {
	PCB* retPCB;
	if (first == 0) return 0;
	Item* tmp = first;
	while (tmp != 0) {
		if (tmp->info->id == id) break;
		tmp=tmp->next;
	}
	if (tmp==0) return 0;
	else {
		if (tmp == first){
			first = first->next;
			if (first != 0)
				first->prev = 0;
			else last = 0;
			tmp->next = 0;
			retPCB = tmp->info;
			tmp->info = 0;
			delete tmp;
			return retPCB;
		}
		if (tmp == last){
			last = last->prev;
			if (last != 0)
				last->next = 0;
			else first = 0;
			tmp->prev=0;
			retPCB=tmp->info;
			tmp->info=0;
			delete tmp;
			return retPCB;
		}
		tmp->prev->next = tmp->next;
		tmp->next->prev = tmp->prev;
		tmp->next = 0;
		tmp->prev = 0;
		retPCB = tmp->info;
		tmp->info=0;
		delete tmp;
		return retPCB;
	}
}

int Queue::hasFirst() {
	if (first != 0) return 1;
	else return 0;
}

void Queue::print() {
	Item* tmp = first;
	while (tmp != 0) {
		cout << tmp->info->tts << " ";
		tmp = tmp->next;
	}
}


