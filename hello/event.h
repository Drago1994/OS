/*
 * event.h
 *
 *  Created on: Jan 21, 2018
 *      Author: OS1
 */

#ifndef EVENT_H_
#define EVENT_H_
#include "ivtno.h"
#include "ivtent.h"

class KernelEv;

class Event {

public:

 Event (IVTNo ivtNo);
 ~Event ();
 void wait ();

protected:

 friend class KernelEv;
 void signal(); // can call KernelEv

private:

 KernelEv* myImpl;
};


#endif /* EVENT_H_ */
