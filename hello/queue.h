/*
 * queue.h
 *
 *  Created on: Sep 10, 2017
 *      Author: OS1
 */

#ifndef QUEUE_H_
#define QUEUE_H_
#include "item.h"


class Queue{
public:
	void add(PCB*);
	PCB* remove();
	PCB* remove(int id);
	void print();
	int hasFirst();
	PCB* get(int id);
	Queue();
	virtual ~Queue();


private:
	Item* first;
	Item* last;

};



#endif /* QUEUE_H_ */
