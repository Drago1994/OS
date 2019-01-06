#ifndef SQUEUE_H
#define SQUEUE_H


#include "item.h"

typedef int ID;



class SQueue{
public:
	
	static SQueue* sleepingQueue;

	void add(PCB*);
	PCB* remove();
	PCB* remove(ID id);
	void print();

	SQueue();
	virtual ~SQueue();

    void timeUpdate();
    int readyToLeave();


private:
	Item* first;
	Item* last;

};

#endif
