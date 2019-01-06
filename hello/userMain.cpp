//#include "thread.h"
//#include <iostream.h>
//////
//////
//////class Ispisivac : public Thread {
//////private:
//////	char c;
//////
//////protected:
//////
//////	virtual void run();
//////	void ispisi(char c){}
//////public:
//////	Ispisivac(StackSize ss, Time ts, char cc): Thread(ss,ts){
//////		c = cc;
//////	}
//////
//////};
//////
//////void Ispisivac::run(){
//////	cout<<"run ";
//////	cout<< getId() <<": "<< c <<endl;
//////	while(1);
//////}
//////
//////
//////void tick(){}
//////
//////int userMain(int argc, char* argv[]) {
//////
//////	//cout<< "startProject"<<endl ;
//////
////////	Ispisivac* t2 = new Ispisivac(2048,43,'c');
////////	cout<< "bla"<<endl ;
////////	t2->start();
////////	Ispisivac* t3 = new Ispisivac(2048,43,'c');
////////		t3->start();
////////		Ispisivac* t4 = new Ispisivac(2048,43,'c');
////////			t4->start();
//////
//////
//////	//delete t2;
////////	delete t3;
////////	delete t4;
//////
////////	cout<< "endProject"<<endl ;
//////
//////
//////	return 0;
//////}
////
////
////
////#include <iostream.h>
////#include <stdlib.h>
////
////#include "thread.h"
////#include "semaphor.h"
////// #include "event.h"
////
//// //PREPAREENTRY(9,1);
////
////void tick() {}
////
////Semaphore* ioMutex = 0;
////Semaphore* sleepSem = 0;
////Semaphore* randMutex = 0;
////
////
////class Znak : public Thread
////{
////public:
////    Znak(char znak, int n) : Thread(), znak(znak), n(n) {}
////    virtual ~Znak() { waitToComplete(); }
////
////    void run()
////    {
////         for (long i = 0; i < 10; i++)
////        for (int d = 0; d < n; d++)
////        {
////            if (ioMutex->wait(0))
////            {
////                cout << znak;
////                ioMutex->signal();
////            }
////        	 cout << znak;
//////             for (int j = 0; j < 1000; j++)
//////                 for (int k = 0; k < 1000; k++);
////
////            sleepSem->wait(1);
////
////            randMutex->wait(0);
////            Time sleepTime = 2 + rand() % 4;
////            randMutex->signal();
////            sleepSem->wait(sleepTime);
////
////             dispatch();
////        }
////
////        ioMutex->wait(0);
////        cout << endl << znak << " finished" << endl;
////        ioMutex->signal();
////    }
////
////private:
////    char znak;
////    int n;
////
////};
////
////
////int userMain2(int argc, char* argv[])
////{
////    ioMutex = new Semaphore(1);
////    sleepSem = new Semaphore(0);
////    randMutex = new Semaphore(1);
////
////    int i, n = 10;
////    Znak** zn = new Znak*[n];
////    for (i = 0; i < n; i++)
////        zn[i] = new Znak('a' + i, 10 + 5 * i);
////
////    for (i = 0; i < n; i++)
////        zn[i]->start();
////
////    for (i = 0; i < n; i++)
////        delete zn[i];
////    delete[] zn;
////
////    delete randMutex;
////    delete sleepSem;
////    delete ioMutex;
////
////    cout << endl << "userMain finished" << endl;
////
////    return 0;
////}
//#include "ivtent.h"
//void tick(){}
//
//PREPAREENTRY(9,0);
//
//void userMain(int argc, char* argv[]){
//	cout <<endl<<"hello world"<<endl;
//	Event event(9);
//	event.wait();
//	cout<< "kraj"<<endl;
//}
