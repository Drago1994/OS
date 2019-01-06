#include "squeue.h"

#include <iostream.h>

SQueue* SQueue::sleepingQueue = new SQueue();

SQueue::SQueue(){
	first = 0;
	last = 0;
}

SQueue::~SQueue(){
	while(first != 0){
		last = first;
		first = first->next;
		delete last;
	}
	last = 0;
}


void SQueue::add(PCB* pcb){
	Item* tmp;
	if (first == 0){
		tmp = new Item(pcb);
		first = tmp;
		last = tmp;
		return;
	}
	tmp = first;
	while(tmp != 0){
		if (pcb->tts >= tmp->info->tts){
			pcb->tts = pcb->tts - tmp->info->tts;
			tmp = tmp->next;
		}
		else break;
	}
	if (tmp != 0){
		Item* newItem = new Item(pcb);
		newItem->next = tmp;
		tmp->prev->next = newItem;
		newItem->prev = tmp->prev;
		tmp->prev = newItem;
		if (tmp == first) first = newItem;
		tmp->info->tts = tmp->info->tts - pcb->tts;
		return;
	}
	else{
		Item* newItem = new Item(pcb);
		last->next = newItem;
		newItem->prev = last;
		last = newItem;
		return;
	}

}

void SQueue::print(){
	Item* tmp = first;
	while (tmp != 0){
		cout << tmp->info->tts << " ";
		tmp = tmp->next;
	}
}

PCB* SQueue::remove(ID id){
	if (first == 0) return 0;
	Item* tmp = first;
	PCB* retPCB;
	while(tmp != 0){
		if (tmp->info->id == id) break;
		tmp=tmp->next;
	}
	if (tmp==0) return 0;
	else{
		if (tmp == first){
			first = first->next;
			first->info->tts = first->info->tts + tmp->info->tts;
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

		tmp->next->info->tts = tmp->next->info->tts + tmp->info->tts;
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

PCB* SQueue::remove() {
	if (first == 0) return 0;

	Item* tmp = first;
	first = first->next;
	tmp->next = 0;
	if (first != 0) {
		first->prev = 0;
		first->info->tts = first->info->tts + tmp->info->tts;
	}



	PCB* retPCB = tmp->info;
	tmp->info=0;
	delete tmp;

	return retPCB;
}

void SQueue::timeUpdate(){
	if (first == 0) return;
	if (first->info->tts > 0)
		first->info->tts = first->info->tts - 1;
}

int SQueue::readyToLeave() {
	if (first == 0) return 0;
	if (first->info->tts <= 0) return 1;
	return 0;
}
